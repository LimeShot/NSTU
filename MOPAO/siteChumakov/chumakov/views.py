from calendar import monthrange
import json
from pathlib import Path
import matplotlib

matplotlib.use('Agg')

import matplotlib.pyplot as plt
import plotly.tools as tls
import plotly.offline as pyo

import pandas as pd
from django.shortcuts import render


class FirstClass:
    def __init__(self, a, b):
        self.a = a
        self.b = b


APP_DIR = Path(__file__).resolve().parent
DATA_FILE = APP_DIR / 'static' / 'data' / 'climatdata_GTK.csv'


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
    if not DATA_FILE.exists():
        return render(request, 'chumakov/data.html', context={'d': [], 'error': f'Файл не найден: {DATA_FILE}'})

    climate_data = pd.read_csv(DATA_FILE)
    json_records = climate_data.reset_index().to_json(orient='records')
    records = json.loads(json_records)
    return render(request, 'chumakov/data.html', context={'d': records})


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
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
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
    
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
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
    
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
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
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
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
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
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
    
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': 'График 6 — Распределение суммы активных температур (май–август)'
    })

