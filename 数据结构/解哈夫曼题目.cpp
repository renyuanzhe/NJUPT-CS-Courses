#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include <queue>
#include<vector>
#include<iostream>
#include<map>
#include<string> 
using namespace std;
typedef char ElementType;

typedef struct HFMTreeNode{
ElementType element;//字符 
int w;  //权值
struct HFMTreeNode * lchild, *rchild;
}HFMTreeNode; 

typedef struct HFMbinarytree //哈夫曼结构体，有一个指针指向树根 
{HFMTreeNode *root;
}HFMbinarytree;

HFMTreeNode * NewNode(ElementType x,int w,HFMTreeNode * ln,HFMTreeNode *rn)//创建新节点 
{HFMTreeNode *p=(HFMTreeNode *)malloc(sizeof(HFMTreeNode));
p->element=x;
p->w=w;
p->lchild=ln;
p->rchild=rn;
return p;
}

void MakeHFMTree(HFMbinarytree *bt,ElementType e,int w,HFMbinarytree *left,HFMbinarytree * right)//以bt作为树根建树 ，left，right分别作为左右子树。操纵的都是树类型，对节点做了一次包装 
{if(bt->root||(left==right&&left!=NULL))return;//如果bt->root不为null ,直接返回 
if((left==right&&left==NULL)){bt->root=NewNode(e,w,NULL,NULL);return;}//建立只有bt一个结点的树（左右子树都为空） 
bt->root=NewNode(e,w,left->root,right->root);
left->root=right->root=NULL;
}

struct tree_compare
{
	bool operator() ( HFMbinarytree a,  HFMbinarytree b) const
	{   
	       
		return (a.root->w) > (b.root->w);	// 小顶堆
	}
};

HFMbinarytree CreateHFMTree(int w[],char c[],int m)
{priority_queue <HFMbinarytree,vector<HFMbinarytree>,struct tree_compare >q;//小顶堆

for(int i=0;i<m;i++)
{ HFMbinarytree x;
   x.root=NULL;  
  MakeHFMTree(&x,c[i],w[i],NULL,NULL);
  q.push(x);
}

while(q.size()>1)
{HFMbinarytree z;
   z.root=NULL;//每新建一个树，都要手动初始化，否则z.root！=null 
  HFMbinarytree x=q.top();
  q.pop();
 HFMbinarytree y=q.top();
 q.pop();
 if((x.root)->w < (y.root)->w)
 {MakeHFMTree(&z,'#',x.root->w+y.root->w,&x,&y); 
 }
 else
 {MakeHFMTree(&z,'#',x.root->w+y.root->w,&y,&x); 
 }
 q.push(z);
}
return q.top();
}

void InOrderTransverse(HFMTreeNode *t){
    if(t==NULL){
        return;
    }
    InOrderTransverse(t->lchild);  //中序遍历根结点的左子树
    printf("%d ",t->w);          //打印输出根结点，此处可以定义其他操作
    InOrderTransverse(t->rchild);  //最后中序遍历根结点的右子树
}
//dfs求哈夫曼树中每个字符的哈夫曼编码 
void InOrderTransverse_plus(HFMTreeNode *t,string code, map<char, string> &charcode){
    if(t==NULL){
        return;
    }
    if(t->element!='#'){charcode[t->element]=code;}
    InOrderTransverse_plus(t->lchild,code.append("0"), charcode);  //中序遍历根结点的左子树
     code.erase(code.end() - 1);;//回溯，删去code的最后一个字符 
    InOrderTransverse_plus(t->rchild,code.append("1"), charcode);  //最后中序遍历根结点的右子树
}
//解码功能 
char decode(HFMTreeNode *t,string &code){
	if(t->element!='#')
	{return t->element;
	}
	char ch=code.at(0);
	if(ch=='0')
	{code.erase(0,1);decode(t->lchild,code);//删去第一个字符 
	}
	if(ch=='1')
	{code.erase(0,1);decode(t->rchild,code);
	}
	
}

int main()
{int W[8]={29,9,26,27,2,23,8,24};
char c[8] ={'A','B','C','D','E','F','G','H'};


HFMbinarytree hfmtree=CreateHFMTree(W,c,8); //构建哈夫曼树 


	
//下面打印各字符哈夫曼编码 
cout<<endl;
map<char, string> charcode;//<字符，编码>
string code="";
InOrderTransverse_plus(hfmtree.root,code,charcode);
for(map<char,string>::iterator it=charcode.begin();it!=charcode.end();it++)
   {
       cout<<(it->first)<<" :"<<it->second<<endl;
        
   }
//解码功能 
code="01011";
cout<<"01011解码的字符为" <<decode(hfmtree.root,code); 
return 0;
} 
