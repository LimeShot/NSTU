#!/usr/bin/env python3
"""
Обработка архива RP5 для расчета суточных, декадных и месячных показателей,
а также SPI-3 и SPEI-3.

Пример запуска:
    pip install -r requirements.txt
    python process_rp5_weather_pandas_spei.py input.gz --outdir result

Что делает скрипт:
- читает gzip-архив RP5;
- считает среднюю температуру и среднюю влажность;
- суммирует осадки и испаряемость;
- считает ГТК по суточным данным и агрегированным периодам;
- считает SPI-3 и SPEI-3 через библиотеку spei.
"""

from __future__ import annotations

import argparse
import gzip
import re
import warnings
from pathlib import Path

import numpy as np
import pandas as pd
import spei


def parse_precipitation(value: object) -> float:
    """Преобразует поле RRR из RP5 в числовое значение осадков."""
    if pd.isna(value):
        return np.nan

    text = str(value).strip().replace(",", ".")
    low = text.lower()

    if low in {"осадков нет", "следы осадков", "нет осадков"}:
        return 0.0

    match = re.search(r"-?\d+(?:\.\d+)?", text)
    return float(match.group(0)) if match else np.nan


def safe_sum(series: pd.Series) -> float:
    """Сумма, которая возвращает NaN, если в периоде нет ни одного значения."""
    return series.sum(min_count=1)


def read_rp5_archive(path: Path) -> pd.DataFrame:
    """Читает gzip-архив RP5 и оставляет только нужные метеопараметры."""
    with gzip.open(path, "rt", encoding="utf-8") as file:
        raw = pd.read_csv(
            file,
            sep=";",
            comment="#",
            quotechar='"',
            na_values=[""],
            dtype=str,
            index_col=False,
        )

    time_col = raw.columns[0]

    data = pd.DataFrame(
        {
            "datetime": pd.to_datetime(
                raw[time_col],
                format="%d.%m.%Y %H:%M",
                errors="coerce",
            ),
            "temperature": pd.to_numeric(raw["T"], errors="coerce"),
            "humidity": pd.to_numeric(raw["U"], errors="coerce"),
            "precipitation": raw["RRR"].map(parse_precipitation),
        }
    )

    return data.dropna(subset=["datetime"]).sort_values("datetime")


def add_daily_evaporation(daily: pd.DataFrame) -> pd.DataFrame:
    """
    Считает суточную испаряемость по формуле Иванова.

    Формула Иванова обычно дает месячную испаряемость:
        E = 0.0018 * (25 + t)^2 * (100 - f)

    Для суточного значения результат делится на число дней в месяце.
    Потом суточные значения суммируются для декад и месяцев.
    """
    result = daily.copy()
    days_in_month = result.index.days_in_month

    result["evaporation"] = (
        0.0018
        * (25 + result["temperature"]) ** 2
        * (100 - result["humidity"])
        / days_in_month
    )

    return result


def add_gtk(table: pd.DataFrame, active_temperature_sum: pd.Series) -> pd.DataFrame:
    """
    Добавляет ГТК.

    Используется классическая логика:
        ГТК = 10 * сумма осадков / сумма активных температур

    Активная температура берется только за дни со средней температурой > 10°C.
    Если активных температур нет, ГТК не считается.
    """
    result = table.copy()
    result["GTK"] = np.where(
        active_temperature_sum > 10,
        10 * result["precipitation"] / active_temperature_sum,
        np.nan,
    )
    return result


def make_daily(observations: pd.DataFrame) -> pd.DataFrame:
    """Формирует суточную таблицу."""
    obs = observations.copy()
    obs["date"] = obs["datetime"].dt.floor("D")

    daily = (
        obs.groupby("date")
        .agg(
            temperature=("temperature", "mean"),
            precipitation=("precipitation", safe_sum),
            humidity=("humidity", "mean"),
        )
        .sort_index()
    )

    # Непрерывный дневной индекс нужен, чтобы SPI/SPEI не склеивали периоды через пропуски.
    full_dates = pd.date_range(daily.index.min(), daily.index.max(), freq="D")
    daily = daily.reindex(full_dates)
    daily.index.name = "date"

    daily = add_daily_evaporation(daily)

    active_temperature = daily["temperature"].where(daily["temperature"] > 10)
    daily["GTK"] = 10 * daily["precipitation"] / active_temperature

    return daily


def make_decade(daily: pd.DataFrame) -> pd.DataFrame:
    """Формирует декадную таблицу."""
    temp = daily.copy()
    temp["date"] = temp.index

    day = temp["date"].dt.day
    start_day = np.select([day <= 10, day <= 20], [1, 11], default=21)

    temp["period"] = pd.to_datetime(
        {
            "year": temp["date"].dt.year,
            "month": temp["date"].dt.month,
            "day": start_day,
        }
    )

    temp["active_temperature"] = temp["temperature"].where(temp["temperature"] > 10, 0)

    grouped = temp.groupby("period")

    decade = grouped.agg(
        days=("temperature", "count"),
        temperature=("temperature", "mean"),
        precipitation=("precipitation", safe_sum),
        humidity=("humidity", "mean"),
        evaporation=("evaporation", safe_sum),
        active_temperature_sum=("active_temperature", "sum"),
    )

    decade = add_gtk(decade, decade["active_temperature_sum"])
    # Оставляем колонку суммы активных температур в итоговой таблице декад
    decade.index.name = "date"

    # В итоговую таблицу не выводим полностью пустые декады.
    return decade[decade["days"] > 0]


def make_monthly(daily: pd.DataFrame) -> pd.DataFrame:
    """Формирует месячную таблицу и считает SPI-3/SPEI-3."""
    temp = daily.copy()
    temp["active_temperature"] = temp["temperature"].where(temp["temperature"] > 10, 0)

    grouped = temp.resample("MS")

    monthly = grouped.agg(
        temperature=("temperature", "mean"),
        precipitation=("precipitation", safe_sum),
        humidity=("humidity", "mean"),
        evaporation=("evaporation", safe_sum),
        active_temperature_sum=("active_temperature", "sum"),
    )

    monthly = add_gtk(monthly, monthly["active_temperature_sum"])
    # Оставляем колонку суммы активных температур в итоговой таблице месяцев

    balance = monthly["precipitation"] - monthly["evaporation"]

    # SPI-3: 3-месячная сумма осадков.
    # SPEI-3: 3-месячная сумма водного баланса: осадки - испаряемость.
    # Непрерывный месячный индекс оставлен специально: так длинные пропуски не склеиваются.
    with warnings.catch_warnings():
        warnings.simplefilter("ignore")
        monthly["SPI_3"] = spei.spi(
            monthly["precipitation"],
            timescale=3,
            fit_freq="MS",
        ).reindex(monthly.index)

        monthly["SPEI_3"] = spei.spei(
            balance,
            timescale=3,
            fit_freq="MS",
        ).reindex(monthly.index)

    monthly.index.name = "date"

    # Для преподавателя убираем месяцы, где вообще нет данных.
    return monthly.dropna(
        subset=["temperature", "precipitation", "humidity"],
        how="all",
    )


def find_missing_intervals(observations: pd.DataFrame) -> pd.DataFrame:
    """Ищет разрывы между датами наблюдений."""
    dates = (
        observations["datetime"]
        .dt.floor("D")
        .drop_duplicates()
        .sort_values()
        .reset_index(drop=True)
    )

    rows = []
    for previous, current in zip(dates.iloc[:-1], dates.iloc[1:]):
        gap = (current - previous).days
        if gap > 1:
            rows.append(
                {
                    "missing_from": (previous + pd.Timedelta(days=1)).strftime("%Y-%m-%d"),
                    "missing_to": (current - pd.Timedelta(days=1)).strftime("%Y-%m-%d"),
                    "missing_days": gap - 1,
                }
            )

    return pd.DataFrame(rows)


def format_output(df: pd.DataFrame) -> pd.DataFrame:
    """Подготавливает таблицу к сохранению."""
    result = df.reset_index()
    result["date"] = pd.to_datetime(result["date"]).dt.strftime("%Y-%m-%d")

    for column in result.columns:
        if column not in {"date", "days"}:
            result[column] = pd.to_numeric(result[column], errors="coerce").round(3)

    return result


def save_outputs(
    daily: pd.DataFrame,
    decade: pd.DataFrame,
    monthly: pd.DataFrame,
    observations: pd.DataFrame,
    input_path: Path,
    outdir: Path,
) -> None:
    """Сохраняет итоговые CSV-файлы."""
    outdir.mkdir(parents=True, exist_ok=True)

    daily_out = format_output(
        daily.dropna(subset=["temperature", "precipitation", "humidity"], how="all")
    )
    decade_out = format_output(decade)
    monthly_out = format_output(monthly)

    # Переименовать сохраняемые колонки на русский
    col_rename = {
        "date": "дата",
        "days": "дней",
        "temperature": "температура",
        "precipitation": "осадки",
        "humidity": "влажность",
        "evaporation": "испаряемость",
        "active_temperature_sum": "сумма_активных_температур",
        "GTK": "ГТК",
        "SPI_3": "SPI_3",
        "SPEI_3": "SPEI_3",
    }

    daily_out = daily_out.rename(columns=col_rename)
    decade_out = decade_out.rename(columns=col_rename)
    monthly_out = monthly_out.rename(columns=col_rename)

    daily_out.to_csv(
        outdir / "daily.csv",
        index=False,
        sep=";",
        encoding="utf-8-sig",
        na_rep="",
    )
    decade_out.to_csv(
        outdir / "decade.csv",
        index=False,
        sep=";",
        encoding="utf-8-sig",
        na_rep="",
    )
    monthly_out.to_csv(
        outdir / "monthly_spi_spei3.csv",
        index=False,
        sep=";",
        encoding="utf-8-sig",
        na_rep="",
    )

    missing_intervals = find_missing_intervals(observations)
    # Переименуем колонки таблицы пропусков
    missing_rename = {
        "missing_from": "пропущено_с",
        "missing_to": "пропущено_по",
        "missing_days": "пропущено_дней",
    }
    missing_intervals = missing_intervals.rename(columns=missing_rename)
    missing_intervals.to_csv(
        outdir / "missing_intervals.csv",
        index=False,
        sep=";",
        encoding="utf-8-sig",
        na_rep="",
    )

    checks = pd.DataFrame(
        {
            "parameter": [
                "source_file",
                "station_period",
                "observations",
                "daily_rows_with_data",
                "decade_rows_with_data",
                "monthly_rows_with_data",
                "missing_intervals",
                "aggregation_temperature",
                "aggregation_humidity",
                "aggregation_precipitation",
                "aggregation_evaporation",
                "SPI_SPEI_window",
                "SPI_SPEI_note",
                "GTK_rule",
            ],
            "value": [
                input_path.name,
                f"{observations.datetime.min():%Y-%m-%d} — {observations.datetime.max():%Y-%m-%d}",
                len(observations),
                len(daily_out),
                len(decade_out),
                len(monthly_out),
                len(missing_intervals),
                "mean",
                "mean",
                "sum",
                "sum",
                "3 months",
                "calculated on continuous monthly index; values after long gaps stay blank until 3 consecutive months exist",
                "10 * precipitation / sum of daily temperatures above 10°C; blank if no active temperatures",
            ],
        }
    )

    # Заголовки для файла контрольных показателей на русском
    checks = checks.rename(columns={"parameter": "параметр", "value": "значение"})
    checks.to_csv(
        outdir / "checks.csv",
        index=False,
        sep=";",
        encoding="utf-8-sig",
        na_rep="",
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path, help="Path to RP5 .gz archive")
    parser.add_argument("--outdir", type=Path, default=Path("rp5_result"))
    args = parser.parse_args()

    observations = read_rp5_archive(args.input)
    daily = make_daily(observations)
    decade = make_decade(daily)
    monthly = make_monthly(daily)

    save_outputs(
        daily=daily,
        decade=decade,
        monthly=monthly,
        observations=observations,
        input_path=args.input,
        outdir=args.outdir,
    )


if __name__ == "__main__":
    main()
