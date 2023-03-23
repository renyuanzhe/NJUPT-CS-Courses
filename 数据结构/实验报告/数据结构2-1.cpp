#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef char ElemType;
typedef struct BinaryTreeNode{
    ElemType Data;
    struct BinaryTreeNode *LChild, *RChild;
}BinaryTreeNode;
 
 
//先序遍历
void PreOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    printf("%c",t->Data);           //打印输出根结点，此处可以定义其他操作
    PreOrderTransverse(t->LChild);  //然后先序遍历左子树
    PreOrderTransverse(t->RChild);  //最后先序遍历右子树
}
 
 
//中序遍历
void InOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    InOrderTransverse(t->LChild);  //中序遍历根结点的左子树
    printf("%c",t->Data);          //打印输出根结点，此处可以定义其他操作
    InOrderTransverse(t->RChild);  //最后中序遍历根结点的右子树
}
 
 
//后序遍历
void PostOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    PostOrderTransverse(t->LChild);  //后序遍历根结点的左子树
    PostOrderTransverse(t->RChild);  //然后后序遍历根结点的右子树
    printf("%c",t->Data);            //最后打印输出根结点，此处可以定义其他操作
}
 
 
//先序遍历构建二叉树
BinaryTreeNode *PreCreateBt(BinaryTreeNode *t){
    char ch;
    ch = getchar();
    if(ch == '#'){                           //输入为#表示这里建立空二叉树，即遍历算法的空操作
        t = NULL;
    }
    else{
        t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        t->Data = ch;                        //构造根结点
        t->LChild = PreCreateBt(t->LChild);  //构造左子树
        t->RChild = PreCreateBt(t->RChild);  //构造右子树
    }
    return t;
}

//求二叉树结点个数
int Size(BinaryTreeNode *t){
    if(!t) return 0;
    return Size(t->LChild) + Size(t->RChild) + 1;
}
 
//求二叉树叶子结点个数
int Leaf(BinaryTreeNode *t){
    if(!t) return 0;
    if((t->LChild == NULL) && (t->RChild == NULL)) return 1;
    return Leaf(t->LChild) + Leaf(t->RChild);
}
 
//求二叉树的高度 
//高度从第一层开始 
int Depth(BinaryTreeNode *t){
    if(!t) return 0;
    else return 1 + max(Depth(t->LChild) , Depth(t->RChild));
}

void Exchange(BinaryTreeNode *t){
	if(!t) return;
	else 
	{ BinaryTreeNode *q = t->LChild;
        t->LChild = t->RChild;
        t->RChild = q;
	
	Exchange(t->LChild), Exchange(t->RChild);
}
	}

int main(){
    BinaryTreeNode *t = NULL;
    printf("先序遍历建树:\n");
    t = PreCreateBt(t);                     //有返回值，所以前面要加个t = ，不然后面没东西输出
    printf("\n先序遍历:\n");
	PreOrderTransverse(t);
    printf("\n\n中序遍历:\n");
    InOrderTransverse(t);
    printf("\n\n后序遍历:\n");
    PostOrderTransverse(t);
    printf("\n");
    printf("结点个数为:%d\n",Size(t));
    printf("叶子结点个数为:%d\n",Leaf(t));
    printf("二叉树的高度为:%d\n",Depth(t));
    Exchange(t);
    printf("\n交换所有左右子树后:\n\n");
    printf("先序遍历:\n");
    PreOrderTransverse(t);
    printf("\n\n中序遍历:\n");
    InOrderTransverse(t);
    printf("\n\n后序遍历:\n");
    PostOrderTransverse(t);
    printf("\n");


    return 0;
}
