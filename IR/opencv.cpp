// lab1_circle_detection.cpp
// Компиляция: g++ lab1_circle_detection.cpp -o lab1 `pkg-config --cflags --libs opencv4`
// Или для старых систем: g++ lab1_circle_detection.cpp -o lab1 `pkg-config --cflags --libs opencv`

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

int main() {
    const int H = 512, W = 512;
    const Point center(W / 2, H / 2);  // (256, 256)
    const int true_radius = 100;
    const int background = 50;
    const int circle_intensity = 200;

    // 1. Создаём чистое изображение с кругом
    Mat image_clean(H, W, CV_8UC1, Scalar(background));
    circle(image_clean, center, true_radius, Scalar(circle_intensity), -1); // заполненный круг

    // Уровни шума (стандартное отклонение)
    vector<int> noise_levels = {10, 30, 70};
    vector<double> snr_db;

    // Для результатов
    vector<Vec3f> detected_circles;

    cout << "Истинный круг: центр = (256, 256), радиус = 100\n";
    cout << string(60, '-') << endl;

    for (int sigma : noise_levels) {
        Mat noisy;
        image_clean.copyTo(noisy);

        // Добавляем гауссов шум
        Mat noise(H, W, CV_32FC1);
        randn(noise, 0, sigma);  // среднее 0, стд.откл. = sigma
        noisy.convertTo(noisy, CV_32FC1);
        noisy = noisy + noise;
        noisy.convertTo(noisy, CV_8UC1);

        // Вычисление SNR
        double signal_amplitude = circle_intensity - background;  // 150
        double noise_amplitude = sigma;
        double snr = 20 * log10(signal_amplitude / noise_amplitude);
        snr_db.push_back(snr);

        // 2. Обнаружение круга через HoughCircles
        Mat blurred, edges;
        GaussianBlur(noisy, blurred, Size(9, 9), 2);
        // Можно использовать Canny + Hough, но HoughCircles работает лучше "из коробки"
        vector<Vec3f> circles;
        HoughCircles(blurred, circles,
                     HOUGH_GRADIENT,   // метод
                     1,                // dp = 1 (разрешение аккумулятора)
                     noisy.rows / 8,   // мин. расстояние между центрами
                     100,              // верхний порог для Canny
                     30,               // порог аккумулятора (уменьшить — больше ложных)
                     80,               // мин радиус
                     120);             // макс радиус

        Vec3f best_circle(0, 0, 0);
        if (!circles.empty()) {
            // Берём самый "уверенный" круг (по величине голосов в Hough)
            best_circle = circles[0];
            for (auto& c : circles) {
                if (c[2] > best_circle[2]) best_circle = c; // c[2] — радиус, но и сила голосования
            }
        }

        detected_circles.push_back(best_circle);

        // Вывод результата
        cout << fixed << setprecision(1);
        cout << "Шум σ = " << setw(2) << sigma
             << " | SNR = " << setw(5) << snr << " дБ"
             << " | Найден круг: ";

        if (best_circle[2] > 0) {
            int cx = cvRound(best_circle[0]);
            int cy = cvRound(best_circle[1]);
            int r  = cvRound(best_circle[2]);
            cout << "центр=(" << cx << "," << cy << "), r=" << r;
        } else {
            cout << "НЕ НАЙДЕН";
        }
        cout << endl;
    }

    // =======================
    // Визуализация
    // =======================
    Mat result;
    cvtColor(image_clean, result, COLOR_GRAY2BGR);

    // Рисуем все зашумлённые + найденные круги
    for (int i = 0; i < noise_levels.size(); i++) {
        Mat noisy_color;
        Mat noisy = imread("", 0); // мы её создавали выше, но проще пересоздать
        // Пересоздаём для отображения
        Mat noisy_single;
        image_clean.copyTo(noisy_single);
        Mat noise(H, W, CV_32FC1);
        randn(noise, 0, noise_levels[i]);
        noisy_single.convertTo(noisy_single, CV_32FC1);
        noisy_single += noise;
        noisy_single.convertTo(noisy_single, CV_8UC1);
        cvtColor(noisy_single, noisy_color, COLOR_GRAY2BGR);

        // Истинный круг — зелёный пунктир
        circle(noisy_color, center, true_radius, Scalar(0, 255, 0), 3, LINE_8);

        // Найденный круг — красный
        Vec3f c = detected_circles[i];
        if (c[2] > 0) {
            Point detected_center(cvRound(c[0]), cvRound(c[1]));
            int r = cvRound(c[2]);
            circle(noisy_color, detected_center, r, Scalar(0, 0, 255), 3);
            circle(noisy_color, detected_center, 2, Scalar(0, 0, 255), -1); // точка центра
        }

        // Подпись
        string text = "sigma=" + to_string(noise_levels[i]) + 
                      ", SNR=" + to_string((int)round(snr_db[i])) + "dB";
        putText(noisy_color, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 
                0.8, Scalar(255, 255, 255), 2);

        // Показываем
        imshow("Лаба 1: Обнаружение круга | " + text, noisy_color);
    }

    // Чистое изображение
    Mat clean_color;
    cvtColor(image_clean, clean_color, COLOR_GRAY2BGR);
    circle(clean_color, center, true_radius, Scalar(0, 255, 0), 3);
    putText(clean_color, "Чистое изображение", Point(10, 30), 
            FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 255, 0), 2);
    imshow("Лаба 1: Обнаружение круга | Чистое", clean_color);

    cout << "\nНажмите любую клавишу на любом окне для выхода...\n";
    waitKey(0);
    return 0;
}