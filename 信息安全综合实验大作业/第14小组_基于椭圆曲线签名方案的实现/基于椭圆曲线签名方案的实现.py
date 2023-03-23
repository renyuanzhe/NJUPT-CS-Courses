import random
from tkinter import ttk
from tkinter.scrolledtext import ScrolledText

from tkinter import * #for gui

import secrets
from hashlib import sha1
def extended_euclidean_algorithm(j, k):#扩展欧几里地算法 j mod k
    # 扩展欧几里地算法输入j和k两个整数，返回(gcd, x, y)。x和y满足jx + ky = 1
    if j == k:
        return (j, 1, 0)
    else:
        i = 0
        j_array = [j]
        k_array = [k]
        q_array = []
        r_array = []

        prev_r_is_zero = False

        while not (prev_r_is_zero):
            q_array.append(k_array[i]//j_array[i])
            r_array.append(k_array[i]%j_array[i])
            k_array.append(j_array[i])
            j_array.append(r_array[i])
            i += 1
            if r_array[i-1] == 0:
                prev_r_is_zero = True

        i -= 1
        gcd = j_array[i]

        x_array = [1]
        y_array = [0]

        i -= 1
        total_steps = i

        while i >= 0:
            y_array.append(x_array[total_steps-i])
            x_array.append(y_array[total_steps-i] - q_array[i]*x_array[total_steps-i])
            i -= 1

        return (gcd, x_array[-1], y_array[-1])



def mod_inverse(j, n):#求乘法逆元，求解(a×x)modp=1，转化为a×x+k×p=1
    #求j mod n 的乘法逆元
    (gcd, x, y) = extended_euclidean_algorithm(j, n)

    if gcd == 1:
        return x%n
    else:
        return -1

def elliptic_add(p, q):#两个不同的点相加
    #输入两个不同的点（元组类型），返回它们相加的结果（元组类型）
    if p == 0 and q == 0: return 0
    elif p == 0: return q
    elif q == 0: return p
    else:
        # 交互 p 和 q 如果 px > qx.
        if p[0] > q[0]:
            temp = p
            p = q
            q = temp
        r = []

        slope = (q[1] - p[1])*mod_inverse(q[0] - p[0], P) % P #若P≠Q，则k=(y2-y1)/(x2-x1) mod p

        r.append((slope**2 - p[0] - q[0]) % P)#x3≡k^2-x1-x2(mod p)
        r.append((slope*(p[0] - r[0]) - p[1]) % P)#y3≡k(x1-x3)-y1(mod p)

        return (r[0], r[1])


def elliptic_double(p):#两个相同的点相加
    r = []

    slope = (3*p[0]**2 + A)*mod_inverse(2*p[1], P) % P#若P=Q 则 k=(3x2+a)/2y1 mod p
    r.append((slope**2 - 2*p[0])%P)#x3≡k^2-x1-x2(mod p)
    r.append((slope*(p[0] - r[0]) - p[1])%P)#y3≡k(x1-x3)-y1(mod p)

    return (r[0], r[1])

def elliptic_multiply(s, p):#倍乘，其中P是一个点（元组），s是倍数

    n = p
    r = 0

    s_binary = bin(s)[2:]#将倍数s化成二进制形式
    s_length = len(s_binary)#二进制s的长度

    for i in reversed(range(s_length)):
        if s_binary[i] == '1':
            r = elliptic_add(r, n)
        n = elliptic_double(n)#存储当前的累加结果

    return r


def generate_public_key():#private_key是一个数字
    #输入一个整数作为私钥，计算其公钥（分为两部分，以元组形式返回）
    private_key=privatekey_input.get(1.0,END)
    private_key=int(private_key)

    publickey_x_input.delete('1.0', END)
    publickey_y_input.delete('1.0', END)
    publickey_x_input.insert(1.0,elliptic_multiply(private_key, BASE_POINT)[0])
    publickey_y_input.insert(1.0, elliptic_multiply(private_key, BASE_POINT)[1])

    return elliptic_multiply(private_key, BASE_POINT)# 公钥P=私钥k0×G

def sign():
    #输入私钥和一段文本，生成签名（分为两部分，以元组形式返回）
    private_key=privatekey_input2.get(1.0,END)
    private_key=int(private_key)
    message=msg_input.get(1.0,END)

    hashed_message = sha1(message.encode('utf-8')).hexdigest()#哈希操作针对的是01串.SHA1的结果是160 bit，通常用一个40位的16进制字符串表示
    hashed_message=int(hashed_message, 16)#哈希字符串即01串(当做16进制)转整数

    # 选择一个随机数k1
    k = secrets.randbelow(P)#取值范围是【1，n-1】

    random_point = elliptic_multiply(k, BASE_POINT)#随机点P1=随机数k1×G

    rx = random_point[0] % N#rx是随机点的横坐标
    signature_proof = mod_inverse(k, N) * (hashed_message + rx*private_key) % N  # S = k1^-1 ×(H(m)＋ k0×R)mod p

    sig_rx_input.delete('1.0', END)
    sig_signature_proof_input.delete('1.0', END)
    sig_rx_input.insert(1.0,rx)
    sig_signature_proof_input.insert(1.0,signature_proof)
    return (rx, signature_proof)

def verify():
    #输入公钥（元组形式），签名（元组形式）和文本，返回布尔值
    rx=sig2_rx_input.get(1.0,END)
    rx=int(rx)
    s=sig2_signature_proof_input.get(1.0,END)
    s=int(s)
    public_key_x=publickey_x_input2.get(1.0,END)
    public_key_x=int(public_key_x)
    public_key_y = publickey_y_input2.get(1.0, END)
    public_key_y = int(public_key_y)
    public_key=(public_key_x,public_key_y)

    message=msg2_input.get(1.0,END)


    hashed_message = sha1(message.encode('utf-8')).hexdigest()  # 哈希操作针对的是01串.SHA1的结果是160 bit，通常用一个40位的16进制字符串表示
    hashed_message = int(hashed_message, 16)  # 哈希字符串即01串(当做16进制)转整数

    inverse_s = mod_inverse(s, N)

    a = elliptic_multiply(hashed_message * inverse_s % N, BASE_POINT)
    b = elliptic_multiply(rx * inverse_s % N, public_key)
    recovered_random_point = elliptic_add(a, b)# P =S^-1 x H x G  +   S^-1 x R x P0

    if_verify.delete('1.0', END)
    if_verify.insert(1.0,recovered_random_point[0] == rx)
    return recovered_random_point[0] == rx


# 计算椭圆曲线在Fp域上的点集
def cal_points(p, a, b):
    return [(x, y) for x in range(p) for y in range(p) if (y*y - (x*x*x + a*x + b)) % p == 0]

def elliptic_add2(p, q,mod):#mod是椭圆曲线的模

    if p == 0 and q == 0: return 0
    elif p == 0: return q
    elif q == 0: return p
    else:
        # Swap p and q if px > qx.
        if p[0] > q[0]:
            temp = p
            p = q
            q = temp
        r = []

        slope = (q[1] - p[1])*mod_inverse(q[0] - p[0], mod) % mod

        r.append((slope**2 - p[0] - q[0]) % mod)
        r.append((slope*(p[0] - r[0]) - p[1]) % mod)

        return (r[0], r[1])

def elliptic_double2(p,a,mod):#mod是椭圆曲线的模

    r = []

    slope = (3*p[0]**2 + a)*mod_inverse(2*p[1], mod) % mod

    r.append((slope**2 - 2*p[0])%mod)
    r.append((slope*(p[0] - r[0]) - p[1])%mod)

    return (r[0], r[1])


def get_order(x0,y0,a,b,p):#计算点P(X0,Y0)在椭圆曲线中的阶,需要a,p参数
    # 计算-P，(x1,y1) ,逆元: 一个椭圆曲线上的点P的逆元，是相对x坐标的对称点
    x1 = x0
    y1 = (-1 * y0) % p
    temp_x = x0#存储累加结果
    temp_y = y0#存储累加结果

    n = 1
    while True:
        n += 1
        if temp_x==x0 and temp_y==y0:
            p_value = elliptic_double2((temp_x, temp_y),a,p)
        else:
            p_value = elliptic_add2((temp_x, temp_y), (x0, y0), p)

        if p_value[0] == x1 and p_value[1] == y1:#实质是看它累加多少次得到单位元，如果P^n=P^-1,那么n+1就是P的阶
            #print("==========该椭圆曲线的阶为%d=========" % (n + 1))
            return n + 1

        temp_x = p_value[0]
        temp_y = p_value[1]
    return -1 #若找不到，则P是无限阶

def generate_parameter():#根据a,b,p随机挑选G并计算G的阶N
    a = int(A_choose.get(1.0, END))
    b = int(B_choose.get(1.0, END))
    p = int(P_choose.get(1.0, END))

    Points=cal_points(p, a, b)#首先找出曲线上所有的散点
    while 1:
        point=random.choice(Points)
        if get_order(point[0],point[1],a,b,p)!=-1:
            BASE_X_Generate.delete('1.0', END)
            BASE_Y_Generate.delete('1.0', END)
            N_Generate.delete('1.0', END)

            BASE_X_Generate.insert(1.0, point[0])
            BASE_Y_Generate.insert(1.0, point[1])
            N_Generate.insert(1.0, get_order(point[0],point[1],a,b,p))
            break
            #return point,get_order(point[0],point[1])




#################################################################################################
#设置超参数a，b，p,G(BASE_POINT)，N，  设置用户的私钥
A = 0
B = 7
# 基点G
BASE_X = 55066263022277343669578718895168534326250603453777594175500187360389116729240
BASE_Y = 32670510020758816978083085130507043184471273380659243275938904335757337482424
BASE_POINT = (BASE_X, BASE_Y)
# 选择的素数P
P = 115792089237316195423570985008687907853269984665640564039457584007908834671663#3037
# 基点G的阶
N = 115792089237316195423570985008687907852837564279074904382605163141518161494337
#################################################################################################
#私钥90091995117922640880280884246606088684600200668880860808084064086262886840684
def change_hyperparameters(): #修改签名算法中的超参数
    global A
    global B
    global BASE_X
    global BASE_Y
    global BASE_POINT
    global P
    global N

    A = A_change.get(1.0, END)
    A=int(A)
    B = B_change.get(1.0, END)
    B = int(B)
    BASE_X = BASE_X_change.get(1.0, END)
    BASE_X = int(BASE_X)
    BASE_Y = BASE_Y_change.get(1.0, END)
    BASE_Y = int(BASE_Y)
    P = P_change.get(1.0, END)
    P = int(P)
    N = A_change.get(1.0, END)
    N = int(N)
    print(B)

########################################################################
root = Tk()
root.title("ECDSA Signature,信安实验大作业")
root.geometry("920x750")
# root.configure(bg='white')
s = ttk.Style(root)
s.configure("TNotebook", tabposition='n',background='#6C6C6C')
s.configure("TFrame",background='#FAEBD7')
notebook = ttk.Notebook(root,padding=20);
notebook.pack(expand=1, fill="both")
frame1 = ttk.Frame(notebook,relief=GROOVE,padding=5)
frame2 = ttk.Frame(notebook,relief=GROOVE,padding=5)
frame3 = ttk.Frame(notebook,relief=GROOVE,padding=5)
frame4 = ttk.Frame(notebook,relief=GROOVE,padding=5)
frame5 = ttk.Frame(notebook,relief=GROOVE,padding=5)
notebook.add(frame1, text='   Generate Keys   ')
notebook.add(frame2, text='   Sign Text   ')
notebook.add(frame3, text='   Verify Signature   ')
notebook.add(frame4, text='   Generate Parameter   ')
notebook.add(frame5, text='   Settings   ')

####################################   page1输入私钥，计算公钥的页面
Label(frame1,text="  Generate Keys: ",font=('Arial', 14, 'bold'),background='#FAEBD7').grid(padx=5,pady=10,row=0,column=0)
#Label(frame1,text="  椭圆曲线参数: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=2, column=0)
Label(frame1,text="Private Key: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=3,column=0)

privatekey_input=ScrolledText(frame1,width=80,height=5)#私钥输入框
privatekey_input.grid(padx=5,pady=10,row=3, column=1,sticky="E",columnspan=4)

Generate_Keys_Button=Button(frame1,text = " Generate Public Keys ",font=('Arial', 12),activebackground='Coral',background='LightSeaGreen',relief=FLAT,command=generate_public_key)
Generate_Keys_Button.grid(ipadx=10,ipady=10,padx=5,pady=10,row=4,column=2)

Label(frame1,text="Public Key_x: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=5,column=0)
Label(frame1,text="Public Key_y: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=6,column=0)
publickey_x_input=ScrolledText(frame1,width=80,height=5)
publickey_x_input.grid(padx=5,pady=10,row=5, column=1,sticky="E",columnspan=4)
publickey_y_input=ScrolledText(frame1,width=80,height=5)
publickey_y_input.grid(padx=5,pady=10,row=6, column=1,sticky="E",columnspan=4)

####################################  page2输入文本并签名
Label(frame2,text="  Signing:            ",font=('Arial', 14, 'bold'),background='#FAEBD7').grid(padx=5,pady=10,row=11,column=0)
Label(frame2,text=" Enter Text:    ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=13,column=0)

msg_input=ScrolledText(frame2,width=80,height=10)
msg_input.grid(padx=5,pady=10,row=13, column=1,sticky="E",columnspan=4)

Label(frame2,text=" Private Key:    ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=14,column=0)
privatekey_input2=ScrolledText(frame2,width=80,height=5)
privatekey_input2.grid(padx=5,pady=10,row=14, column=1,sticky="E",columnspan=4)

Sign_Button=Button(frame2,text = " Sign text ",font=('Arial', 12),activebackground='Coral',background='LightSeaGreen',relief=FLAT,command=sign)
Sign_Button.grid(ipadx=10,ipady=10,padx=5,pady=10,row=15,column=2)

Label(frame2,text=" Signature(rx):      ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=16,column=0)
sig_rx_input=ScrolledText(frame2,width=80,height=5)
sig_rx_input.grid(padx=5,pady=10,row=16, column=1,sticky="E",columnspan=4)

Label(frame2,text=" Signature(signature_proof):      ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=17,column=0)
sig_signature_proof_input=ScrolledText(frame2,width=80,height=5)
sig_signature_proof_input.grid(padx=5,pady=10,row=17, column=1,sticky="E",columnspan=4)

####################################     page3验证文本和其签名
Label(frame3,text="  Verify Signature: ",font=('Arial', 14, 'bold'),background='#FAEBD7').grid(padx=5,pady=10,row=14,column=0)

Label(frame3,text=" Enter Text: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=21,column=0)
msg2_input=ScrolledText(frame3,width=80,height=10)
msg2_input.grid(padx=5,pady=10,row=21, column=1,sticky="E",columnspan=4)

Label(frame3,text=" Enter Signature(rx): ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=23,column=0)
sig2_rx_input=ScrolledText(frame3,width=80,height=5)
sig2_rx_input.grid(padx=5,pady=10,row=23, column=1,sticky="E",columnspan=2)

Label(frame3,text=" Enter Signature(signature_proof): ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=24,column=0)
sig2_signature_proof_input=ScrolledText(frame3,width=80,height=5)
sig2_signature_proof_input.grid(padx=5,pady=5,row=24, column=1,sticky="E",columnspan=4)

Label(frame3,text=" Enter Public Key_x: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=25,column=0)
publickey_x_input2=ScrolledText(frame3,width=80,height=5)
publickey_x_input2.grid(padx=5,pady=5,row=25, column=1,sticky="E",columnspan=4)

Label(frame3,text=" Enter Public Key_y: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=26,column=0)
publickey_y_input2=ScrolledText(frame3,width=80,height=5)
publickey_y_input2.grid(padx=5,pady=5,row=26, column=1,sticky="E",columnspan=4)

Verify_Button=Button(frame3,text = " Verify Signature ",activebackground='Coral',font=('Arial', 12),background='LightSeaGreen',relief=FLAT,command=verify)
Verify_Button.grid(ipadx=10,ipady=10,padx=5,pady=10,row=27,column=1)

Label(frame3,text=" is_correct: ",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=28,column=0)
if_verify=ScrolledText(frame3,width=80,height=5)
if_verify.grid(padx=5,pady=5,row=28, column=1,sticky="E",columnspan=4)


####################################     page4根据abp，计算G，N
Label(frame4,text=" Generate Parameter:            ",font=('Arial', 14, 'bold'),background='#FAEBD7').grid(padx=5,pady=10,row=11,column=0)

Label(frame4,text="  A:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=13,column=0)
A_choose=ScrolledText(frame4,width=70,height=4)
A_choose.grid(padx=5,pady=10,row=13, column=1,sticky="E",columnspan=4)

Label(frame4,text="  B:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=20,column=0)
B_choose=ScrolledText(frame4,width=70,height=4)
B_choose.grid(padx=5,pady=10,row=20, column=1,sticky="E",columnspan=4)

Label(frame4,text="  P:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=27,column=0)
P_choose=ScrolledText(frame4,width=70,height=4)
P_choose.grid(padx=5,pady=10,row=27, column=1,sticky="E",columnspan=4)

Generate_Button=Button(frame4,text = " Generate N,P ",font=('Arial', 12),activebackground='Coral',background='LightSeaGreen',relief=FLAT,command=generate_parameter)
Generate_Button.grid(ipadx=10,ipady=10,padx=5,pady=10,row=34,column=2)

Label(frame4,text="  BASE_X:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=40,column=0)
BASE_X_Generate=ScrolledText(frame4,width=80,height=5)
BASE_X_Generate.grid(padx=5,pady=5,row=40, column=1,sticky="E",columnspan=4)

Label(frame4,text="  BASE_Y:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=47,column=0)
BASE_Y_Generate=ScrolledText(frame4,width=80,height=5)
BASE_Y_Generate.grid(padx=5,pady=5,row=47, column=1,sticky="E",columnspan=4)

Label(frame4,text="  N:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=54,column=0)
N_Generate=ScrolledText(frame4,width=80,height=5)
N_Generate.grid(padx=5,pady=5,row=54, column=1,sticky="E",columnspan=4)


####################################     page5更改超参数
Label(frame5,text=" hyper-parameters:            ",font=('Arial', 14, 'bold'),background='#FAEBD7').grid(padx=5,pady=10,row=11,column=0)

Label(frame5,text="  A:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=13,column=0)
A_change=ScrolledText(frame5,width=70,height=4)
A_change.grid(padx=5,pady=10,row=13, column=1,sticky="E",columnspan=4)

Label(frame5,text="  B:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=20,column=0)
B_change=ScrolledText(frame5,width=70,height=4)
B_change.grid(padx=5,pady=10,row=20, column=1,sticky="E",columnspan=4)

Label(frame5,text="  BASE_X:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=27,column=0)
BASE_X_change=ScrolledText(frame5,width=70,height=4)
BASE_X_change.grid(padx=5,pady=10,row=27, column=1,sticky="E",columnspan=4)

Label(frame5,text="  BASE_Y:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=34,column=0)
BASE_Y_change=ScrolledText(frame5,width=70,height=4)
BASE_Y_change.grid(padx=5,pady=10,row=34, column=1,sticky="E",columnspan=4)

Label(frame5,text="  P:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=41,column=0)
P_change=ScrolledText(frame5,width=70,height=4)
P_change.grid(padx=5,pady=10,row=41, column=1,sticky="E",columnspan=4)

Label(frame5,text="  N:",font=('Arial', 12),background='#FAEBD7').grid(padx=5,pady=10,row=48,column=0)
N_change=ScrolledText(frame5,width=70,height=4)
N_change.grid(padx=5,pady=10,row=48, column=1,sticky="E",columnspan=4)


Change_Button=Button(frame5,text = " Change_hyperparameters ",font=('Arial', 12),activebackground='Coral',background='LightSeaGreen',relief=FLAT,command=change_hyperparameters)
Change_Button.grid(ipadx=10,ipady=10,padx=5,pady=10,row=55,column=2)


####################################
root.mainloop()
####################################


