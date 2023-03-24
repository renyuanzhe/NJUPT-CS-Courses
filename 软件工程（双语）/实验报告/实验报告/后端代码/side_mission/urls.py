from django.urls import path,include
from. import views

urlpatterns = [
    path('', views.index),
    path('index', views.index, name='主页'),
    path('me', views.me),
    path('login', views.login),
    path('mission_hall', views.m_h, name='任务大厅'),
    path('register', views.register),
    path('new_mission', views.new_mission),
    path('renwu/<forloop_counter>', views.renwu, name='任务详情'),
    
]
