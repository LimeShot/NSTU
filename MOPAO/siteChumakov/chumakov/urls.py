from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('about/', views.about, name='about'),
    path('data/', views.data, name='data'),
    # Дальше добавите пути для графиков (см. пункт 9)
    path('graph1/', views.graph_temp_year, name='graph'),
    path('graph2/', views.graph_temp_active, name='graph'),
    path('graph3/', views.graph3, name='graph'),
    path('graph4/', views.graph4, name='graph'),
    path('graph5/', views.graph5, name='graph'),
    path('graph6/', views.graph6, name='graph'),

]