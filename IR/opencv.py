import cv2
import numpy as np
import math

# Параметры изображения
H, W = 512, 512
center = (W // 2, H // 2)        # (256, 256)
true_radius = 100
background = 50
circle_intensity = 200

# 1. Создаём чистое изображение с заполненным кругом
image_clean = np.full((H, W), background, dtype=np.uint8)
cv2.circle(image_clean, center, true_radius, circle_intensity, -1)  # заполненный круг

# Уровни шума (стандартное отклонение)
noise_levels = [10, 30, 70]
snr_db = []
detected_circles = []

print("Истинный круг: центр = (256, 256), радиус = 100")
print("-" * 60)

for sigma in noise_levels:
    # Копируем чистое изображение и добавляем гауссов шум
    noisy = image_clean.astype(np.float32)
    noise = np.random.normal(0, sigma, (H, W)).astype(np.float32)
    noisy = noisy + noise
    noisy = np.clip(noisy, 0, 255).astype(np.uint8)

    # Вычисление SNR в децибелах
    signal_amplitude = circle_intensity - background  # 150
    noise_amplitude = sigma
    snr = 20 * math.log10(signal_amplitude / noise_amplitude)
    snr_db.append(snr)

    # 2. Обнаружение круга с помощью HoughCircles
    blurred = cv2.GaussianBlur(noisy, (9, 9), 2)

    circles = cv2.HoughCircles(
        blurred,
        cv2.HOUGH_GRADIENT,
        dp=1,                    # разрешение аккумулятора
        minDist=noisy.shape[0] // 8,
        param1=100,              # верхний порог Canny
        param2=30,               # порог аккумулятора (меньше → больше ложных)
        minRadius=80,
        maxRadius=120
    )

    best_circle = None
    if circles is not None:
        circles = np.uint16(np.around(circles))
        # Выбираем круг с наибольшим радиусом (обычно соответствует наибольшему накоплению голосов)
        best_circle = max(circles[0], key=lambda c: c[2])  # c[2] — радиус
        best_circle = best_circle.astype(float)  # возвращаем в float для единообразия

    detected_circles.append(best_circle)

    # Вывод результата в консоль
    print(f"Шум σ = {sigma:2d} | SNR = {snr:5.1f} дБ | Найден круг: ", end="")
    if best_circle is not None:
        cx, cy, r = int(best_circle[0]), int(best_circle[1]), int(best_circle[2])
        print(f"центр=({cx},{cy}), r={r}")
    else:
        print("НЕ НАЙДЕН")

# =======================
# Визуализация
# =======================

# Чистое изображение
clean_color = cv2.cvtColor(image_clean, cv2.COLOR_GRAY2BGR)
cv2.circle(clean_color, center, true_radius, (0, 255, 0), 3)
cv2.putText(clean_color, "Чистое изображение", (10, 30),
            cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)
cv2.imshow("Лаба 1: Обнаружение круга | Чистое", clean_color)

# Зашумлённые изображения + найденные круги
for i, sigma in enumerate(noise_levels):
    # Пересоздаём зашумлённое изображение
    noisy_float = image_clean.astype(np.float32)
    noise = np.random.normal(0, sigma, (H, W)).astype(np.float32)
    noisy_float = noisy_float + noise
    noisy = np.clip(noisy_float, 0, 255).astype(np.uint8)
    noisy_color = cv2.cvtColor(noisy, cv2.COLOR_GRAY2BGR)

    # Истинный круг — зелёный
    cv2.circle(noisy_color, center, true_radius, (0, 255, 0), 3, cv2.LINE_8)

    # Найденный круг — красный
    c = detected_circles[i]
    if c is not None:
        center_det = (int(c[0]), int(c[1]))
        radius_det = int(c[2])
        cv2.circle(noisy_color, center_det, radius_det, (0, 0, 255), 3)
        cv2.circle(noisy_color, center_det, 2, (0, 0, 255), -1)  # центр точкой

    # Подпись
    text = f"sigma={sigma}, SNR={int(round(snr_db[i]))}dB"
    cv2.putText(noisy_color, text, (10, 30),
                cv2.FONT_HERSHEY_SIMPLEX, 0.8, (255, 255, 255), 2)

    cv2.imshow(f"Лаба 1: Обнаружение круга | {text}", noisy_color)

print("\nНажмите любую клавишу на любом окне для выхода...")
cv2.waitKey(0)
cv2.destroyAllWindows()