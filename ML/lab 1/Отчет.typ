#import "@preview/modern-g7-32:0.2.0": abstract, appendix-heading, appendixes, enum-numbering, gost

#set enum(numbering: enum-numbering)

#show: gost.with(
  ministry: "Наименование министерства (ведомства) или другого структурного образования, в систему которого входит организация-исполнитель",
  organization: (
    full: "Полное наименование организации — исполнителя НИР",
    short: "Сокращённое наименование организации",
  ),
  udk: "индекс УДК",
  research-number: "регистрационный номер НИР",
  report-number: "регистрационный номер отчета",
  approved-by: (
    name: "Фамилия И.О.",
    position: "Должность, наимен. орг.",
    year: 2017,
  ), // Гриф согласования
  agreed-by: (
    name: "Фамилия И.О.",
    position: "Должность, наимен. орг.",
    year: auto,
  ), // Гриф утверждения, год подставляется из аргумента year
  report-type: "отчёт",
  about: "О научно-исследовательской работе",
  research: "Наименование НИР",
  bare-subject: false, // Можно убрать "по теме"
  subject: "Наименование отчёта",
  manager: (
    name: "Фамилия И.О.",
    position: "Должность",
    title: "Руководитель НИР,",
  ), // Руководитель отчёта
  stage: (type: "вид отчёта", num: 1), // Этап отчёта
  federal: "Наименование федеральной программы",
  part: 2, // Номер книги отчёта
  city: "Город",
  year: auto, // Можно поменять год, auto - текущий год
  text-size: (default: 14pt, small: 10pt), // Можно указать размеры текста
  indent: 1.25cm, // Можно указать отступ
  hide-title: true, // Убрать ли титульный лист
  title-footer-align: center, // Выравнивание города и года на титульном листе
  pagination-align: center, // Выравнивание номера страницы
  margin: (
    left: 30mm,
    right: 15mm,
    top: 20mm,
    bottom: 20mm,
  ), // Отступы страницы
  add-pagebreaks: false, // Убрать ли разрывы страниц
)

#set par(spacing: 12pt)

#outline()

#pagebreak()

= Цель работы

Цель работы:  Построить модели линейной, полиномиальной (полином 2 или 3 степени), логистической и ридж-регрессии для прогнозирования успеваемости студентов.

= Набор данных

Источник набора данных: https://www.kaggle.com/datasets/stealthtechnologies/predict-student-performance-dataset/data

Выходная переменная (целевая):
- `Grades`: Итоговая оценка успеваемости студента.
\

Признаки набора данных:
- `Study Hours`: Среднее количество часов в день, затрачиваемых на учебу (числовой).
- `Sleep Hours`: Среднее количество часов в день, затрачиваемых на сон (числовой).
- `Socioeconomic Score`: Нормализованный балл (0-1), указывающий на социально-экономическое положение студента.
- `Attendance (%)`: Процент посещенных студентом занятий (числовой).

= Предварительная обработка данных

- Пропущенные значения: В данных нет пропусков (проверено с помощью `isnull().sum()`).
- Исключены: `Posted On`, `Floor`, `Area Locality` (из-за большого количества уникальных значений).
- Кодирование символьных данных: Категориальные признаки (`Area Type`, `City`, `Furnishing Status`, `Tenant Preferred`, `Point of Contact`) закодированы с помощью `OneHotEncoder`.

= Разделение набора данных

Набор данных разделен на обучающую (80%) и тестовую (20%) выборки с помощью `train_test_split`.

= Модели машинного обучения
Полученные модели:
- Линейная регрессия: `LinearRegression`.
- Полиномиальная регрессия 2-ой степени: `PolynomialFeatures(degree=2)` + `LinearRegression`.
- Полиномиальная регрессия 3-ей степени: `PolynomialFeatures(degree=3)` + `LinearRegression`.
- Ридж-регрессия: `Ridge` (alpha=1.0).
- Ридж-регрессия + полином??: `PolynomialFeatures(degree=3)` + `Ridge` (alpha=1.0).

= График регрессии, прогнозные значения и уравнение регрессии

График: Построен scatter plot для `Size` vs `Rent` с данными, тестовыми значениями и прогнозами линейной регрессии (matplotlib).

Уравнения регрессии (коэффициенты извлечены из моделей):

- Линейная: $ "Rent" = -18486.370 \
  + 5553.960 dot"Area Type_Built Area"
  - 1275.123 dot"Area Type_Carpet Area"\
  - 4278.837 dot"Area Type_Super Area"
  - 4874.722 dot"City_Bangalore" \
  - 12703.227 dot"City_Chennai"
  + 2349.352 dot"City_Delhi" \
  - 21727.989 dot"City_Hyderabad"
  - 7842.364 dot"City_Kolkata"
  + 44798.950 dot"City_Mumbai" \
  + 5569.976 dot"Furnishing Status_Furnished"
  - 3045.807 dot"Furnishing Status_Semi-Furnished" \
  - 2524.169 dot"Furnishing Status_Unfurnished"
  + 4079.037 dot"Tenant Preferred_Bachelors" \
  + 3307.130 dot"Tenant Preferred_Bachelors/Family"
  - 7386.167 dot"Tenant Preferred_Family" \
  - 5005.848 dot"Point of Contact_Contact Agent"
  + 19397.413 dot"Point of Contact_Contact Builder"\
  - 14391.565 dot"Point of Contact_Contact Owner"
  + 3669.642 dot"BHK" \
  + 36.602 dot"Size"
  + 11502.331 dot"Bathroom" $

= Оценка точности моделей

#table(
  columns: (auto, auto, auto, auto, auto),
  align: center,
  [*Модель*], [*R²*], [*RMSE*], [*MAE*], [*MSE*],
  [Линейная регрессия], [0.5205], [43717.0552], [22232.6300], [1911180916.2022],
  [Полиномиальная регрессия], [0.7958], [28528.0921], [14062.6489], [813852036.6120],
  [Ридж-регрессия], [0.5205], [43716.6342], [22222.5073], [1911144103.7330],
)

Полиномиальная модель показывает наилучшие результаты (высокий R², низкие ошибки).

= Заключение

В работе реализован регрессионный анализ для прогнозирования арендной платы. Полиномиальная регрессия степени 2 оказалась наиболее точной. Рекомендуется дальнейшая оптимизация (например, подбор гиперпараметров) для улучшения моделей.
