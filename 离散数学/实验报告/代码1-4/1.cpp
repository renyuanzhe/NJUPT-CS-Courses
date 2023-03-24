#include <iostream>
#include <string>
#include<cstring>
#include <set>
#include <map>
using namespace std;
 
string org;       //原式，后面将其改造成后缀表达式 
string pcnf;    //主合取范式
string pdnf;    //主析取范式

int a, b, res;  //a、b保存出栈的两个元素的值，res保存计算结果

int choose;
 
class SeqStack 
{
public:
    SeqStack(int mSize);
    ~SeqStack();
    bool Push(char x);  
    bool Pop(); 
    char Top(); 
private:
    int top;
    char *st;
    int maxtop;
};
 
SeqStack::SeqStack(int mSize)
{
    maxtop = mSize - 1;
    st = new char[mSize];
    top = -1;
}
 
SeqStack::~SeqStack()
{
    delete[]st;
}
 
bool SeqStack::Push(char x) 
{
    if(top == maxtop)
        return false;
    st[++top] = x;
    return true;
}
 
bool SeqStack::Pop()     
{
    if(top == -1)
        return false;
    top--;
    return true;
}
 
char SeqStack::Top()        
{
    return st[top];
}
 
void And();     //合取
void Or();      //析取
void Not();     //否定
void If();      //条件
void Iif(); //双条件
bool CanIn(char out);       //判断能否进栈
void Suffix();              //求后缀表达式
void Calculate();           //计算公式的值
void Print();               //输出真值表和范式
void Calculate1();
 
SeqStack stack(200);        
  
map<char,int>map1; //（命题变元，真假） 

//dfs枚举t个2^t次方种 01组合 
void dfs(map<char,int>::iterator n)//n=begin;
{
if(n==map1.end())
{Calculate1();//计算 
return;
}
else
{
n->second=1;
n++;
dfs(n);
n--;
n->second=0;
n++;
dfs(n);
}
}




int main()
{
    cout << "! 否定" << endl << "| 析取" << endl <<"& 合取" << endl << "-> 条件" << endl << "<-> 双条件" << endl << endl;
    cout<<"请输入命题" <<endl; 
    
    
    
   
    char str[100];//初始读入 
    char ch[100];//简化初始式 
    cin >> str;
    int cnt = 0;
    for(int i = 0; i < strlen(str);)
    {
        if(str[i] == '-')
        {
            ch[cnt++] = '>';
            i += 2;
        }
        else if(str[i] == '<')
        {
            ch[cnt++] = '~';
            i += 3;
        }
        else
        {
            ch[cnt++] = str[i];
            if((65<=str[i]&&str[i]<=90)||(97<=str[i]&&str[i]<=122)){map1.insert(pair<char, int>(str[i],1));}
            i++;
        
    }
}
    ch[cnt++] = '\0';
    org = ch;
    Suffix();  //转后缀 
    map<char,int>::iterator iter = map1.begin();
    
	for (iter = map1.begin();iter != map1.end(); iter++){
         cout << iter->first<<"\t";//打印各最小命题变元 
    }
    cout<<str; //打印输入式 
    cout<<endl;
    
	iter = map1.begin();
	dfs(iter) ; 
    
	
    if(pdnf.length() != 0)  
        pdnf.erase(pdnf.length() - 2); //去掉式子末尾的多余连接符 
    if(pcnf.length() != 0)  
        pcnf.erase(pcnf.length() - 2);
    
    cout << "主析取范式：" << pdnf << endl << endl;
    cout << "主合取范式：" << pcnf << endl << endl;
	
    return 0;
}
 








void And()      //合取
{
    res = a * b;
    stack.Push(res);
}
 
void Or()       //析取
{
    res = a + b;
    res = res > 1 ? 1 : res;
    stack.Push(res);
}
 
void Not()      //否定
{
    a = stack.Top();
    stack.Pop();
    res = a == 1 ? 0 : 1;
    stack.Push(res);
}
 
void If()       //条件,b->a
{
    res = (b == 1 && a == 0) ? 0 : 1;
    stack.Push(res);
}
 
void Iif()  //双条件
{
    res = (b == a) ? 1 : 0;
    stack.Push(res);
}
 
bool CanIn(char out)        //先计算优先级，然后判断能否进栈
{
    char in = stack.Top();  
    int i, o;   //分别表示栈内外运算符的优先级
    switch(in)
    {
        case '#':i = 0; break;
        case '(':i = 1; break;
        case '~':i = 3; break;
        case '>':i = 5; break;
        case '|':i = 7; break;
        case '&':i = 9; break;
        case '!':i = 11; break;
        case ')':i = 12; break;
    }
    switch(out)
    {
        case '#':o = 0; break;
        case '(':o = 12; break;
        case '~':o = 2; break;
        case '>':o = 4; break;
        case '|':o = 6; break;
        case '&':o = 8; break;
        case '!':o = 10; break;
        case ')':o = 1; break;
    }
 
    if(i < o)      //如果栈外的优先级比栈内的高，就可以进栈，因为离栈顶越近，就越先出栈
        return true;
    else
        return false;
}
 
void Suffix()   //转换为后缀表达式
{
    string tmp = "";                //保存后缀表达式
    stack.Push('#');                //栈底
    for(int i = 0; (unsigned)i < org.length(); i++)
    {
        //if(org[i] == 'P' || org[i] == 'Q' || org[i] == 'R' || org[i] == 'S' || org[i] == 'T' || org[i] == 'U')      //如果是P、Q、R 就保存到字符串tmp中
        if((65<=org[i]&&org[i]<=90)||(97<=org[i]&&org[i]<=122))
        {
            tmp = tmp + org[i];
            continue;           
        }
        if(CanIn(org[i]))           
            stack.Push(org[i]);
        else if(org[i] == ')')       
        {
            while(stack.Top() != '(')
            {
                tmp = tmp + stack.Top();          
                stack.Pop();
            }
            stack.Pop();     
        }
        else                    
        {
            do
            {
                tmp = tmp + stack.Top();            
                stack.Pop();
            } while(!CanIn(org[i]));        
            stack.Push(org[i]);  
        }
    }
    while(stack.Top() != '#') 
    {
        tmp = tmp + stack.Top();   
        stack.Pop();
    }
    stack.Pop();                // '#' 出栈
    org = tmp;                      
}

void Calculate1()
{ 

 
    for(int i = 0; (unsigned)i < org.length(); i++)//org是后缀表达式 
    {if((65<=org[i]&&org[i]<=90)||(97<=org[i]&&org[i]<=122))//后缀表达式中遇到命题变元 ，入栈其01值 
            { stack.Push(map1[org[i]]);
              continue;          
            }
    	
    	 if(org[i] != '!')         // 后缀表达式中的单元连接词!
            {
                a = stack.Top();    
                stack.Pop();       
                b = stack.Top();
                stack.Pop();
            }
            switch(org[i])//后缀表达式中遇到双元连接词 ，栈顶变元出栈 ，并计算，更新res真假 
            {
                case '~':Iif(); break;
                case '>':If(); break;
                case '|':Or(); break;
                case '&':And(); break;
                case '!':Not(); break;
            } 
	}
	map<char,int>::iterator iter = map1.begin();
	 
	if(res == 1)  //res是整个命题的真假 
	{
	pdnf = pdnf + "(";//pdnf为主析取范式 
	for (iter = map1.begin();iter != map1.end(); iter++){
		string t1(1,iter->first);char t3[3]={'!',iter->first,'\0'}; string t2(t3);//把char类型的iter->first,!iter->first变成string，蛋疼的c++字符串 
         pdnf = pdnf + (iter->second == 1? t1 : t2)  ;
         if(iter != --map1.end()){pdnf=pdnf+"&" ;}
    }
    pdnf = pdnf + ")"+" | ";
    
	}
    else
	{pcnf = pcnf + "(";//pncf为主合取范式 
	
	for (iter = map1.begin();iter != map1.end(); iter++){
		string t1(1,iter->first);  char t3[3]={'!',iter->first,'\0'};   string t2(t3);//把char类型的iter->first,!iter->first变成string，蛋疼的c++字符串 
         pcnf = pcnf + (iter->second == 0 ? t1 : t2);
         if(iter != --map1.end()){pcnf=pcnf+"|" ;}
    }
    pcnf = pcnf + ")"+" & ";
	}  
	
	for (iter = map1.begin();iter != map1.end(); iter++){//打印每种组合命题变元的01值 
         cout << iter->second << "\t";
         
    }
    cout<<res<<endl;
    res=0;     //非必须 
    }
 
