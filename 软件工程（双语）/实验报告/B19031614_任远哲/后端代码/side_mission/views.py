from django.shortcuts import render,redirect

from django.contrib.auth.hashers import make_password, check_password
from django.http import HttpResponseRedirect, HttpResponse
from django.shortcuts import render
from side_mission.models import User
from side_mission.models import Mission
from django.contrib import messages


global count
count = {'已发任务': 0 ,'已接任务': 0, '已完成任务':0}

def index(request):
    return render(request,'index.html')
    
def me(request):
    username = request.session.get("username")
    global count
    content = {'计数': count,'username':username}
    if username:
        return render(request,"me.html",content)
    else:
        return render(request,"me.html")
    
def m_h(request):
    lst = Mission.objects.all()
    if lst:
        content = { 'LIST': lst }
        return render(request,'mission_hall.html',content)
    else:
        content = { 'LIST': 'none' }
        return render(request,'mission_hall.html',content)

def new_mission(request):
    global count
    if request.method == 'GET':
        return render(request,'new_mission.html')
    if request.method == 'POST':
        tit = request.POST.get('发布任务')
        mission = request.POST.get('概述')
        cat = request.POST.get('联系方式')
        Mission.objects.create(
            mis_title=tit,
            mis_content=mission,
            mis_contact=cat,
        )
        count['已发任务'] = count['已发任务'] + 1
        return HttpResponseRedirect(
            '/mission_hall'
        )

    
def login(request):
    if request.method == 'GET':
        return render(request,'login.html')
    if request.method == 'POST':
        num = request.POST.get('usernum')
        password = request.POST.get('password')
        if User.objects.filter(u_num = num).exists():#如果输入的账号在数据库中存在
            user = User.objects.get(u_num=num)
            if check_password(password,user.u_password):#如果账号的密码也匹配
                ticket = 'dsvdsvsvs'  #网页登陆成功后可以看到这个ticket的值
                response = HttpResponse()
                response.set_cookie('ticket',ticket)#令牌，用户登陆成功就会有一个令牌，并传输到数据库中，只要令牌还在浏览器缓存中，用户访问页面就不需要再次输入密码，关闭浏览器后令牌被删除。
                user.u_ticket = ticket
                request.session["username"] = user.u_name
                user.save()
                return HttpResponseRedirect(
            '/index'
        )#这里返回一个存储所有用户信息的页面
            else:
                #return HttpResponse('用户密码错误')
                messages.success(request,"用户密码错误")
                return HttpResponseRedirect('/login')
        else:
            #return HttpResponse('用户不存在')
            messages.success(request,"用户账户不存在")
            return HttpResponseRedirect('/login')
            
def renwu(request, forloop_counter):
    global count
    lst = Mission.objects.all()
    chang = Mission.objects.get(id=lst[int(forloop_counter) - 1].id) 
    if request.method == "POST":
        chang.mis_state = '已完成'
        chang.save()
        count['已接任务'] = count['已接任务'] + 1
        return HttpResponseRedirect(
            '/mission_hall'
        )
    else:
        content = { 'detail' : lst[int(forloop_counter) - 1]}
        return render(request,'renwu.html', content)

def register(request):
    if request.method == 'GET':
        return render(request,'register.html')
    if request.method == 'POST':
        name = request.POST.get('username')
        unum = request.POST.get('usernum')
        if User.objects.filter(u_num = unum).exists():
            messages.success(request,"该用户已存在")
            return HttpResponseRedirect('/register')
        else:
            password1 = request.POST.get('psw1')
            password2 = request.POST.get('psw2')
            if password1 == password2:
                password = make_password(password1)
                #password = password1
            telnum = request.POST.get('tel')
            #不明文显示密码
            User.objects.create(
                u_name=name,
                u_num=unum,
                u_password=password,
                u_tel=telnum,
            )#将写入的数据写入到数据库中
            messages.success(request,"注册成功，请登录")
            return HttpResponseRedirect(
                '/login'
            )#在注册后跳转到登陆页面
'''       
def new_mission(request):
    global lst
    if request.method == "POST":
        if(request.POST['发布任务'] == '' ):
            return render(request,'new_mission.html',{'警告':'请输入内容！'})  
        else:
            lst.append({ '任务':str(request.POST['发布任务']), '已完成':False})
            content = { 'LIST': lst }
            return redirect('任务大厅')   
    else:
        content = { 'LIST': lst }
        return render(request,'new_mission.html',content)
'''


        
    
   

