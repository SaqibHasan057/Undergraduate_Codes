from django.db import models

# Create your models here.

class Area(models.Model):
	area_name = models.CharField(max_length=200,null=True)
	number_of_theft = models.IntegerField()
	number_of_murder = models.IntegerField()
	number_of_rape = models.IntegerField()
	number_of_robbery = models.IntegerField()
	number_of_terrorism = models.IntegerField()

	def __str__(self):
		return self.area_name


class User(models.Model):
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)
	user_name = models.CharField(max_length=200)
	email_id = models.CharField(max_length=200)
	age = models.IntegerField()
	password = models.CharField(max_length=200)
	admin_priviledge = models.IntegerField();

	def __str__(self):
		return self.user_name

class Advertisement(models.Model):
	description = models.CharField(max_length=200000,null=True)
	email_id = models.CharField(max_length=200,null=True)
	phone_no = models.CharField(max_length=20,null=True)
	type = models.CharField(max_length=20,null=True)
	link_to_website = models.CharField(max_length=200,null=True)
	date_of_issue = models.CharField(max_length=200,null=True)

	def __str__(self):
		return self.description

class Contact(models.Model):
	name_of_instution = models.CharField(max_length=200,null=True)
	email_id = models.CharField(max_length=200,null=True)
	phone_no = models.CharField(max_length=20,null=True)
	link_to_website = models.CharField(max_length=200,null=True)
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)

	def __str__(self):
		return self.name_of_instution

class Complaint(models.Model):
	description = models.CharField(max_length=200000,null=True)
	tag = models.CharField(max_length=20,null=True)
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)
	user_id = models.ForeignKey('User',on_delete=models.CASCADE)
	date_of_issue = models.CharField(max_length=200, null=True)

	def __str__(self):
		return self.description

class Theft(models.Model):
	complaint_id = models.ForeignKey('Complaint',on_delete=models.CASCADE)
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)
	month = models.IntegerField()
	year = models.IntegerField()

	def __str__(self):
		return self.complaint_id

class Murder(models.Model):
	complaint_id = models.ForeignKey('Complaint',on_delete=models.CASCADE)
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)
	month = models.IntegerField()
	year = models.IntegerField()

	def __str__(self):
		return self.complaint_id

class Robbery(models.Model):
	complaint_id = models.ForeignKey('Complaint',on_delete=models.CASCADE)
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)
	month = models.IntegerField()
	year = models.IntegerField()

	def __str__(self):
		return self.complaint_id

class Rape(models.Model):
	complaint_id = models.ForeignKey('Complaint',on_delete=models.CASCADE)
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)
	month = models.IntegerField()
	year = models.IntegerField()

	def __str__(self):
		return self.complaint_id

class Terrorism(models.Model):
	complaint_id = models.ForeignKey('Complaint',on_delete=models.CASCADE)
	area_id = models.ForeignKey('Area',on_delete=models.CASCADE)
	month = models.IntegerField()
	year = models.IntegerField()

	def __str__(self):
		return self.complaint_id

