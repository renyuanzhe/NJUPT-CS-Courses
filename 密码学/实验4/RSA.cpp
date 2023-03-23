#include<cstring>
#include<iostream>
 
using namespace std;
typedef long long LL;
int p=11, q=23, e=7;
bool Is_prime(int n)//普通判断素数
{
    for(int i=1;i*i<=n;++i)
    {
        if(n%i==0) return false;
    }
    return true;
}

LL exgcd(LL a,LL b,LL &x,LL &y)//扩展欧几里得算法  ax+by=gcd(a,b)  函数返回值ret为gcd(a,b) 
 {
	   if(b==0)
    {
        x=1,y=0;
        return a;
    }
    LL ret=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return ret;
}




LL qkpow(LL a,LL p,LL mod) //求a^p %mod 思路是把p看成成二进制形式 ，(a^b) mod c = (a mod c)^b mod c 
{
    LL ans=1,base=a%mod; 
    while(p)
    {
        if(p&1) ans=ans*base%mod;//如果 p最后一位是1 
        base=(base*base)%mod; //每一次移位都要平方 
        p>>=1;
    }
    return ans;
}

LL getInv(int a,int mod)//求a在mod下的逆元，不存在逆元返回-1 
{   if(Is_prime(mod))  //如果mod为素数，用费马小定理+快速模指数算法求逆元 
    {return qkpow(a,mod-2,mod);
	}
    LL x,y;
    LL d=exgcd(a,mod,x,y);
    return d==1?(x%mod+mod)%mod:-1;
}
int main(){
    
    // 计算 n = p×q，φ(n) = (p-1)×(q-1)
    // 计算 d，满足 d*e ≡ 1mod φ(n) 
    // 得到：公钥为 {e,n}, 私钥为 {d,n}    
    // 密文：C = M^e (mod n)
    //明文：M = C^d (mod n) 
    int n = p*q;
    
    int d =getInv(e,(p-1)*(q-1));
    

    
    int plaintext=30;// plaintext < n 
    cout<<"明文为"<<plaintext<<endl; 
    
    int cipher=qkpow(plaintext,e,n);
    cout<<"密文为"<<cipher<<endl; 
    
    
    int decode_cipher=qkpow(cipher,d,n);
    cout<<"解密为"<<decode_cipher<<endl; 
    return 0;
}
