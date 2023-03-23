#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef int ElemType;
typedef struct {
	int n;               //顺序表的长度（元素个数） 
	int maxLength;       //顺序表的最大允许长度
	ElemType *element;   //存放动态分配一维数组首地址
}SeqList;

void merge(int *a,int left,int mid,int right)
{
	int temp[100];int k=0;
	int i=left,j=mid+1;
	while (i<=mid&&j<=right)
	{if(a[i]<=a[j]){temp[k++]=a[i++];}
	   else{temp[k++]=a[j++];}
	}
	
	if(i==mid+1)
	{while(j<=right)
	{temp[k++]=a[j++];
	}
	}
	
	if(j==right+1)
	{while(i<=mid)
	{temp[k++]=a[i++];
	}
	}
	for(int i=0,j=left;i<k;i++,j++)
	{a[j]=temp[i];
	}

} 

//归并排序 
void SeqListSort(SeqList *L,int left,int right)
{ if(left>=right){return;}
  int* array=L->element;
  int mid=(right+left)/2;
  SeqListSort(L, left, mid);
  SeqListSort(L, mid+1, right);
  merge(array,left,mid,right);
}

 
//顺序表初始化
int Init(SeqList *L, int maxSize) {
	L->maxLength = maxSize;
	L->n = 0;
	L->element = (ElemType*)malloc(sizeof(ElemType)*maxSize);
    if(!L->element)
    return OK;
}
//顺序表的查找
int Find(SeqList L,int i,ElemType *x){
    if(i<0||i>L.n-1){
        return ERROR;    //判断元素下标i是否越界
    }
    *x=L.element[i];     //把element[i]的值赋给x 
    return OK;
}
 
//初始化插入
int Insert(SeqList *L, int i, ElemType x) {
	int j;
	if (i<-1 || i>L->n - 1)                      //判断下标i是否越界
		return ERROR;
	if (L->n == L->maxLength)                    //判断顺序表存储空间是否已满
		return ERROR;
	for (j = L->n - 1; j > i; j--) {
		L->element[j + 1] = L->element[j];   //从后往前逐个后移元素
	}
	L->element[i + 1] = x;                       //将新元素放入下标为i+1的位置
	L -> n = L->n + 1;                           //长度+1
	return OK;
}
//顺序表的删除
int Delete(SeqList *L, int i){
    int j;
    if(i<0||i>L->n-1){                   //下标i是否越界
        return ERROR;
    }
    if(!L->n){                           //顺序表是否为空
        return ERROR;
    }
    for(j=i+1;j<L->n;j++){
        L->element[j-1]=L->element[j];   //从前往后逐个前移元素
    }
    L->n--;                              //表长减1
    return OK;
}
//顺序表输出
int Output(SeqList *L) {
	int i;
	if (!L->n)
		return ERROR;                 //判断顺序表是否为空
	for (i = 0; i <= L->n - 1; i++)
		printf("%d ", L->element[i]);  //从前往后逐个输出元素
	return OK;
}
//顺序表的撤销
void Destroy(SeqList *L){
    (*L).n=0;
    (*L).maxLength=0;
    free((*L).element);
}
int main()
{
	int i,x;
	SeqList list;
	Init(&list, 10);                   //对线性表初始化
	for (i = 0; i < 9; i++) {
		Insert(&list, i - 1, -i);   //将0-8插入到顺序表中
	}
	Output(&list);
    printf("\n");
    Delete(&list,0);                       //删除0
    printf("\n删除0号元素为:\n");
	Output(&list);
	printf("\n");
	SeqListSort(&list,0,7);         //对下标（0，7）排序 
	printf("\n从小到大排序后为:\n");
	Output(&list);
    Destroy(&list);
    return 0;
}
