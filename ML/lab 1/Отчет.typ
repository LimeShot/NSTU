#set text(font: "Times New Roman", size: 14pt)
#show raw: set text(font: "Consolas", size: 12pt)
#set par(first-line-indent: 1cm, leading: 0.65em)

#show heading: it => {
  let size = 14pt
  text(size: size)[#it.body]
  set par(first-line-indent: 1cm)
}

#set page(
  margin: (x: 2cm, y: 2cm),
  numbering: "1",
)

// Настройка оглавления
#set outline(
  indent: auto,
  title: [Содержание],
)

#counter(page).update(2)

#v(2em) // Отступ перед содержанием
#outline() // Вставка оглавления
#pagebreak() // Новая страница после содержания

= 1. Цель работы

Цель работы: Разработать модели машинного обучения для прогнозирования арендной платы за жилье.

= 2. Набор данных

Источник набора данных: https://www.kaggle.com/datasets/iamsouravbanerjee/house-rent-prediction-dataset/data

Выходная переменная (целевая):
- `Rent`: (арендная плата).

Признаки набора данных:
- `BHK`: Количество спален, холлов и кухонь (числовой).
- `Size`: Площадь жилья (числовой).
- `Floor`: Этаж (категориальный).
- `Area Type`: Тип площади (категориальный).
- `Area Locality`: Район (категориальный).
- `City`: Город (категориальный).
- `Furnishing Status`: Статус мебелировки (категориальный).
- `Tenant Preferred`: Предпочтительный арендатор (категориальный).
- `Bathroom`: Количество ванных комнат (числовой).
- `Point of Contact`: Контакт (категориальный).

= 3. Предварительная обработка данных

- Пропущенные значения: В данных нет пропусков (проверено с помощью `isnull().sum()`).
- Исключены: `Posted On`, `Floor`, `Area Locality` (из-за большого количества уникальных значений).
- Кодирование символьных данных: Категориальные признаки (`Area Type`, `City`, `Furnishing Status`, `Tenant Preferred`, `Point of Contact`) закодированы с помощью `OneHotEncoder`.

= 4. Разделение набора данных

Набор данных разделен на обучающую (80%) и тестовую (20%) выборки с помощью `train_test_split`.

= 5. Модели машинного обучения
Полученные модели:
- Линейная регрессия: `LinearRegression`.
- Полиномиальная регрессия: `PolynomialFeatures(degree=2)` + `LinearRegression`.
- Ридж-регрессия: `Ridge` (alpha=1.0).

= 5. График регрессии, прогнозные значения и уравнение регрессии

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

= 7. Оценка точности моделей

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
