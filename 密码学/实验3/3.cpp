#include <stdio.h>
#include <string.h>
#define S(x,n)  (x<<n|x>>(32-n))    //宏定义S函数为循环左移

static unsigned long m[16],w[80],h[5];

//1、补位:(余数448位)+补长度(64位)=512位 m
static void sha1_pad(char *input, int len){
    int i,n;
    
    for(i=0;i<16;i++){
        m[i] = 0;
    }
    for(i=0;i<len;i++){
        n = 24-((i&0x03)<<3);
        m[i/4] |= input[i]<<n;
    }
    n = 24-((i&0x03)<<3); //11000-i&011<<3
    m[i/4] |= 0x80<<n; //10000000<<n
    m[15] = len*8;
}

//2、由 512位 m生成 80字 w
static void sha1_prepare(void){
    int i;
    for(i=0;i<16;i++){
        w[i]=m[i];
    }
    for(i=16;i<80;i++){
        w[i]=w[i-16]^w[i-14]^w[i-8]^w[i-3];
        w[i]=S(w[i],1); //(w[i]<<n|w[i]>>(32-n))
    }
}

//3、由 80字 w计算 h
static void sha1_calc(void){
    int i;
    unsigned long a,b,c,d,e,f,k,temp;
    
    h[0]=0x67452301;
    h[1]=0xEFCDAB89;
    h[2]=0x98BADCFE;
    h[3]=0x10325476;
    h[4]=0xC3D2E1F0;
    a = h[0];
    b = h[1];//11101111110011011010101110001001
    c = h[2];//10011000101110101101110011111110
    d = h[3];//10000001100100101010001110110
    e = h[4];
    for(i=0;i<80;i++){
        switch(i/20){
        case 0:
            k=0x5A827999;
            f=(b&c)|(~b&d); 
            break;
        case 1:
            k=0x6ED9EBA1;
            f=b^c^d;
            break;
        case 2:
            k=0x8F1BBCDC;
            f=(b&c)|(b&d)|(c&d);
            break;
        case 3:
            k=0xCA62C1D6;
            f=b^c^d;
            break;
        }
        temp=S(a,5)+f+e+w[i]+k;
        e=d;
        d=c;
        c=S(b,30);
        b=a;
        a=temp;
    }
    h[0]+=a;
    h[1]+=b;
    h[2]+=c;
    h[3]+=d;
    h[4]+=e;
}

//input:待校验的数据，len:数据长度(小于56字节)
unsigned long* sha1(char* input, int len){
    sha1_pad(input,len);
    sha1_prepare();
    sha1_calc();
    return h;
}

int main(void){
    char str[1024];
    unsigned long* mac;
    printf("input:");
    gets(str);
    mac=sha1(str,strlen(str));
    printf("SHA1=%08X%08X%08X%08X%08X\n",mac[0],mac[1],mac[2],mac[3],mac[4]);
}
