#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
#define ERROR 0
#define OK 1
 
typedef struct Node {
	ElemType element;     //结点的数据域
	struct Node * link;   //结点的指针域
}Node;
 
typedef struct {
	struct Node* head;    //表头结点
	int n;
}HeaderList;
 
//带表头结点单链表的初始化
int Init(HeaderList *h) {
    h->head=(Node*)malloc(sizeof(Node));      
    if(!h->head){
        return ERROR;
    }
	h->head->link = NULL;                    
	h->n = 0;
	return OK;
}
 
 
//带表头结点单链表的查找
int Find(HeaderList *h,int i,ElemType *x){
    Node *p;
    int j;
    if(i<0||i>h->n-1){
        return ERROR;
    }
    p=h->head->link;
    for(j=0;j<i;j++){
        p=p->link;
    }
    *x=p->element;
    return OK;
}
 
 
//带表头结点单链表的插入
int Insert(HeaderList *h, int i, ElemType x) {
	Node *p, *q;
	int j;
	if (i<-1 || i>h->n - 1)
		return ERROR;
	p = h->head;                     
	for (j = 0; j <= i; j++) {
		p = p->link;
	}
	q = (Node*)malloc(sizeof(Node));  
	q->element = x;
	q->link = p->link;                
	p->link = q;
	h->n++;
	return OK;
}
 
 
//带表头结点单链表的删除
int Delete(HeaderList *h,int i){
    int j;
    Node *p,*q;
    if(!h->n){
        return ERROR;
        if(i<0||i>h->n-1){
            return ERROR;
        }
    }
    q=h->head;
    for(j=0;j<i;j++){
        q=q->link;
    }
    p=q->link;
    q->link=p->link;                //从单链表中删除p所指结点
    free(p);                        
    h->n--;
    return OK;
}
//带表头结点单链表的输出
int Output(HeaderList *h) {
	Node *p;
	if (!h->n)
		return ERROR;
	p = h->head->link;
	while (p) {
		printf("%d ",p->element);
		p = p->link;
	}
	return OK;
}
//带表头结点单链表的撤销
void Destroy(HeaderList *h){
    Node *p,*present=h->head; 
    
    while(present)
    {p=present->link;
    free(present);
    present=p;
	}
}
int main()
{
	int i;
	int x;
	HeaderList list;
	Init(&list);
	for (i = 0; i < 11; i++) {
		Insert(&list, i - 1, i);    //插入0~10
	}
	Output(&list);
    Delete(&list,0);                //删除0
    printf("\n删除下标0的元素是:\n");
    Output(&list);
    Find(&list,1,&x);               //查找下标为1的元素
	printf("\n下标1的元素是:");
	printf("%d ",x);
    Destroy(&list);
    return 0; 
}
