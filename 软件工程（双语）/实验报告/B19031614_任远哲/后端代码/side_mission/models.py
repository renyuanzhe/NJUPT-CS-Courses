from django.db import models

#模块
class User(models.Model):
    u_name = models.CharField(max_length=20)
    u_num = models.CharField(max_length=20,default="")
    u_password = models.CharField(max_length=255)
    u_ticket = models.CharField(max_length=255,null=True)
    u_tel = models.CharField(max_length=255,default="")

    class Meta:
        db_table = 'user'


class Mission(models.Model):
    mis_title = models.CharField(max_length=20,default="")
    mis_content = models.CharField(max_length=255)
    mis_contact = models.CharField(max_length=25,default="")
    mis_state = models.CharField(max_length=3,default="未完成")

    class Meta:
        db_table = 'mission'

# Create your models here.
