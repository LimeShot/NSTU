from calendar import monthrange
import json
from pathlib import Path
import matplotlib

matplotlib.use('Agg')

import matplotlib.pyplot as plt
import plotly.graph_objects as go
import plotly.tools as tls
import plotly.offline as pyo
from plotly.subplots import make_subplots

import pandas as pd
from django.shortcuts import render


class FirstClass:
    def __init__(self, a, b):
        self.a = a
        self.b = b


APP_DIR = Path(__file__).resolve().parent
ROOT_DIR = APP_DIR.parents[1]
STATIC_DATA_DIR = APP_DIR / 'static' / 'data'
DATA_FILE = STATIC_DATA_DIR / 'climatdata_GTK.csv'
DATA_PAGE_FILE = STATIC_DATA_DIR / 'climate_data_rapidapi.csv'
SPEI_ALL_FILE = STATIC_DATA_DIR / 'spei_all_stations.csv'
LAB2_STATION_FILE = STATIC_DATA_DIR / 'indices_station_17150.csv'
LAB2_FORECAST_FILE = STATIC_DATA_DIR / 'lab2_forecasts.csv'
LAB2_FUTURE_FORECAST_FILE = STATIC_DATA_DIR / 'lab2_future_forecasts.csv'
LAB2_METRICS_FILE = STATIC_DATA_DIR / 'lab2_metrics.csv'
LAB2_STATS_FILE = STATIC_DATA_DIR / 'lab2_statistics.json'
LAB2_ARIMA_SUMMARY_FILE = STATIC_DATA_DIR / 'lab2_arima_summary.txt'
LAB2_SARIMA_SUMMARY_FILE = STATIC_DATA_DIR / 'lab2_sarima_summary.txt'

MONTH_LABELS = {
    '1': 'январь',
    '2': 'февраль',
    '3': 'март',
    '4': 'апрель',
    '5': 'май',
    '6': 'июнь',
    '7': 'июль',
    '8': 'август',
    '9': 'сентябрь',
    '10': 'октябрь',
    '11': 'ноябрь',
    '12': 'декабрь',
}

MONTH_SHORT_LABELS = {
    '1': 'янв',
    '2': 'фев',
    '3': 'мар',
    '4': 'апр',
    '5': 'май',
    '6': 'июн',
    '7': 'июл',
    '8': 'авг',
    '9': 'сен',
    '10': 'окт',
    '11': 'ноя',
    '12': 'дек',
}

DATA_COLUMN_LABELS = {
    'station_id': 'ID станции',
    'country': 'Страна',
    'region': 'Регион',
    'Name': 'Код станции',
    'Name2': 'Название станции',
    'lat': 'Широта',
    'lon': 'Долгота',
    'elevation': 'Высота',
    'height': 'Высота',
    'date': 'Дата',
    'year': 'Год',
    'tem_active': 'Сумма активных температур',
    'sum_osadki': 'Сумма осадков',
    'GTK': 'ГТК',
    'SPEI3': 'SPEI3',
    'SPEI6': 'SPEI6',
    'SPEI9': 'SPEI9',
    'SPEI12': 'SPEI12',
}


def _first_existing_path(*paths):
    for path in paths:
        if path.exists():
            return path
    return paths[0]


def _data_column_label(column_name):
    if column_name in DATA_COLUMN_LABELS:
        return DATA_COLUMN_LABELS[column_name]

    if column_name.startswith('Tem') and column_name[3:] in MONTH_LABELS:
        return f'Температура, {MONTH_LABELS[column_name[3:]]}'

    if column_name.startswith('Os') and column_name[2:] in MONTH_LABELS:
        return f'Осадки, {MONTH_LABELS[column_name[2:]]}'

    return column_name


def _format_table_value(value):
    if pd.isna(value):
        return ''

    if isinstance(value, pd.Timestamp):
        return value.strftime('%Y-%m-%d')

    if isinstance(value, float):
        formatted = f'{value:.3f}'.rstrip('0').rstrip('.')
        return formatted if formatted != '-0' else '0'

    return value


def _load_monthly_spei(spei_file):
    if not spei_file.exists():
        return pd.DataFrame()

    spei_data = pd.read_csv(spei_file, dtype={'station_id': str})
    if 'date' not in spei_data.columns or 'station_id' not in spei_data.columns:
        return pd.DataFrame()

    spei_columns = [column for column in ('SPEI3', 'SPEI6', 'SPEI9', 'SPEI12') if column in spei_data.columns]
    if not spei_columns:
        return pd.DataFrame()

    spei_data['date'] = pd.to_datetime(spei_data['date'], errors='coerce')
    spei_data = spei_data.dropna(subset=['date'])

    for column in spei_columns:
        spei_data[column] = pd.to_numeric(spei_data[column], errors='coerce')

    return spei_data[['date', 'station_id', *spei_columns]]


def _add_gtk_columns(climate_data):
    temp_months = {
        int(column[3:]): column
        for column in climate_data.columns
        if column.startswith('Tem') and column[3:].isdigit()
    }
    osadki_months = {
        int(column[2:]): column
        for column in climate_data.columns
        if column.startswith('Os') and column[2:].isdigit()
    }
    paired_months = sorted(set(temp_months) & set(osadki_months))
    if not paired_months or 'year' not in climate_data.columns:
        return climate_data

    climate_data = climate_data.copy()
    climate_data['tem_active'] = 0.0
    climate_data['sum_osadki'] = 0.0

    for month in paired_months:
        temp_col = temp_months[month]
        os_col = osadki_months[month]
        temp = pd.to_numeric(climate_data[temp_col], errors='coerce')
        osadki = pd.to_numeric(climate_data[os_col], errors='coerce')
        days = climate_data['year'].apply(
            lambda year: monthrange(int(year), month)[1] if pd.notna(year) else pd.NA
        )
        active_period = temp.notna() & osadki.notna() & (temp > 10)

        climate_data['tem_active'] += temp.where(active_period, 0) * days.where(active_period, 0)
        climate_data['sum_osadki'] += osadki.where(active_period, 0)

    gtk_raw = climate_data['sum_osadki'] / (0.1 * climate_data['tem_active'])
    climate_data['GTK'] = gtk_raw.round(2).where(climate_data['tem_active'] > 0)
    return climate_data


def _table_column_label(column_name, selected_data_type):
    if selected_data_type == 'temperature' and column_name.startswith('Tem') and column_name[3:] in MONTH_LABELS:
        return MONTH_SHORT_LABELS[column_name[3:]]

    if selected_data_type == 'precipitation' and column_name.startswith('Os') and column_name[2:] in MONTH_LABELS:
        return MONTH_SHORT_LABELS[column_name[2:]]

    return _data_column_label(column_name)


def _table_payload(data_frame, selected_data_type=None):
    columns = [
        {'name': column, 'label': _table_column_label(column, selected_data_type)}
        for column in data_frame.columns
    ]
    rows = [
        [_format_table_value(row[column]) for column in data_frame.columns]
        for _, row in data_frame.iterrows()
    ]
    return columns, rows


def _data_type_options():
    return [
        {'value': 'temperature', 'label': 'Температура'},
        {'value': 'precipitation', 'label': 'Осадки'},
        {'value': 'gtk', 'label': 'ГТК'},
        {'value': 'spei', 'label': 'SPEI'},
    ]


def _existing_columns(data_frame, requested_columns):
    return [column for column in requested_columns if column in data_frame.columns]


def _month_columns(data_frame, prefix):
    return [
        column
        for column in data_frame.columns
        if column.startswith(prefix) and column[len(prefix):].isdigit()
    ]


def _select_columns(data_frame, selected_data_type):
    if data_frame.empty:
        return data_frame

    if selected_data_type == 'spei':
        columns = _existing_columns(data_frame, ['date', 'SPEI3', 'SPEI6', 'SPEI9', 'SPEI12'])
    elif selected_data_type == 'precipitation':
        columns = _existing_columns(data_frame, ['year']) + _month_columns(data_frame, 'Os')
    elif selected_data_type == 'gtk':
        columns = _existing_columns(data_frame, ['year', 'tem_active', 'sum_osadki', 'GTK'])
    else:
        columns = _existing_columns(data_frame, ['year']) + _month_columns(data_frame, 'Tem')

    return data_frame[columns]


def _station_options(climate_data):
    station_columns = [column for column in ('station_id', 'Name2', 'Name', 'country', 'region') if column in climate_data.columns]
    if 'station_id' not in station_columns:
        return []

    stations = (
        climate_data[station_columns]
        .drop_duplicates(subset=['station_id'])
        .sort_values(['Name2', 'station_id'], na_position='last')
    )
    options = []
    for _, station in stations.iterrows():
        name = station.get('Name2') or station.get('Name') or station['station_id']
        code = station.get('Name')
        label_parts = [str(name)]
        if code and code != name:
            label_parts.append(str(code))
        label_parts.append(str(station['station_id']))
        options.append({
            'value': station['station_id'],
            'label': ' / '.join(label_parts),
        })
    return options


def _selected_station_label(station_options, selected_station):
    for station in station_options:
        if station['value'] == selected_station:
            return station['label']
    return 'Все станции'


def _station_metadata(station_meta, selected_station):
    if station_meta.empty or not selected_station:
        return []

    station_rows = station_meta[station_meta['station_id'] == selected_station]
    if station_rows.empty:
        return []

    station = station_rows.iloc[0]
    fields = [
        ('station_id', 'ID станции'),
        ('Name2', 'Название'),
        ('Name', 'Код'),
        ('country', 'Страна'),
        ('region', 'Регион'),
        ('lat', 'Широта'),
        ('lon', 'Долгота'),
        ('elevation', 'Высота'),
        ('height', 'Высота'),
    ]
    metadata = []
    for column, label in fields:
        if column in station.index:
            value = _format_table_value(station[column])
            if value != '':
                metadata.append({'label': label, 'value': value})
    return metadata


def _station_summary(station_meta, selected_station):
    if station_meta.empty or not selected_station:
        return None

    station_rows = station_meta[station_meta['station_id'] == selected_station]
    if station_rows.empty:
        return None

    station = station_rows.iloc[0]
    name = _format_table_value(station.get('Name2', '')) or selected_station
    code = _format_table_value(station.get('Name', ''))
    country = _format_table_value(station.get('country', ''))
    region = _format_table_value(station.get('region', ''))
    lat = _format_table_value(station.get('lat', ''))
    lon = _format_table_value(station.get('lon', ''))
    elevation = _format_table_value(station.get('elevation', '')) or _format_table_value(station.get('height', ''))

    subtitle_parts = [part for part in (code, f'ID {selected_station}') if part]
    details = []
    if country or region:
        details.append({'label': 'Локация', 'value': ' / '.join(part for part in (country, region) if part)})
    if lat or lon:
        details.append({'label': 'Координаты', 'value': ', '.join(part for part in (lat, lon) if part)})
    if elevation:
        details.append({'label': 'Высота', 'value': f'{elevation} м'})

    return {
        'name': name,
        'subtitle': ' · '.join(subtitle_parts),
        'details': details,
    }


def index(request):
    return render(request, 'chumakov/index.html')


def about(request):
    context = {
        'faculty': 'Автоматики  и вычислительной техники',
        'department': 'Кафедра систем сбора и обработки информации',
        'course': 'Моделирование процессов и объектов',
        'project_name': 'Знакомство с Django. Математические и графические модели.',
        'title': 'О студенте',
        'grouplist': ['АТМ-25'],
        'langs': ['Python', 'C#', 'C++', 'C'],
        'work': ['Django', 'Django Rest API', 'Flask', 'FastAPI'],
        'set': (1, 2, 3, 4),
        'year': (2023, 2025, 2026, 2027),
        'dict': {'name': 'Илья', 'last_name': 'Чумаков', 'age': 22},
        'obj': FirstClass(20, 35),
    }
    return render(request, 'chumakov/about.html', context=context)


def data(request):
    data_file = _first_existing_path(DATA_PAGE_FILE, DATA_FILE)
    spei_file = SPEI_ALL_FILE
    data_type_options = _data_type_options()
    selected_data_type = (
        request.GET.get('data')
        or ('spei' if request.GET.get('dataset') == 'spei' else request.GET.get('columns'))
        or 'temperature'
    )
    if selected_data_type not in {option['value'] for option in data_type_options}:
        selected_data_type = 'temperature'
    selected_station = request.GET.get('station', '')

    if not data_file.exists():
        return render(
            request,
            'chumakov/data.html',
            context={
                'columns': [],
                'rows': [],
                'station_options': [],
                'data_type_options': data_type_options,
                'selected_data_type': selected_data_type,
                'selected_station': selected_station,
                'error': f'Файл не найден: {data_file}',
            },
        )

    climate_data = pd.read_csv(data_file, dtype={'station_id': str})
    if 'year' in climate_data.columns:
        climate_data['year'] = pd.to_numeric(climate_data['year'], errors='coerce').astype('Int64')
    climate_data = _add_gtk_columns(climate_data)

    station_options = _station_options(climate_data)
    valid_station_ids = {station['value'] for station in station_options}
    if selected_station not in valid_station_ids:
        selected_station = station_options[0]['value'] if station_options else ''

    station_meta_columns = [
        column
        for column in ('station_id', 'country', 'region', 'Name', 'Name2', 'lat', 'lon', 'elevation', 'height')
        if column in climate_data.columns
    ]
    station_meta = climate_data[station_meta_columns].drop_duplicates(subset=['station_id'])

    selected_station_metadata = _station_metadata(station_meta, selected_station)
    selected_station_summary = _station_summary(station_meta, selected_station)
    monthly_spei = _load_monthly_spei(spei_file)

    if selected_station:
        climate_data = climate_data[climate_data['station_id'] == selected_station].copy()
        if not monthly_spei.empty:
            monthly_spei = monthly_spei[monthly_spei['station_id'] == selected_station].copy()

    if selected_data_type == 'spei':
        table_data = monthly_spei
        source_file = spei_file.name if spei_file.exists() else None
        table_title = 'SPEI'
        table_note = 'SPEI показан отдельно от основных климатических данных в исходном помесячном виде.'
    else:
        table_data = climate_data
        source_file = data_file.name
        table_title = next(option['label'] for option in data_type_options if option['value'] == selected_data_type)
        table_note = 'Основные климатические данные для выбранной станции. Метаданные вынесены выше таблицы.'

    sort_columns = [column for column in ('station_id', 'year', 'date') if column in table_data.columns]
    if sort_columns:
        table_data = table_data.sort_values(sort_columns, kind='stable')
    table_data = _select_columns(table_data, selected_data_type)

    columns, rows = _table_payload(table_data, selected_data_type)

    context = {
        'columns': columns,
        'rows': rows,
        'row_count': len(rows),
        'station_count': table_data['station_id'].nunique() if 'station_id' in table_data.columns else 0,
        'source_file': source_file,
        'spei_source_file': spei_file.name if spei_file.exists() else None,
        'station_options': station_options,
        'data_type_options': data_type_options,
        'selected_data_type': selected_data_type,
        'selected_station': selected_station,
        'selected_station_label': _selected_station_label(station_options, selected_station),
        'selected_station_metadata': selected_station_metadata,
        'selected_station_summary': selected_station_summary,
        'table_title': table_title,
        'table_note': table_note,
    }
    return render(request, 'chumakov/data.html', context=context)





def graph_temp_year(request):
    year = 1970
    climate_data = pd.read_csv(DATA_FILE)
    data = climate_data[climate_data['year'] == year].iloc[0]
    months = ['Янв','Фев','Мар','Апр','Май','Июн','Июл','Авг','Сен','Окт','Ноя','Дек']

    fig, ax = plt.subplots(figsize=(12, 6))
    ax.plot(months, data[['Tem1','Tem2','Tem3','Tem4','Tem5','Tem6','Tem7','Tem8','Tem9','Tem10','Tem11','Tem12']],
            'o-r', lw=3, label='Температура (°C)', alpha=0.8)
    ax.plot(months, data[['Os1','Os2','Os3','Os4','Os5','Os6','Os7','Os8','Os9','Os10','Os11','Os12']],
            's-b', lw=3, label='Осадки (мм)', alpha=0.8)
    ax.set_title(f'Температура и осадки за {year} год', fontsize=16)
    ax.set_ylabel('Значение', fontsize=16)
    ax.set_xlabel('Номер месяца', fontsize=16)
    ax.grid(True)
    ax.legend()

    # Конвертируем в Plotly
    plot_div = _matplotlib_plot_div(fig, include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {'plot_div': plot_div, 'title': f'График 1 — {year} год'})


def graph_temp_active(request):
    year = 1970
    climate_data = pd.read_csv(DATA_FILE)
    data = climate_data[climate_data['year'] == year].iloc[0]

    months = ['Май', 'Июн', 'Июл', 'Авг']
    temp = data[['Tem5','Tem6','Tem7','Tem8']].values
    prec = data[['Os5','Os6','Os7','Os8']].values

    days_in_month = [31, 30, 31, 31]  # Май, Июнь, Июль, Август

    activ_temp = [temp[i]*days_in_month[i] if temp[i] > 10 else 0 for i in range(len(temp))]

    fig, ax = plt.subplots(figsize=(12, 6))
    ax.plot(months, temp, 'o-r', lw=3, label='Температура воздуха, °C', alpha=0.9)
    ax.plot(months, prec, 's-b', lw=3, label='Осадки, мм', alpha=0.9)
    ax.plot(months, activ_temp, 'd-g', lw=3, label='Сумма активных температур, °C*дни', alpha=0.9)

    ax.set_title(f'Температура, осадки и сумма активных температур за {year} год', fontsize=16)
    ax.set_xlabel('Месяц', fontsize=16)
    ax.set_ylabel('Значение', fontsize=16)
    ax.grid(True)
    ax.legend()

    plot_div = _matplotlib_plot_div(fig, include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': f'График 2 — Сумма активных температур (май–август) за {year} год'
    })


def graph3(request):
    df = pd.read_csv(DATA_FILE)
    fig, ax = plt.subplots(figsize=(12, 6))
    ax.plot(df['year'], df['GTK'], 'o-', lw=3, label='ГТК')
    ax.set_title('Гидротермический коэффициент (ГТК) по годам', fontsize=16)
    ax.set_xlabel('Год', fontsize=16)
    ax.set_ylabel('ГТК', fontsize=16)
    ax.grid(True)
    ax.legend()

    plot_div = _matplotlib_plot_div(fig, include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': 'График 3 — Гидротермический коэффициент ГТК'
    })


def graph4(request):
    year = 1970
    df = pd.read_csv(DATA_FILE)
    data = df[df['year'] == year].iloc[0]

    months = ['Янв', 'Фев', 'Мар', 'Апр', 'Май', 'Июн', 'Июл', 'Авг', 'Сен', 'Окт', 'Ноя', 'Дек']
    temp = data[['Tem1','Tem2','Tem3','Tem4','Tem5','Tem6','Tem7','Tem8','Tem9','Tem10','Tem11','Tem12']].values
    prec = data[['Os1','Os2','Os3','Os4','Os5','Os6','Os7','Os8','Os9','Os10','Os11','Os12']].values

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7))
    ax1.bar(months, temp, color='red', alpha=0.7)
    ax1.set_title(f'Температура по месяцам за {year} год', fontsize=14)
    ax1.set_ylabel('Температура, °C', fontsize=16)
    ax1.set_xlabel('Месяц', fontsize=16)
    ax1.grid(True, axis='y')

    ax2.bar(months, prec, color='blue', alpha=0.7)
    ax2.set_title(f'Осадки по месяцам за {year} год', fontsize=14)
    ax2.set_ylabel('Осадки, мм', fontsize=16)
    ax2.set_xlabel('Месяц', fontsize=16)
    ax2.grid(True, axis='y')

    plt.tight_layout()
    plot_div = _matplotlib_plot_div(fig, include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': f'График 4 — Гистограммы за {year} год'
    })


def graph5(request):
    df = pd.read_csv(DATA_FILE)
    months = ['Янв', 'Фев', 'Мар', 'Апр', 'Май', 'Июн', 'Июл', 'Авг', 'Сен', 'Окт', 'Ноя', 'Дек']

    # Средние по всем годам
    temp_mean = df[['Tem1','Tem2','Tem3','Tem4','Tem5','Tem6','Tem7','Tem8','Tem9','Tem10','Tem11','Tem12']].mean().values
    prec_mean = df[['Os1','Os2','Os3','Os4','Os5','Os6','Os7','Os8','Os9','Os10','Os11','Os12']].mean().values

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7))
    ax1.bar(months, temp_mean, color='red', alpha=0.7)
    ax1.set_title('Среднемноголетняя температура по месяцам', fontsize=14)
    ax1.set_ylabel('Температура, °C', fontsize=16)
    ax1.set_xlabel('Месяц', fontsize=16)
    ax1.grid(True, axis='y')

    ax2.bar(months, prec_mean, color='blue', alpha=0.7)
    ax2.set_title('Среднемноголетние осадки по месяцам', fontsize=14)
    ax2.set_ylabel('Осадки, мм', fontsize=16)
    ax2.set_xlabel('Месяц', fontsize=16)
    ax2.grid(True, axis='y')

    plt.tight_layout()
    plot_div = _matplotlib_plot_div(fig, include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': 'График 5 — Среднемноголетние гистограммы'
    })


def graph6(request):
    df = pd.read_csv(DATA_FILE)

    temp_cols = [col for col in df.columns if col.startswith('Tem')]
    osadki_cols = [col for col in df.columns if col.startswith('Os')]

    osadki_nan = df[osadki_cols].isna().sum(axis=1)
    temp_nan = df[temp_cols].isna().sum(axis=1)

    df["tem_active"] = 0.0

    df = df[(osadki_nan <= 6) & (temp_nan <= 6)]
    for temp_col, os_col in zip(temp_cols, osadki_cols):
        df[temp_col] = df[temp_col].fillna(df[temp_col].mean())
        df[os_col] = df[os_col].fillna(df[os_col].mean())

        active_period = df[temp_col] > 10
        days = df['year'].astype('Int64').apply(lambda y: monthrange(int(y), int(temp_col[3:]))[1] if pd.notna(y) else pd.NA)

        df["tem_active"] += df[temp_col].where(active_period, 0) * days

    fig, ax = plt.subplots(figsize=(12, 6))
    ax.hist(df['tem_active'], bins=15, color='green', alpha=0.8, edgecolor='black')
    ax.set_title('Распределение суммы активных температур (май–август)', fontsize=16)
    ax.set_xlabel('Сумма активных температур, °C', fontsize=16)
    ax.set_ylabel('Количество лет', fontsize=16)
    ax.grid(True)

    plot_div = _matplotlib_plot_div(fig, include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': 'График 6 — Распределение суммы активных температур (май–август)'
    })


def _plotly_div(fig, include_plotlyjs=False):
    fig.update_layout(autosize=True, width=None)
    return pyo.plot(
        fig,
        output_type='div',
        include_plotlyjs=include_plotlyjs,
        config={'responsive': True, 'displayModeBar': False},
    )


def _matplotlib_plot_div(fig, include_plotlyjs=False):
    plotly_fig = tls.mpl_to_plotly(fig)
    plotly_fig.update_layout(autosize=True, width=None)
    return _plotly_div(plotly_fig, include_plotlyjs=include_plotlyjs)


LAB2_MODEL_ORDER = ['ARIMA', 'SARIMA', 'XGBoost', 'LSTM']


def _lab2_model_sort_key(model_name):
    try:
        return LAB2_MODEL_ORDER.index(model_name)
    except ValueError:
        return len(LAB2_MODEL_ORDER)


def modeling(request):
    required_files = [
        LAB2_STATION_FILE,
        LAB2_FORECAST_FILE,
        LAB2_FUTURE_FORECAST_FILE,
        LAB2_METRICS_FILE,
        LAB2_STATS_FILE,
        LAB2_ARIMA_SUMMARY_FILE,
        LAB2_SARIMA_SUMMARY_FILE,
    ]
    missing = [path.name for path in required_files if not path.exists()]
    labels = {
        'page_title': 'Моделинг',
        'data_title': 'Данные для расчета',
        'data_note': 'Результаты обучения моделей на данных станции 17150.',
        'station': 'Станция',
        'spei_period': 'Ряд SPEI3',
        'train_end': 'Обучение до',
        'test_start': 'Тест с',
        'future_period': 'Прогноз на 2 года',
        'describe_title': 'Описательная статистика SPEI3',
        'tests_title': 'Статистические тесты',
        'series': 'Ряд',
        'test': 'Тест',
        'statistic': 'Статистика',
        'conclusion': 'Вывод',
        'metrics_title': 'Метрики прогноза на тесте',
        'model': 'Модель',
        'arima_summary': 'Результаты обучения ARIMA',
        'sarima_summary': 'Результаты обучения SARIMA',
        'forecast': 'прогноз',
    }
    if missing:
        return render(request, 'chumakov/lab2.html', {
            'title': labels['page_title'],
            'labels': labels,
            'error': 'Не найдены файлы результатов: ' + ', '.join(missing) + '. Запустите lab2_generate_results.py из корня проекта.',
        })

    station = pd.read_csv(LAB2_STATION_FILE, parse_dates=['date'])
    station_spei = station[['date', 'SPEI3']].dropna()
    forecasts = pd.read_csv(LAB2_FORECAST_FILE, parse_dates=['date'])
    future_forecasts = pd.read_csv(LAB2_FUTURE_FORECAST_FILE, parse_dates=['date'])
    metrics = pd.read_csv(LAB2_METRICS_FILE)
    metrics = (
        metrics.assign(_model_order=metrics['model'].map(_lab2_model_sort_key))
        .sort_values('_model_order')
        .drop(columns=['_model_order'])
    )
    best_rmse = metrics['RMSE'].min()
    metrics['is_best'] = metrics['RMSE'].eq(best_rmse)
    with LAB2_STATS_FILE.open(encoding='utf-8') as file:
        stats = json.load(file)
    arima_summary = LAB2_ARIMA_SUMMARY_FILE.read_text(encoding='utf-8')
    sarima_summary = LAB2_SARIMA_SUMMARY_FILE.read_text(encoding='utf-8')

    rolling_mean = station_spei['SPEI3'].rolling(window=12).mean()
    rolling_std = station_spei['SPEI3'].rolling(window=12).std()

    spei_fig = make_subplots(rows=2, cols=1, shared_xaxes=True, vertical_spacing=0.12)
    spei_fig.add_trace(go.Scatter(x=station_spei['date'], y=station_spei['SPEI3'], name='SPEI3'), row=1, col=1)
    spei_fig.add_trace(go.Scatter(x=station_spei['date'], y=rolling_mean, name='Скользящее среднее, 12 мес.'), row=2, col=1)
    spei_fig.add_trace(go.Scatter(x=station_spei['date'], y=rolling_std, name='Скользящее std, 12 мес.'), row=2, col=1)
    spei_fig.update_layout(title='SPEI3 и скользящая статистика, станция 17150', height=650)

    acf_values = pd.DataFrame(stats['acf'])
    pacf_values = pd.DataFrame(stats['pacf'])
    corr_fig = make_subplots(rows=1, cols=2, subplot_titles=('ACF первой разности SPEI3', 'PACF первой разности SPEI3'))
    corr_confidence = 1.96 / (max(len(station_spei['SPEI3'].diff().dropna()), 1) ** 0.5)
    corr_fig.add_trace(go.Bar(x=acf_values['lag'], y=acf_values['value'], name='ACF'), row=1, col=1)
    corr_fig.add_trace(go.Bar(x=pacf_values['lag'], y=pacf_values['value'], name='PACF'), row=1, col=2)
    corr_fig.add_hrect(y0=-corr_confidence, y1=corr_confidence, fillcolor='rgba(31,95,170,0.13)', line_width=0, layer='below', row=1, col=1)
    corr_fig.add_hrect(y0=-corr_confidence, y1=corr_confidence, fillcolor='rgba(31,95,170,0.13)', line_width=0, layer='below', row=1, col=2)
    for col in (1, 2):
        corr_fig.add_hline(y=corr_confidence, line_dash='dot', line_color='rgba(31,95,170,0.55)', line_width=1, row=1, col=col)
        corr_fig.add_hline(y=-corr_confidence, line_dash='dot', line_color='rgba(31,95,170,0.55)', line_width=1, row=1, col=col)
    corr_fig.update_yaxes(range=[-1, 1])
    corr_fig.update_layout(height=430, showlegend=False)

    model_plots = []
    test_start_date = pd.to_datetime(stats['test_start'])
    history_tail = station_spei[station_spei['date'] >= test_start_date]
    model_names = sorted(forecasts['model'].unique(), key=_lab2_model_sort_key)
    for model_name in model_names:
        model_data = forecasts[forecasts['model'] == model_name].sort_values('date')
        model_future = future_forecasts[future_forecasts['model'] == model_name].sort_values('date')
        forecast_anchor_date = model_data['date'].iloc[-1]
        forecast_anchor_value = model_data['predicted'].iloc[-1]
        future_dates = pd.concat([pd.Series([forecast_anchor_date]), model_future['date']], ignore_index=True)
        future_values = pd.concat([pd.Series([forecast_anchor_value]), model_future['predicted']], ignore_index=True)
        model_fig = go.Figure()
        model_fig.add_trace(go.Scatter(x=history_tail['date'], y=history_tail['SPEI3'], mode='lines', name='Факт SPEI3'))
        model_fig.add_trace(go.Scatter(x=model_data['date'], y=model_data['predicted'], mode='lines', name='Прогноз на тесте'))
        model_fig.add_trace(go.Scatter(x=future_dates, y=future_values, mode='lines', name='Прогноз на 24 мес.'))
        model_fig.update_layout(title=f'{model_name}: прогноз SPEI3 на тесте и на 2 года вперед', height=430)
        model_plots.append({'model': model_name, 'plot': _plotly_div(model_fig)})

    residual_fig = go.Figure()
    for model_name in model_names:
        model_data = forecasts[forecasts['model'] == model_name].sort_values('date')
        model_data = model_data.sort_values('date')
        residual_fig.add_trace(go.Scatter(x=model_data['date'], y=model_data['residual'], mode='lines', name=model_name))
    residual_fig.add_hline(y=0, line_dash='dash', line_color='gray')
    residual_fig.update_layout(title='Остатки моделей на тестовом периоде', height=420)

    conclusion_names = {'stationary': 'стационарен', 'non-stationary': 'нестационарен'}
    series_names = {'SPEI3': 'SPEI3'}
    tests = []
    for row in stats['tests']:
        translated = row.copy()
        translated['series'] = series_names.get(translated['series'], translated['series'])
        translated['conclusion'] = conclusion_names.get(translated['conclusion'], translated['conclusion'])
        tests.append(translated)

    describe_labels = {
        'count': 'Количество наблюдений',
        'mean': 'Среднее',
        'std': 'Стандартное отклонение',
        'min': 'Минимум',
        '25%': '25-й процентиль',
        '50%': 'Медиана',
        '75%': '75-й процентиль',
        'max': 'Максимум',
    }
    describe = {describe_labels.get(name, name): value for name, value in stats['spei3_describe'].items()}
    notebook_arima_plots = [
        {
            'model': 'ARIMA',
            'plots': [
                {
                    'title': 'Диагностика обучения ARIMA',
                    'src': 'chumakov/lab2_notebook/arima_diagnostics.png',
                },
                {
                    'title': 'Остатки ARIMA',
                    'src': 'chumakov/lab2_notebook/arima_residuals.png',
                },
                {
                    'title': 'Прогноз ARIMA на тестовом периоде',
                    'src': 'chumakov/lab2_notebook/arima_forecast.png',
                },
            ],
        },
        {
            'model': 'SARIMA',
            'plots': [
                {
                    'title': 'Диагностика обучения SARIMA',
                    'src': 'chumakov/lab2_notebook/sarima_diagnostics.png',
                },
                {
                    'title': 'Остатки SARIMA',
                    'src': 'chumakov/lab2_notebook/sarima_residuals.png',
                },
                {
                    'title': 'Прогноз SARIMA на тестовом периоде',
                    'src': 'chumakov/lab2_notebook/sarima_forecast.png',
                },
            ],
        },
    ]

    context = {
        'title': labels['page_title'],
        'labels': labels,
        'station_id': stats['station_id'],
        'series_start': stats['series_start'],
        'series_end': stats['series_end'],
        'train_end': stats['train_end'],
        'test_start': stats['test_start'],
        'future_start': stats['future_start'],
        'future_end': stats['future_end'],
        'describe': describe,
        'tests': tests,
        'metrics': metrics.to_dict('records'),
        'notebook_arima_plots': notebook_arima_plots,
        'arima_summary': arima_summary,
        'sarima_summary': sarima_summary,
        'spei_plot': _plotly_div(spei_fig, include_plotlyjs=True),
        'corr_plot': _plotly_div(corr_fig),
        'model_plots': model_plots,
        'residual_plot': _plotly_div(residual_fig),
    }
    return render(request, 'chumakov/lab2.html', context)
