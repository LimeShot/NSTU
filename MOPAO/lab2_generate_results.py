from __future__ import annotations

import json
import os
import random
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import statsmodels.api as sm
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
from sklearn.preprocessing import MinMaxScaler
from statsmodels.tsa.stattools import acf, pacf
from statsmodels.tsa.arima.model import ARIMA
from statsmodels.tsa.statespace.sarimax import SARIMAX
from tensorflow.keras.callbacks import EarlyStopping, ReduceLROnPlateau
from tensorflow.keras.layers import LSTM, Dense, Dropout, Input
from tensorflow.keras.models import Sequential
from tensorflow.keras.optimizers import Adam
from xgboost import XGBRegressor


ROOT = Path(__file__).resolve().parent
STATIC_DATA = ROOT / "siteChumakov" / "chumakov" / "static" / "data"
STATIC_NOTEBOOK = ROOT / "siteChumakov" / "chumakov" / "static" / "chumakov" / "lab2_notebook"
STATION_FILE = STATIC_DATA / "indices_station_17150.csv"
ALL_STATIONS_FILE = STATIC_DATA / "spei_all_stations.csv"
FUTURE_STEPS = 24
MODEL_ORDER = ["ARIMA", "SARIMA", "XGBoost", "LSTM"]
PLOT_BLUE = "#0f8fd5"
PLOT_RED = "#e84d3c"
PLOT_GRID = "#dce5ed"
PLOT_TEXT = "#1d2b3a"

plt.rcParams["font.family"] = "DejaVu Sans"
plt.rcParams["axes.unicode_minus"] = False


def metric_row(model: str, actual: pd.Series, predicted: pd.Series) -> dict[str, float | str]:
    actual, predicted = actual.align(predicted, join="inner")
    residual = actual - predicted
    non_zero = actual.replace(0, np.nan)
    return {
        "model": model,
        "RMSE": float(np.sqrt(mean_squared_error(actual, predicted))),
        "MAE": float(mean_absolute_error(actual, predicted)),
        "MAPE": float((np.abs(residual / non_zero).dropna().mean()) * 100),
        "R2": float(r2_score(actual, predicted)),
    }


def adf_result(series: pd.Series) -> dict[str, float | str]:
    stat, pvalue, used_lag, nobs, critical_values, _ = sm.tsa.adfuller(series.dropna())
    return {
        "test": "ADF",
        "statistic": float(stat),
        "pvalue": float(pvalue),
        "lags": int(used_lag),
        "nobs": int(nobs),
        "conclusion": "stationary" if pvalue < 0.05 else "non-stationary",
        "critical_1": float(critical_values["1%"]),
        "critical_5": float(critical_values["5%"]),
        "critical_10": float(critical_values["10%"]),
    }


def kpss_result(series: pd.Series) -> dict[str, float | str]:
    stat, pvalue, used_lag, critical_values = sm.tsa.kpss(series.dropna(), regression="c", nlags="auto")
    return {
        "test": "KPSS",
        "statistic": float(stat),
        "pvalue": float(pvalue),
        "lags": int(used_lag),
        "conclusion": "stationary" if pvalue > 0.05 else "non-stationary",
        "critical_1": float(critical_values["1%"]),
        "critical_5": float(critical_values["5%"]),
        "critical_10": float(critical_values["10%"]),
    }


def make_features(series: pd.Series, lags: int = 12) -> pd.DataFrame:
    data = pd.DataFrame({"SPEI3": series})
    for lag in range(1, lags + 1):
        data[f"lag_{lag}"] = data["SPEI3"].shift(lag)
    for window in (3, 6, 12):
        data[f"rolling_mean_{window}"] = data["SPEI3"].shift(1).rolling(window).mean()
        data[f"rolling_std_{window}"] = data["SPEI3"].shift(1).rolling(window).std()
    data['EWMA_12'] = data["SPEI3"].ewm(span=12).mean()
    data['EWMA_6'] = data["SPEI3"].ewm(span=6).mean()
    data['Diff_1'] = data["SPEI3"].diff(1)
    data['Diff_12'] = data["SPEI3"].diff(12) 
    data["month"] = data.index.month
    data["year"] = data.index.year
    return data.dropna()


def create_lstm_feature_dataset(
    features: pd.DataFrame,
    target: pd.Series,
    sequence_length: int = 12,
) -> tuple[np.ndarray, np.ndarray, pd.DatetimeIndex]:
    x, y, indices = [], [], []
    feature_values = features.values
    target_values = target.values
    for i in range(sequence_length, len(features)):
        x.append(feature_values[i - sequence_length:i])
        y.append(target_values[i])
        indices.append(target.index[i])
    return np.array(x), np.array(y), pd.DatetimeIndex(indices)


def create_lstm_series_dataset(
    scaled_series: pd.Series,
    sequence_length: int = 24,
) -> tuple[np.ndarray, np.ndarray, pd.DatetimeIndex]:
    x, y, indices = [], [], []
    values = scaled_series.values
    for i in range(sequence_length, len(values)):
        x.append(values[i - sequence_length:i])
        y.append(values[i])
        indices.append(scaled_series.index[i])
    x_array = np.array(x).reshape(len(x), sequence_length, 1)
    return x_array, np.array(y), pd.DatetimeIndex(indices)


def make_future_features(history: pd.Series, forecast_date: pd.Timestamp, lags: int = 12) -> pd.DataFrame:
    row = {}
    for lag in range(1, lags + 1):
        row[f"lag_{lag}"] = history.iloc[-lag]
    for window in (3, 6, 12):
        window_data = history.iloc[-window:]
        row[f"rolling_mean_{window}"] = window_data.mean()
        row[f"rolling_std_{window}"] = window_data.std()
    # use the most recent scalar values (not full Series) to avoid object dtypes
    row['EWMA_12'] = float(history.ewm(span=12).mean().iloc[-1])
    row['EWMA_6'] = float(history.ewm(span=6).mean().iloc[-1])
    row['Diff_1'] = float(history.diff(1).iloc[-1])
    # diff over 12 periods may be NaN for short histories; coerce to float safely
    diff12 = history.diff(12)
    row['Diff_12'] = float(diff12.iloc[-1])
    row["month"] = forecast_date.month
    row["year"] = forecast_date.year
    return pd.DataFrame([row])


def recursive_xgb_forecast(model: XGBRegressor, series: pd.Series, future_index: pd.DatetimeIndex) -> pd.Series:
    history = series.copy()
    predictions = []
    for forecast_date in future_index:
        features = make_future_features(history, forecast_date)
        # ensure numeric dtypes for XGBoost (int/float/bool/category required)
        features = features.astype(float)
        prediction = float(model.predict(features)[0])
        predictions.append(prediction)
        history.loc[forecast_date] = prediction
    return pd.Series(predictions, index=future_index, name="predicted")


def recursive_lstm_feature_forecast(
    model: Sequential,
    feature_scaler: MinMaxScaler,
    target_scaler: MinMaxScaler,
    feature_history: pd.DataFrame,
    series_history: pd.Series,
    future_index: pd.DatetimeIndex,
    feature_cols: list[str],
    sequence_length: int = 12,
) -> pd.Series:
    scaled_feature_history = list(feature_scaler.transform(feature_history[feature_cols]))
    predictions = []
    history = series_history.copy()
    for forecast_date in future_index:
        future_features = make_future_features(history, forecast_date).reindex(columns=feature_cols)
        scaled_future = feature_scaler.transform(future_features.astype(float))[0]
        scaled_feature_history.append(scaled_future)
        x_input = np.array(scaled_feature_history[-sequence_length:]).reshape(
            1, sequence_length, len(feature_cols)
        )
        scaled_prediction = float(model.predict(x_input, verbose=0)[0, 0])
        prediction = float(target_scaler.inverse_transform([[scaled_prediction]])[0, 0])
        predictions.append(prediction)
        history.loc[forecast_date] = prediction
    return pd.Series(predictions, index=future_index, name="predicted")


def recursive_lstm_series_forecast(
    model: Sequential,
    scaler: MinMaxScaler,
    series_history: pd.Series,
    future_index: pd.DatetimeIndex,
    sequence_length: int = 24,
) -> pd.Series:
    scaled_history = list(scaler.transform(series_history.values.reshape(-1, 1)).ravel())
    predictions = []
    for _ in future_index:
        x_input = np.array(scaled_history[-sequence_length:]).reshape(1, sequence_length, 1)
        scaled_prediction = float(model.predict(x_input, verbose=0)[0, 0])
        scaled_history.append(scaled_prediction)
        prediction = float(scaler.inverse_transform([[scaled_prediction]])[0, 0])
        predictions.append(prediction)
    return pd.Series(predictions, index=future_index, name="predicted")


def build_lstm_model(sequence_length: int, feature_count: int) -> Sequential:
    model = Sequential(
        [
            Input(shape=(sequence_length, feature_count)),
            LSTM(64, return_sequences=True),
            Dropout(0.15),
            LSTM(32, return_sequences=False),
            Dense(16, activation="relu"),
            Dense(1),
        ]
    )
    model.compile(optimizer=Adam(learning_rate=0.001), loss="huber")
    return model


def style_axis(ax: plt.Axes) -> None:
    ax.set_facecolor("#ffffff")
    ax.grid(True, color=PLOT_GRID, linewidth=0.8, alpha=0.85)
    ax.tick_params(colors=PLOT_TEXT, labelsize=9)
    for spine in ("top", "right"):
        ax.spines[spine].set_visible(False)
    ax.spines["left"].set_color("#c8d4df")
    ax.spines["bottom"].set_color("#c8d4df")


def save_figure(fig: plt.Figure, output_path: Path) -> None:
    fig.patch.set_facecolor("#ffffff")
    fig.savefig(output_path, dpi=160, bbox_inches="tight", facecolor="#ffffff")
    plt.close(fig)


def save_diagnostics_plot(result, title: str, output_path: Path) -> None:
    fig = result.plot_diagnostics(figsize=(12.5, 8.2))
    fig.suptitle(title, fontsize=14, fontweight="bold", color=PLOT_TEXT, y=0.99)
    for ax in fig.axes:
        style_axis(ax)
        ax.title.set_color(PLOT_TEXT)
        ax.title.set_fontsize(10)
    fig.tight_layout(rect=(0, 0, 1, 0.97))
    save_figure(fig, output_path)


def save_residuals_plot(actual: pd.Series, predicted: pd.Series, title: str, output_path: Path) -> None:
    actual, predicted = actual.align(predicted, join="inner")
    residuals = actual - predicted
    fig, ax = plt.subplots(figsize=(12.5, 4.8))
    ax.plot(residuals.index, residuals, color=PLOT_BLUE, linewidth=1.8, label="Остатки")
    ax.axhline(0, color=PLOT_RED, linewidth=1.4, linestyle="--", alpha=0.85)
    ax.set_title(title, fontsize=14, fontweight="bold", color=PLOT_TEXT, pad=14)
    ax.set_xlabel("Дата", color=PLOT_TEXT)
    ax.set_ylabel("Ошибка", color=PLOT_TEXT)
    style_axis(ax)
    ax.legend(frameon=False, loc="upper right")
    fig.tight_layout()
    save_figure(fig, output_path)


def save_forecast_plot(actual: pd.Series, predicted: pd.Series, title: str, output_path: Path) -> None:
    actual, predicted = actual.align(predicted, join="inner")
    fig, ax = plt.subplots(figsize=(12.5, 4.8))
    ax.plot(actual.index, actual, color=PLOT_BLUE, linewidth=1.8, label="Факт")
    ax.plot(predicted.index, predicted, color=PLOT_RED, linewidth=1.8, label="Прогноз")
    ax.set_title(title, fontsize=14, fontweight="bold", color=PLOT_TEXT, pad=14)
    ax.set_xlabel("Дата", color=PLOT_TEXT)
    ax.set_ylabel("SPEI3", color=PLOT_TEXT)
    style_axis(ax)
    ax.legend(frameon=False, loc="upper right")
    fig.tight_layout()
    save_figure(fig, output_path)


def write_arima_sarima_plots(
    arima_result,
    sarima_result,
    test: pd.Series,
    forecasts: dict[str, pd.Series],
) -> None:
    STATIC_NOTEBOOK.mkdir(parents=True, exist_ok=True)
    plot_configs = [
        ("arima", "ARIMA", arima_result),
        ("sarima", "SARIMA", sarima_result),
    ]
    for file_prefix, model_name, result in plot_configs:
        save_diagnostics_plot(
            result,
            f"Диагностика обучения {model_name}",
            STATIC_NOTEBOOK / f"{file_prefix}_diagnostics.png",
        )
        save_residuals_plot(
            test,
            forecasts[model_name],
            f"Остатки {model_name} на тестовом периоде",
            STATIC_NOTEBOOK / f"{file_prefix}_residuals.png",
        )
        save_forecast_plot(
            test,
            forecasts[model_name],
            f"Прогноз {model_name} на тестовом периоде",
            STATIC_NOTEBOOK / f"{file_prefix}_forecast.png",
        )


def fit_lstm_model(model: Sequential, x_train: np.ndarray, y_train: np.ndarray) -> None:
    callbacks = [
        EarlyStopping(monitor="val_loss", patience=35, restore_best_weights=True),
        ReduceLROnPlateau(monitor="val_loss", factor=0.5, patience=12, min_lr=0.00005),
    ]
    model.fit(
        x_train,
        y_train,
        epochs=350,
        batch_size=24,
        validation_split=0.15,
        callbacks=callbacks,
        verbose=0,
        shuffle=False,
    )


def main() -> None:
    os.environ["TF_CPP_MIN_LOG_LEVEL"] = "2"
    np.random.seed(42)
    random.seed(42)

    STATIC_DATA.mkdir(parents=True, exist_ok=True)

    station_data = pd.read_csv(STATION_FILE, parse_dates=["date"])
    all_stations = pd.read_csv(ALL_STATIONS_FILE, parse_dates=["date"])

    series = (
        station_data.set_index("date")["SPEI3"]
        .dropna()
        .asfreq("MS")
        .interpolate(limit_direction="both")
    )
    train = series.loc[: "2010-12-01"]
    test = series.loc["2011-01-01":]

    forecasts: dict[str, pd.Series] = {}
    future_forecasts: dict[str, pd.Series] = {}
    future_index = pd.date_range(series.index[-1] + pd.offsets.MonthBegin(1), periods=FUTURE_STEPS, freq="MS")

    arima = ARIMA(train, order=(4, 1, 0)).fit()
    forecasts["ARIMA"] = arima.forecast(steps=len(test)).rename("predicted")
    forecasts["ARIMA"].index = test.index
    arima_full = ARIMA(series, order=(4, 1, 0)).fit()
    future_forecasts["ARIMA"] = arima_full.forecast(steps=FUTURE_STEPS).rename("predicted")
    future_forecasts["ARIMA"].index = future_index

    sarima = SARIMAX(
        train,
        order=(1, 1, 1),
        seasonal_order=(1, 0, 1, 12),
        enforce_stationarity=False,
        enforce_invertibility=False,
    ).fit(disp=False)
    forecasts["SARIMA"] = sarima.forecast(steps=len(test)).rename("predicted")
    forecasts["SARIMA"].index = test.index
    sarima_full = SARIMAX(
        series,
        order=(1, 1, 1),
        seasonal_order=(1, 0, 1, 12),
        enforce_stationarity=False,
        enforce_invertibility=False,
    ).fit(disp=False)
    future_forecasts["SARIMA"] = sarima_full.forecast(steps=FUTURE_STEPS).rename("predicted")
    future_forecasts["SARIMA"].index = future_index

    (STATIC_DATA / "lab2_arima_summary.txt").write_text(str(arima.summary()), encoding="utf-8")
    (STATIC_DATA / "lab2_sarima_summary.txt").write_text(str(sarima.summary()), encoding="utf-8")
    write_arima_sarima_plots(arima, sarima, test, forecasts)

    features = make_features(series)
    feature_cols = [col for col in features.columns if col != "SPEI3"]
    train_features = features.loc[: "2010-12-01"]
    test_features = features.loc["2011-01-01":]
    x_train = train_features.drop(columns=["SPEI3"])
    y_train = train_features["SPEI3"]
    x_test = test_features.drop(columns=["SPEI3"])
    y_test = test_features["SPEI3"]
    xgb = XGBRegressor(
        n_estimators=200,
        max_depth=5,
        learning_rate=0.04,
        subsample=0.9,
        colsample_bytree=0.9,
        objective="reg:squarederror",
        random_state=42,
    )
    xgb.fit(x_train, y_train)
    forecasts["XGBoost"] = pd.Series(xgb.predict(x_test), index=y_test.index, name="predicted")
    future_forecasts["XGBoost"] = recursive_xgb_forecast(xgb, series, future_index)

    sequence_length = 24
    lstm_scaler = MinMaxScaler(feature_range=(-1, 1))
    train_scaled = pd.Series(
        lstm_scaler.fit_transform(train.values.reshape(-1, 1)).ravel(),
        index=train.index,
        name="SPEI3",
    )
    test_scaled = pd.Series(
        lstm_scaler.transform(test.values.reshape(-1, 1)).ravel(),
        index=test.index,
        name="SPEI3",
    )
    x_lstm_train, y_lstm_train, _ = create_lstm_series_dataset(train_scaled, sequence_length)
    test_context_scaled = pd.concat([
        train_scaled.tail(sequence_length),
        test_scaled,
    ])
    x_lstm_test, _, lstm_index = create_lstm_series_dataset(test_context_scaled, sequence_length)
    lstm = build_lstm_model(sequence_length, 1)
    fit_lstm_model(lstm, x_lstm_train, y_lstm_train)
    lstm_pred_scaled = lstm.predict(x_lstm_test, verbose=0).ravel()
    lstm_pred = lstm_scaler.inverse_transform(lstm_pred_scaled.reshape(-1, 1)).ravel()
    forecasts["LSTM"] = pd.Series(lstm_pred, index=lstm_index, name="predicted")
    
    full_lstm_scaler = MinMaxScaler(feature_range=(-1, 1))
    full_scaled = pd.Series(
        full_lstm_scaler.fit_transform(series.values.reshape(-1, 1)).ravel(),
        index=series.index,
        name="SPEI3",
    )
    x_lstm_full, y_lstm_full, _ = create_lstm_series_dataset(full_scaled, sequence_length)
    full_lstm = build_lstm_model(sequence_length, 1)
    fit_lstm_model(full_lstm, x_lstm_full, y_lstm_full)
    future_forecasts["LSTM"] = recursive_lstm_series_forecast(
        full_lstm,
        full_lstm_scaler,
        series,
        future_index,
        sequence_length,
    )

    forecast_rows = []
    metrics = []
    for model_name, predicted in forecasts.items():
        actual = series.reindex(predicted.index)
        metrics.append(metric_row(model_name, actual, predicted))
        for date, prediction in predicted.items():
            forecast_rows.append(
                {
                    "date": date.date().isoformat(),
                    "model": model_name,
                    "actual": float(actual.loc[date]),
                    "predicted": float(prediction),
                    "residual": float(actual.loc[date] - prediction),
                }
            )

    metric_order = {model: index for index, model in enumerate(MODEL_ORDER)}
    metrics_df = pd.DataFrame(metrics)
    metrics_df["_model_order"] = metrics_df["model"].map(metric_order).fillna(len(MODEL_ORDER))
    metrics_df = metrics_df.sort_values("_model_order").drop(columns=["_model_order"])

    pd.DataFrame(forecast_rows).to_csv(STATIC_DATA / "lab2_forecasts.csv", index=False)
    metrics_df.to_csv(STATIC_DATA / "lab2_metrics.csv", index=False)

    future_rows = []
    for model_name, predicted in future_forecasts.items():
        for date, prediction in predicted.items():
            future_rows.append(
                {
                    "date": date.date().isoformat(),
                    "model": model_name,
                    "predicted": float(prediction),
                }
            )
    pd.DataFrame(future_rows).to_csv(STATIC_DATA / "lab2_future_forecasts.csv", index=False)

    first_diff = series.diff().dropna()
    stat_payload = {
        "station_id": 17150,
        "series_start": series.index.min().date().isoformat(),
        "series_end": series.index.max().date().isoformat(),
        "future_start": future_index.min().date().isoformat(),
        "future_end": future_index.max().date().isoformat(),
        "train_end": "2010-12-01",
        "test_start": "2011-01-01",
        "spei3_describe": series.describe().to_dict(),
        "tests": [
            {"series": "SPEI3", **adf_result(series)},
            {"series": "SPEI3", **kpss_result(series)},
        ],
        "acf": [{"lag": i, "value": float(v)} for i, v in enumerate(acf(first_diff, nlags=40))],
        "pacf": [{"lag": i, "value": float(v)} for i, v in enumerate(pacf(first_diff, nlags=40, method="ywm"))],
        "index_checks": {
            "SPEI3_first_valid": station_data["SPEI3"].first_valid_index(),
            "SPEI6_first_valid": station_data["SPEI6"].first_valid_index(),
            "SPEI9_first_valid": station_data["SPEI9"].first_valid_index(),
            "SPEI12_first_valid": station_data["SPEI12"].first_valid_index(),
        },
    }
    for key, row_number in stat_payload["index_checks"].items():
        if row_number is not None:
            stat_payload["index_checks"][key] = station_data.loc[row_number, "date"].date().isoformat()

    with (STATIC_DATA / "lab2_statistics.json").open("w", encoding="utf-8") as file:
        json.dump(stat_payload, file, ensure_ascii=False, indent=2)


if __name__ == "__main__":
    main()
