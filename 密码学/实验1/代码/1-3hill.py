import numpy as np
def encode(string, size):
    #把 string 转换成 size x size 的 int32 numpy.ndarray
    blocks = (string[i:i + size] for i in range(0, len(string), size))
    # 将 a-z 编码为 0-25
    return np.array([list(map(ord, block)) for block in blocks], dtype='int32') - ord('a')

def matrixMul(A, B):
    res = [[0] * len(B[0]) for i in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                res[i][j] += A[i][k] * B[k][j]
    return res
#把一个 0-25 数字映射到字母
def modify(x):
    return chr(x%26+ord('a'))

def matrixT(A):
    B=[[0]*len(A)]*len(A[0])
    for i in  range (len(A)):
        for j in range (len(A[0])):
            B[j][i]=A[i][j]
    return list(map(list, zip(*A)))

def Statistics(plaintext ,cipher):
    Plain = {chr(i):0 for i in range(97,123)}
    Cipher={chr(i):0 for i in range(97,123)}
    for i in plaintext:
        Plain[i]=Plain[i]+1
    for i in cipher:
        Cipher[i]=Cipher[i]+1
    print("明文字频统计",Plain)
    print("密文字频统计",Cipher)
# 要加密的信息
msg=  'inseveraldistributedsystemsausershouldonlybeabletoaccessdataifauserpossesacertainsetofcredentialsorattributescurrentlytheonlymethodforenforcingsuchpoliciesistoemployatrustedservertostorethedataandmediateaccesscontrolhoweverifanyserverstoringthedataiscompromisedthentheconfidentialityofthedatawillbecompromisedinthispaperwepresentasystemforrealizingcomplexaccesscontrolonencrypteddatathatwecallciphertextpolicyattributebasedencryptionbyusingourtechniquesencrypteddatacanbekeptconfidentialevenifthestorageserverisuntrustedmoreoverourmethodsaresecureagainstcollusionattacks'
print("要加密的明文为：",msg,"\r\n")
# 加密矩阵
encryptermatrix = [[10, 5, 12, 0, 0], [3, 14, 21, 0, 0], [8, 9, 11, 0, 0], [0, 0, 0, 11, 8], [0, 0, 0, 3, 7]]
#print(encryptermatrix)

# 加密
encrypted = matrixMul(encode(msg, 5),encryptermatrix )#密文矩阵
encryptedlist =sum(encrypted,[])#转一维

cipher = ''.join(map(modify, encryptedlist))#映射到字母
print("密文为：",cipher,"\r\n")

# 解密矩阵decrypter。矩阵A的逆是(det A)^-1*伴随(A)
inverseelement=[0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25]#0到25在mod(26)下逆元
det=(int)(np.linalg.det(encryptermatrix))#求行列式
#np.linalg.det(encryptermatrix)*np.linalg.inv(encryptermatrix为伴随矩阵
decryptermatrix =[[(round(z)*(inverseelement[det%26]))%26 for  z in  y ]for y in (np.linalg.det(encryptermatrix)*np.linalg.inv(encryptermatrix)).tolist()]
#decryptermatrix=[[21,15,17,0,0],[23,2,16,0,0],[25,4,3,0,0],[0,0,0,7,18],[0,0,0,23,11]]
#print(decryptermatrix)
# 解密代码
decrypted = matrixMul(encode(cipher, 5),decryptermatrix)#解密后明文矩阵
decryptedlist=sum(decrypted,[])#list转一维

# 明文
plaintext = ''.join(map(modify,decryptedlist))#map对list批量操作
print("解密后明文为",plaintext,"\r\n")
Statistics(plaintext,cipher)#统计