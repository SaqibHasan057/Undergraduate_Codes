from django.conf.urls import url


from . import views

urlpatterns = [
    url(r'^register/$', views.register, name='register'),
    url(r'^login/$', views.login, name='login'),
    url(r'^addComplaint/$', views.addComplaint, name='addComplaint'),
    url(r'^addAdvertisement/$', views.addAdvertisement, name='addAdvertisment'),
    url(r'^getAdvertisement/$', views.getAdvertisement, name='getAdvertisment'),
    url(r'^getComplaint/$', views.getComplaint, name='getComplaint'),
    url(r'^getContact/$', views.getContact, name='getContact'),
    url(r'^getRawStatistics/$', views.getRawStatistics, name='getRawStatistics'),
    url(r'^getAllStatistics/$', views.getAllStatistics, name='getAllStatistics'),
]
