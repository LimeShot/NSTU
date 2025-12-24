import streamlit as st
import os
import json
import numpy as np
import pickle
import tensorflow as tf
from pathlib import Path

# ==================== НАСТРОЙКИ ====================
MODELS_DIR = Path(os.path.dirname(os.path.abspath(__file__)), "models")

# ===================================================

@st.cache_resource
def load_all_models():
    models_data = []
    all_features = set()

    # Ищем все .json конфиги
    for config_path in MODELS_DIR.glob("*.json"):
        with open(config_path, "r", encoding="utf-8") as f:
            config = json.load(f)

        model_type = config["model_type"]
        features = config["features"]
        target = config["target"][0]
        needs_scaling = config.get("needs_scaling", False)

        # Путь к файлу с моделью
        model_file = config["coefs"]
        model_path = MODELS_DIR / model_file

        # Загрузка модели
        if not model_path.exists():
            st.error(f"Файл модели не найден: {model_path}")
            continue

        if model_path.suffix in {".pkl"}:
            with open(model_path, "rb") as f:
                model = pickle.load(f)
        elif model_path.suffix in {".h5", ".keras"}:
            model = tf.keras.models.load_model(model_path)
        else:
            st.error(f"Неподдерживаемый формат модели: {model_path}")
            continue

        # Загрузка скейлеров, если нужно
        x_scaler = y_scaler = None
        if needs_scaling:
            x_scaler_path = MODELS_DIR / config["x_scaler"]
            y_scaler_path = MODELS_DIR / config["y_scaler"]

            if x_scaler_path.exists():
                with open(x_scaler_path, "rb") as f:
                    x_scaler = pickle.load(f)
            else:
                st.error(f"Файл скейлера X не найден: {x_scaler_path}")
            if y_scaler_path.exists():
                with open(y_scaler_path, "rb") as f:
                    y_scaler = pickle.load(f)
            else:
                st.error(f"Файл скейлера Y не найден: {y_scaler_path}")

        models_data.append({
            "name": model_type,
            "model": model,
            "features": features,
            "target": target,
            "needs_scaling": needs_scaling,
            "x_scaler": x_scaler,
            "y_scaler": y_scaler,
            "R2": config.get("R2", "—"),
            "RMSE": config.get("RMSE", "—"),
        })

        all_features.update(features)

    return models_data, sorted(all_features)


# ==================== ЗАГРУЗКА ====================
models_data, all_features = load_all_models()

if not models_data:
    st.error("Не найдено ни одной корректной модели в папке `models/`")
    st.stop()

# ==================== SIDEBAR ====================
st.sidebar.header("Значения признаков")

input_values = {}
for feature in all_features:
    input_values[feature] = st.sidebar.number_input(
        feature,
        value=0.0,
        step=0.01,
        format="%.6f"
    )

# ==================== ОСНОВНОЙ ЭКРАН ====================
st.title("Прогнозирование с помощью загруженных моделей")

st.header("Текущие значения признаков")
cols = st.columns(3)
for i, (feat, val) in enumerate(input_values.items()):
    with cols[i % 3]:
        st.metric(feat, f"{val:.6g}")

st.markdown("---")
st.header("Предсказания моделей")

for md in models_data:
    with st.expander(f"Модель: {md['name']} | R2 = {md['R2']} | RMSE = {md['RMSE']}", expanded=True):
        try:
            X_input = np.array([[input_values[f] for f in md['features']]])

            if md['needs_scaling'] and md['x_scaler'] is not None:
                X_scaled = md['x_scaler'].transform(X_input)
                pred_scaled = md['model'].predict(X_scaled)
            else:
                pred_scaled = md['model'].predict(X_input)

            pred_scaled = pred_scaled.flatten()[0]

            # Обратное преобразование, если был скейлер таргета
            if md['needs_scaling'] and md['y_scaler'] is not None:
                pred_original = md['y_scaler'].inverse_transform([[pred_scaled]])[0][0]
                st.info(f"**{md['target']} (после скейлера):** `{pred_scaled:.6g}`")
                st.success(f"**{md['target']} (исходная шкала):** `{pred_original:.6g}`")
            else:
                st.success(f"**{md['target']}:** `{pred_scaled:.6g}`")

        except Exception as e:
            st.error(f"Ошибка предсказания: {str(e)}")