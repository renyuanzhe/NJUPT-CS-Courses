#include<stdio.h>
#include<map>
#include<string.h>
using namespace std;
int key[100]={0};//输入(143)(56),经过getkey，得到421365 
int decodekey[100]={0};//解密密钥 
void getkey(char* pointerK){
	
	int* ktemp=key;
	int i;
	int t=0;
	for(i=0;i<100;i++)
		key[i]=i;
 
    
	do{
		if(*pointerK=='(')
			continue;
		else{
			t=*pointerK-'0';
			while(*(pointerK+1)!=')'){
			ktemp[*pointerK-'0']=*(pointerK+1)-'0';
			pointerK++;
			}
			ktemp[*pointerK-'0']=t;
			pointerK++;
		}
	}	while(*(++pointerK)!='\0');	
	
}


int main()
{
    char plaintext[9999]="inseveraldistributedsystemsausershouldonlybeabletoaccessdataifauserpossesacertainsetofcredentialsorattributescurrentlytheonlymethodforenforcingsuchpoliciesistoemployatrustedservertostorethedataandmediateaccesscontrolhoweverifanyserverstoringthedataiscompromisedthentheconfidentialityofthedatawillbecompromisedinthispaperwepresentasystemforrealizingcomplexaccesscontrolonencrypteddatathatwecallciphertextpolicyattributebasedencryptionbyusingourtechniquesencrypteddatacanbekeptconfidentialevenifthestorageserverisuntrustedmoreoverourmethodsaresecureagainstcollusionattacks",cipher[9999],decodetext[9999];//明文，密文，由密文解密得到的明文 
    char K[100];//K=(143)(56)
    
    int cyclelen,len;
    //printf("请输入你要输入的明文：");
    //scanf("%s",plaintext);
    len=strlen(plaintext);
    
	printf("明文为：\n");
    for(int i=0; i<len; i++)
        printf("%c",plaintext[i]);
	printf("\n");
 
    printf("输入周期长度：");
    scanf("%d",&cyclelen);
    getchar();
    
    printf("\n");
    

    //补齐末尾空缺 
	for(int i=len; i<len+cyclelen-(len%cyclelen); i++)
        {plaintext[i]='#';
		}
	plaintext[len+cyclelen-len%cyclelen]='\0';
 
    
	printf("请输入置换形式，形如(143)(56) \n");
    gets(K);//K=(143)(56)
    
	
     printf("加密密钥如下：\n");
	//(143)(56),经过getkey，得到421365 
	getkey(K);
	//打印加密密钥 
	for(int i=1;i<=cyclelen;i++)
    {printf("%d ", key[i]) ;
	   
    }
    
    //加密过程 
	int flag=1;
    for(int i=0; i<len+cyclelen-len%cyclelen; i++)//plaintext[len+cyclelen-len%cyclelen]='\0'
    {  if(flag==cyclelen+1){flag=1;}
	
        
        cipher[i]=plaintext[i-(flag-key[flag])];
        flag++;
    }
    //打印密文 
    printf("\n\n");
    printf("密文如下：\n");
    for(int i=0; i<len+cyclelen-len%cyclelen; i++)
        printf("%c",cipher[i]);
    printf("\n\n");
    
    
	printf("通过加密密钥，构造解密密钥：\n");
	//通过加密密钥，构造解密密钥 
    for(int i=1;i<=cyclelen;i++)
    {
	   decodekey[key[i]]=i;
    }
    //打印解密密钥
    for(int i=1;i<=cyclelen;i++)
    {printf("%d ", decodekey[i]) ;
	   
    }
    
    //解密过程 
	flag=1;
    for(int i=0; i<len; i++)
    {  if(flag==cyclelen+1){flag=1;}
	
       
        decodetext[i]=cipher [i-(flag-decodekey[flag])];
        flag++;
    }
    //打印解密后密文 
	printf("\n\n");
    printf("密文经过解密结果如下：\n");
    for(int i=0; i<len; i++)
        printf("%c",decodetext[i]);
    printf("\n");
    
    printf("密文统计：\n");
    map<char,int>statistics;
    for(int i=0; i<26; i++)
        statistics.insert(pair<int, int>(i+97, 0));
    for(int i=0; i<len; i++)
        {
		statistics[cipher[i]]++;
        
    }
    for(int i=0; i<26; i++)
        printf("%c：%d个",i+97,statistics[i+97]);
    return 0;
}
