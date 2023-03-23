#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <algorithm>
#include<queue> 
using namespace std;

int isBST=1;//是否为BST 
int node_arr[100]={0};//树中节点存入数组 
int node_num=0;//树中节点的数量
 
typedef struct BinaryTreeNode{
    int value;                                //二叉树节点的值 
    struct BinaryTreeNode *LChild, *RChild;   //二叉树当前节点的左右孩子 
}BinaryTreeNode;
 
 
//先序遍历
void PreOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    printf("%d ",t->value);           //打印输出根结点，此处可以定义其他操作
    PreOrderTransverse(t->LChild);  //然后先序遍历左子树
    PreOrderTransverse(t->RChild);  //最后先序遍历右子树
}
//中序遍历
void InOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    InOrderTransverse(t->LChild);  //中序遍历根结点的左子树
    printf("%d ",t->value);          //打印输出根结点，此处可以定义其他操作
    InOrderTransverse(t->RChild);  //最后中序遍历根结点的右子树
}
//后序遍历
void PostOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    PostOrderTransverse(t->LChild);  //后序遍历根结点的左子树
    PostOrderTransverse(t->RChild);  //然后后序遍历根结点的右子树
    printf("%d ",t->value);            //最后打印输出根结点，此处可以定义其他操作
}
void Transverse(BinaryTreeNode *t) //三种遍历 
{   printf("\n先序遍历:\n");
	PreOrderTransverse(t);
    printf("\n中序遍历:\n");
    InOrderTransverse(t);
    printf("\n后序遍历:\n");
    PostOrderTransverse(t);
    printf("\n");
    printf("\n");
}

BinaryTreeNode *PreCreateBt_IsBST(BinaryTreeNode *t,int parent_value,int flag){
    int ch;
    //scanf("%d",&ch);
    cin>>ch;
    getchar();
    if(ch == -1)//输入为-1表示这里建立空二叉树，即遍历算法的空操作
	{                           
        t = NULL;
    }
    else{
        t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        t->value = ch;                        //构造根结点
        
        node_arr[node_num++]=ch;//把新创建节点的值存入节点数组
		 
        if(flag==2)//当前构建的节点是根节点 
        {
        	t->LChild = PreCreateBt_IsBST(t->LChild,t->value,0);  //构造左子树
            t->RChild = PreCreateBt_IsBST(t->RChild,t->value,1);  //构造右子树
		}
		if(flag==0)//当前构建的节点是左子节点
        {   
            if(t->value > parent_value)// 当前构建的节点的值大于其父节点 
            { 
			   isBST=0; //不再是二叉搜索树 
			}
        	t->LChild = PreCreateBt_IsBST(t->LChild,t->value,0);  //构造左子树
            t->RChild = PreCreateBt_IsBST(t->RChild,t->value,1);  //构造右子树
		}
		if(flag==1)//当前构建的节点是右子节点
        {   
            if(t->value < parent_value)// 当前构建的节点的值小于其父节点 
            { 
			  isBST=0; //不再是二叉搜索树 
			}
        	t->LChild = PreCreateBt_IsBST(t->LChild,t->value,0);  //构造左子树
            t->RChild = PreCreateBt_IsBST(t->RChild,t->value,1);  //构造右子树
		}   
    }
    return t;
}


int Balanced_height(BinaryTreeNode* root) {//如果以root为根节点的二叉树平衡，返回以root为根的树的高度（只有一个根节点的情况算高度1）。否则返回-1 
    if (root == NULL) {
        return 0;
    }
    int leftHeight = Balanced_height(root->LChild);//计算左子树高度 
    int rightHeight = Balanced_height(root->RChild);//计算右子树高度 
    //这里采用后序遍历，节约时间 
    if (leftHeight == -1 || rightHeight == -1 || fabs(leftHeight - rightHeight) > 1) 
	{//leftHeight, rightHeight=-1代表 root的子树已经不平衡 ，这时就把不平衡信息传递上去 
        return -1; //返回-1既包含左右子树本身不平衡的情况，又包含左右子树因为高度不等导致当前节点不平衡的情况 
    } 
	else {
        return fmax(leftHeight, rightHeight) + 1;
    }
}
bool isBalanced(BinaryTreeNode* root) {//判断二叉树是否平衡 
    return Balanced_height(root) >= 0;
}


BinaryTreeNode* sortedArrayToAVL_helper(int* nums, int left, int right) {//将nums数组的[left，right区间]重建成AVL
    if (left > right) {
        return NULL;
    }
    
    int mid = (left + right) / 2;// 总是选择中间位置左边的数字作为根节点

    BinaryTreeNode* root = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    root->value = nums[mid];
    root->LChild = sortedArrayToAVL_helper(nums, left, mid - 1);
    root->RChild = sortedArrayToAVL_helper(nums, mid + 1, right);
    return root;
}
BinaryTreeNode* sortedArrayToAVL(int* nums, int numsSize) {
    return sortedArrayToAVL_helper(nums, 0, numsSize - 1);
}

//求二叉树的高度
int Depth(BinaryTreeNode *t){
    if(!t) return 0;
    // else return (1 + Depth(t->LChild) > Depth(t->RChild) ? Depth(t->LChild) : Depth(t->RChild));
    else return 1 + max(Depth(t->LChild) , Depth(t->RChild));
}

void Print_Tree(BinaryTreeNode *t)//可视化打印二叉树结构 
{

    if(t==NULL) return; 
    
	queue<BinaryTreeNode*> q_node;//存放节点的指针
	queue<int> q_value;//存放节点的值 
	 
    q_node.push(t);
    q_value.push(t->value);//这里先插入根节点 
    int depth=1;//二叉树当前深度，根节点深度为1
	int real_depth=Depth(t);//二叉树真实深度 
    int cnt=1;//插入节点的数量 
    
    while(!q_node.empty()&&depth<=real_depth)//要满足当前遍历了的二叉树深度小于等于实际深度 
    {   
	   if(cnt>pow(2,depth)-1)//满二叉树情况下，节点数=2^层数 -1 
        {
		  depth++;   //根节点为第一层 ，不断更新深度 
		}
		
        if(q_node.front()->LChild!=NULL)//如果当前节点的左孩子非空，把左孩子入队列 
        {
              q_node.push(q_node.front()->LChild);
              q_value.push(q_node.front()->LChild->value);//左孩子的值 
              cnt++; //遍历了的节点数+1 
        }
        else//如果当前节点的左孩子为空 ，构造一个空节点（value=0），入队列 
        {
         BinaryTreeNode* t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));//构造空结点
         t->value = -1;                        
         t->LChild=NULL;
         t->RChild=NULL;
         q_node.push(t);
         q_value.push(t->value);
         cnt++;
		}
		
		
        if(q_node.front()->RChild!=NULL)
        {
              q_node.push(q_node.front()->RChild);
              q_value.push(q_node.front()->RChild->value);
              cnt++; 
        }
        else//如果当前节点的右孩子为空 ，构造一个空节点（value=0），入队列 
        {
         BinaryTreeNode* t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode)); //构造空结点
         t->value = -1;                       
         t->LChild=NULL;
         t->RChild=NULL;
         q_node.push(t);
         q_value.push(t->value);
         cnt++;
		}
         
         q_node.pop();//当前节点处理完，出队列 
    
	}
	
    for (int i = 1; i <= real_depth; i++) 
	{
        int layer_node_num = pow(2,i-1);//第i层有几个节点 
        int layer_margin_num = pow(2,real_depth-i)-1;//第i层每个节点两边有几个空格 
        for (int j = 1; j <=layer_node_num; j++)//这一层有几个空格 
         {
            for(int k=1;k<=layer_margin_num;k++)
            {
			  cout<<' ';
			  cout<<' ';
			}
		
			cout<<q_value.front();
			for(int k=1;k<=layer_margin_num;k++)
            {
			  cout<<' ';
			  cout<<' ';
			}
			
			cout<<' ';
			cout<<' ';
			
            q_value.pop();
         }
        printf("\n");
    }
    
}

int main(){
	cout<<"先序遍历建树，其中空节点用-1表示，每个节点之间有空格" <<endl; 
    BinaryTreeNode *t = NULL;            
    t =PreCreateBt_IsBST(t,100,2);   //第二个参数随意，这里我输入了100 
    
	cout<<endl;
	Print_Tree(t) ;//可视化 
	Transverse(t); //打印三种遍历 
      
    if(isBST&&isBalanced(t))
    {cout<<"该树是AVL树"<<endl; 
	}
	
	if (isBST==0||isBalanced(t)==0)
	{   cout<< endl<<"------------------------------------"<<endl<<endl;
	    cout<< "该树不是AVL树的原因：";
		if(isBST==0) 
		{ cout<<"不是二叉搜索树;"; 
		}
		if(isBalanced(t)==0) 
		{ cout<<"不满足平衡要求;"<<endl; 
		}
     cout<<endl; 
	 cout<<endl<<"下面将该树重建成AVL树"<<endl;
	 sort(node_arr,node_arr+node_num);//节点数组排序 
	 t=sortedArrayToAVL(node_arr,node_num);//将排序好的节点数组重建成二叉搜索树 
	 
	 cout<<endl;
	 Print_Tree(t); //可视化 
	 Transverse(t); //打印三种遍历
	}
	cout<<endl;
    system("pause");
    
	return 0;
}
