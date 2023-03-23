var k1=0,k2=0,k3=0,k4=0,k5=0;

function judgepsw() //密码是否一致
{
    var flag = true;
    var initial_password = document.getElementById("pswid1").value;
    var confirm_password = document.getElementById("pswid2").value;
    if (initial_password != confirm_password) {
        alert("请确认密码是否一致")
        var tip = document.getElementById("pswtip2");
        tip.innerHTML = "请再次输入密码";
        tip.style.color = "red";
    }
    else {
        var tip = document.getElementById("pswtip2");
        tip.innerHTML = "OK";
        tip.style.color = "green";
        k1=1;
    }
}

function input_nullcheck(node, text) //检测输入是否为空
{
    if (node.value == null || node.value == "") {
        alert(text);
        return false;
    }
    else
        return true;
}

function checkname()// 检测用户名长度
{
    var usernode = document.getElementById("nameid");
    input_nullcheck(usernode, "请输入用户名");
    if (usernode.value.length > 0 ) {
        var tip = document.getElementById("nametip");
        tip.innerHTML = "OK";
        tip.style.color = "green";
        k2=1;
    }
    else {
        var tip = document.getElementById("nametip");
        tip.innerHTML = "请输入用户名";
        tip.style.color = "red";
    }
}
/*
function checkemail()//验证邮箱是否合法
{
    var useremailnode = document.getElementById("useremail");
    if (input_nullcheck(useremailnode, "请输入邮箱")) {
        apos = useremailnode.value.indexOf("@")
        dotpos =useremailnode.value.lastIndexOf(".")
        if (apos < 1 || dotpos - apos < 2) {
            alert("邮箱不合法");
            var tip = document.getElementById("useremailtip");
            tip.innerHTML = "请输入合法邮箱";
            tip.style.color = "red";
        }
        else {
            var tip = document.getElementById("useremailtip");
            tip.innerHTML = "OK";
            tip.style.color = "green";
        }
    }       
}*/

function checkpsw()//检测密码长度
{
    var passwordnode = document.getElementById("pswid1");
    if (input_nullcheck(passwordnode, "请输入密码")) {
        if (passwordnode.value.length >= 8) {
            var tip = document.getElementById("pswtip1");
            tip.innerHTML = "OK";
            tip.style.color = "green";
            k3=1;
        }
        else {
            var tip = document.getElementById("pswtip1");
            tip.innerHTML = "密码至少8位";
            tip.style.color = "red";
        }
    }   
}

function checktel()//检测电话号码
{
    var telnode = document.getElementById("telid");
    if (input_nullcheck(telnode, "请输入手机号")) {
        if (telnode.value.length != 11) {
            var tip = document.getElementById("teltip");
            tip.style.color = "red";
            tip.innerHTML = "请输入11位手机号";
        }
        else {
            var flag = 1;
            var string = telnode.value;
            for (var i = 0; i < 11; i++) {
                if (string[i] >= '0' && string[i] <= '9')
                    continue;
                else {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                var tip = document.getElementById("teltip");
                tip.innerHTML = "OK";
                tip.style.color = "green";
                k4=1;
            }
            else {
                var tip = document.getElementById("teltip");
                alert("请输入11位合法手机号");
                tip.innerHTML = "请输入11位手机号";
                tip.style.color = "red";
            }
        }
    }
}

function checkid()//检测学号
{
    var telnode = document.getElementById("idid");
    if (input_nullcheck(telnode, "请输入您的学号")) {
        if (telnode.value.length != 10 ) {
            var tip = document.getElementById("idtip");
            tip.style.color = "red";
            tip.innerHTML = "请正确输入您的学号";
        }
        else {
            var flag = 1;
            var string = telnode.value;
            for (var i = 0; i < 10; i++) {
                if (string[i] >= '0' && string[i] <= '9')
                    continue;
                else {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                var tip = document.getElementById("idtip");
                tip.innerHTML = "OK";
                tip.style.color = "green";
                k5=1;
            }
            else {
                var tip = document.getElementById("idtip");
                alert("请正确输入您的学号");
                tip.innerHTML = "请输入您的学号";
                tip.style.color = "red";
            }
        }
    }
}

function judge(){
    if(k1&&k2&&k3&&k4&&k5)
        ;
        //alert("注册成功，请重新登陆!");
        //return true;
    else{
        alert("请确认您的注册信息");
        return false;
    }
}