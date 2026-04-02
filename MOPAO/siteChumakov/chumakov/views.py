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
    ax.set_ylabel('Значение')
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

    months = ['Янв', 'Фев', 'Мар', 'Апр', 'Май', 'Июн', 'Июл', 'Авг', 'Сен', 'Окт', 'Ноя', 'Дек']
    temp = data[['Tem1','Tem2','Tem3','Tem4','Tem5','Tem6','Tem7','Tem8','Tem9','Tem10','Tem11','Tem12']].values
    prec = data[['Os1','Os2','Os3','Os4','Os5','Os6','Os7','Os8','Os9','Os10','Os11','Os12']].values

    fig, ax = plt.subplots(figsize=(12, 6))
    ax.plot(months, temp, 'o-r', lw=3, label='Температура воздуха, °C', alpha=0.9)
    ax.plot(months, prec, 's-b', lw=3, label='Осадки, мм', alpha=0.9)
    # Добавляем сумму активных температур как горизонтальную линию (масштаб разный, поэтому отдельно)
    ax.axhline(y=data['tem_active']/10, color='green', linestyle='--', lw=2, label=f'Сумма активных T (май–авг) = {int(data["tem_active"])} °C')
    
    ax.set_title(f'Температура, осадки и сумма активных температур за {year} год', fontsize=16)
    ax.set_xlabel('Месяц')
    ax.set_ylabel('Значение')
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
    ax.plot(df['year'], df['GTK'], 'o-', color='purple', lw=3, label='ГТК')
    ax.set_title('Гидротермический коэффициент (ГТК) по годам', fontsize=16)
    ax.set_xlabel('Год')
    ax.set_ylabel('ГТК')
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

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))
    ax1.bar(months, temp, color='red', alpha=0.7)
    ax1.set_title(f'Температура по месяцам за {year} год', fontsize=14)
    ax1.set_ylabel('Температура, °C')
    ax1.grid(True, axis='y')

    ax2.bar(months, prec, color='blue', alpha=0.7)
    ax2.set_title(f'Осадки по месяцам за {year} год', fontsize=14)
    ax2.set_ylabel('Осадки, мм')
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

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))
    ax1.bar(months, temp_mean, color='red', alpha=0.7)
    ax1.set_title('Среднемноголетняя температура по месяцам', fontsize=14)
    ax1.set_ylabel('Температура, °C')
    ax1.grid(True, axis='y')

    ax2.bar(months, prec_mean, color='blue', alpha=0.7)
    ax2.set_title('Среднемноголетние осадки по месяцам', fontsize=14)
    ax2.set_ylabel('Осадки, мм')
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
    
    fig, ax = plt.subplots(figsize=(12, 6))
    ax.hist(df['tem_active'], bins=15, color='green', alpha=0.8, edgecolor='black')
    ax.set_title('Распределение суммы активных температур (май–август)', fontsize=16)
    ax.set_xlabel('Сумма активных температур, °C')
    ax.set_ylabel('Количество лет')
    ax.grid(True)
    
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': 'График 6 — Распределение суммы активных температур (май–август)'
    })

def graph7(request):
    df = pd.read_csv(DATA_FILE)
    
    fig, ax = plt.subplots(figsize=(12, 6))
    ax.hist(df['tem_active'], bins=15, color='green', alpha=0.8, edgecolor='black')
    ax.set_title('Распределение суммы активных температур (май–август)', fontsize=16)
    ax.set_xlabel('Сумма активных температур, °C')
    ax.set_ylabel('Количество лет')
    ax.grid(True)
    
    plotly_fig = tls.mpl_to_plotly(fig)
    plot_div = pyo.plot(plotly_fig, output_type='div', include_plotlyjs=True)
    plt.close(fig)
    return render(request, 'chumakov/graph.html', {
        'plot_div': plot_div,
        'title': 'График 6 — Распределение суммы активных температур (май–август)'
    })

