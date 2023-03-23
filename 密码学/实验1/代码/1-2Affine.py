
def myExtGCD(a, b):
    # a: 模的取值,b: 想求逆的值

    if b == 0:
        return 1, 0, a
    else:
        x, y, q = myExtGCD(b, a % b)
        # q = gcd(a, b) = gcd(b, a%b)
        x, y = y, (x - (a // b) * y)
        return x, y, q

def lettermodify(x):
    return ord(x)-ord('a')

def numbermodify(x):
    return chr(x%26+ord('a'))

def Statistics(plaintext ,cipher):
    Plain = {chr(i):0 for i in range(97,123)}
    Cipher={chr(i):0 for i in range(97,123)}

    for i in plaintext:
        Plain[i]=Plain[i]+1
    for i in cipher:
        Cipher[i]=Cipher[i]+1
    print("明文字频统计",Plain)
    print("密文字频统计",Cipher)

msg = 'inseveraldistributedsystemsausershouldonlybeabletoaccessdataifauserpossesacertainsetofcredentialsorattributescurrentlytheonlymethodforenforcingsuchpoliciesistoemployatrustedservertostorethedataandmediateaccesscontrolhoweverifanyserverstoringthedataiscompromisedthentheconfidentialityofthedatawillbecompromisedinthispaperwepresentasystemforrealizingcomplexaccesscontrolonencrypteddatathatwecallciphertextpolicyattributebasedencryptionbyusingourtechniquesencrypteddatacanbekeptconfidentialevenifthestorageserverisuntrustedmoreoverourmethodsaresecureagainstcollusionattacks'
a=11
b=6
plaincode=map(lettermodify,list(msg))
cipercode=[]
for i in plaincode:
    cipercode.append((i*a+b)%26)
ciper=''.join(map(numbermodify,cipercode))

print('密文为：',ciper)

cipercode=map(lettermodify,list(ciper))
plaincode=[]
for i in cipercode:
    plaincode.append((myExtGCD(26,a)[1]*(i-b))%26)

plaintext=''.join(map(numbermodify,plaincode))

print("解密后明文为",plaintext,"\r\n")
Statistics(msg,ciper)