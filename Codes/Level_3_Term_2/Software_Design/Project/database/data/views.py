
from django.shortcuts import render,HttpResponse
import json
from django.core import serializers
from django.views.decorators.csrf import csrf_exempt
# Create your views here.

from data.models import *

@csrf_exempt
def register(request):
    if request.method == 'POST':
        body_unicode = request.body.decode('utf-8')
        body_data = json.loads(body_unicode)
        areaName = body_data['area_name']
        userName = body_data['user_name']
        emailID = body_data['email_id']
        password = body_data['password']
        age = body_data['age']
        newUser = User.objects.filter(email_id=emailID)
        areaObject = Area.objects.get(area_name=areaName)

        if not newUser:
            data_object = User(area_id=areaObject, user_name=userName, email_id=emailID,age=age,password=password,admin_priviledge=0)
            data_object.save()
            return HttpResponse("Successful")
        else:
            return HttpResponse("Already Exists")

@csrf_exempt
def login(request):
	if request.method == 'POST':
		body_unicode = request.body.decode('utf-8')
		body_data = json.loads(body_unicode)
		emailID = body_data['email_id']
		password = body_data['password']
		enterUser = User.objects.filter(email_id=emailID)

		if not enterUser:
			return HttpResponse("Non-existent")
		else:
			data = User.objects.get(email_id=emailID)
			if(data.password==password):
				json_loginData=[{'user_name': data.user_name,'user_id':data.id,'age':data.age,'email_id':data.email_id,'area_name':data.area_id.area_name,'admin_priviledge':data.admin_priviledge}]
				return HttpResponse(json.dumps(json_loginData), content_type='application/json')
			else:
				return HttpResponse("Fail")







@csrf_exempt
def addComplaint(request):
	if request.method == 'POST':
		body_unicode = request.body.decode('utf-8')
		body_data = json.loads(body_unicode)
		userID = body_data['user_id']
		areaName = body_data['area_name']
		description = body_data['description']
		date_of_issue = body_data['date_of_issue']
		tag = body_data['tag']

		userObject = User.objects.get(id=userID)
		areaObject = Area.objects.get(area_name=areaName)

		if not userObject or not areaObject:
			return HttpResponse("Invalid")
		else:
			data_object = Complaint(user_id=userObject,area_id=areaObject,description=description,tag=tag,date_of_issue=date_of_issue)
			data_object.save()
			return HttpResponse("Successful")

@csrf_exempt
def addAdvertisement(request):
	if request.method == 'POST':
		body_unicode = request.body.decode('utf-8')
		body_data = json.loads(body_unicode)
		description = body_data['description']
		type = body_data['type']
		email = body_data['email_id']
		phoneNo = body_data['phone_no']
		linkToWebsite = body_data['link_to_website']
		date_of_issue = body_data['date_of_issue']

		data_object = Advertisement(description=description,type=type,email_id=email,phone_no=phoneNo,link_to_website=linkToWebsite,date_of_issue=date_of_issue)
		data_object.save()
		return HttpResponse("Successfully posted")


@csrf_exempt
def getAdvertisement(request):
	if request.method == 'GET':
		queryset = Advertisement.objects.all()
		data = [{'description': item.description, 'email_id': item.email_id,'type':item.type,'phone_no':item.phone_no,'link_to_website':item.link_to_website,'date_of_issue':item.date_of_issue} for item in queryset]
		return HttpResponse(json.dumps(data), content_type='application/json')

@csrf_exempt
def getComplaint(request):
	if request.method == 'GET':
		queryset = Complaint.objects.all()
		data = [{'description': item.description, 'tag': item.tag, 'area_name': item.area_id.area_name, 'user_name': item.user_id.user_name,'date_of_issue':item.date_of_issue} for item in queryset]
		return HttpResponse(json.dumps(data), content_type='application/json')

@csrf_exempt
def getContact(request):
	if request.method == 'POST':
		body_unicode = request.body.decode('utf-8')
		body_data = json.loads(body_unicode)
		area_name = body_data['area_name']
		print(area_name)
		area_object = Area.objects.get(area_name=area_name)
		print(area_object)
		queryset = Contact.objects.filter(area_id=area_object)
		print(queryset)
		data = [{'name_of_institution': item.name_of_instution, 'email_id': item.email_id,'phone_no':item.phone_no,'link_to_website':item.link_to_website,'area_name':item.area_id.area_name} for item in queryset]
		return HttpResponse(json.dumps(data), content_type='application/json')

@csrf_exempt
def getRawStatistics(request):
	if request.method == 'POST':
		body_unicode = request.body.decode('utf-8')
		body_data = json.loads(body_unicode)
		area_name = body_data['area_name']
		print(area_name)
		area_object = Area.objects.get(area_name=area_name)
		print(area_object)
		queryset = area_object
		item = queryset
		print(queryset)
		data = [{'area_name': item.area_name, 'number_of_theft': item.number_of_theft,'number_of_murder':item.number_of_murder,'number_of_rape':item.number_of_rape,'number_of_robbery':item.number_of_robbery,'number_of_terrorism':item.number_of_terrorism}]
		return HttpResponse(json.dumps(data), content_type='application/json')

def getAllStatistics(request):
	if request.method == 'GET':
		queryset = Area.objects.all()
		data = [{'area_name': item.area_name, 'number_of_theft': item.number_of_theft,'number_of_murder': item.number_of_murder, 'number_of_rape': item.number_of_rape,'number_of_robbery': item.number_of_robbery, 'number_of_terrorism': item.number_of_terrorism,'total':item.number_of_murder+item.number_of_rape+item.number_of_robbery+item.number_of_terrorism+item.number_of_theft}for item in queryset]
		return HttpResponse(json.dumps(data), content_type='application/json')
