#include<stdio.h>
#include<stdlib.h>
 
typedef struct PNode{
    int coef;             //系数
    int exp;              //指数
    struct PNode* link;
}PNode;
 
typedef struct{
    struct PNode *head;
}polynominal;
 

//多项式的创建
void Create(polynominal *p){
    PNode *pn,*pre,*q;
    p->head = (PNode*)malloc(sizeof(PNode));//表头节点 
    p->head->exp = -1;//表头节点的exp为-1 
    p->head->link = p->head;               //循环链表 
    for(;;){
        pn=(PNode*)malloc(sizeof(PNode));
        printf("系数:\n");
        scanf("%d",&pn->coef);
        printf("指数:\n");
        scanf("%d",&pn->exp);
        if(pn->exp<0) {free(pn);break;}//直到exp输入-1，结束 
        pre = p->head;
        q = p->head->link;
        while(q && q->exp > pn->exp){
            pre = q;
            q = q->link;
        }
        pn->link = q;
        pre->link = pn;
    }
}
//多项式输出
void Output(polynominal p){
    PNode *q;
    int flag = 1;                                   //是否为第一项
    q = p.head->link;//头结点 
    if (!q){
        return;
    }
    while(q != p.head){
        if (!flag && (q->coef > 0)) printf("+");    //在非第一项的正系数前输出+号
        flag = 0;                                   //flag置为0,表示不是第一项
        if(q->coef == 0){                           //当前项系数为0
            return;
        }
        printf("%d",q->coef);                       
        switch(q->exp){                             //判断当前项指数
            case 0:break;                          
            case 1:printf("X");break;               
            default:printf("X^%d",q->exp);break;   
        }
        q = q->link;
    }
}
//多项式的相加,结果存入qx中
void Add(polynominal *px,polynominal *qx){
    PNode *q,*q1 = qx->head,*p, *p1,*temp;    //q1指向qx的表头结点
    p = px->head->link;                       //p指向多项式px的第一个结点
    p1 = px->head;
    q = q1->link;                             
    while(p->exp >= 0){
        while(p->exp < q->exp){               
            q1 = q;
            q = q->link;
        }
        if(p->exp == q->exp){                
            q->coef = q->coef + p->coef;
            if(q->coef == 0){                 
                q1->link = q->link;           
                free(q);                      
                q = q1->link;                
                p = p->link;
            } 
            else{                             //若相加后系数不为0
                q1 = q;                       //q1后移
                q = q->link;
                p = p->link;                  //p也后移
            }
        }
        else{                                 
            temp = (PNode*)malloc(sizeof(PNode));     
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            q1 = q1->link;
            p = p->link;
        }
   }
   
}
//多项式乘法 
void Multiply(polynominal *px,polynominal *qx)
{  polynominal result;//先建立result，作为乘法结果的存放位置 
   PNode* headnode=(PNode*)malloc(sizeof(PNode)); //初始化result多项式 
   PNode* firstnode=(PNode*)malloc(sizeof(PNode));
   headnode->exp=-1;
   headnode->link=firstnode;
   result.head=headnode;
   firstnode->coef=0;
   firstnode->exp=0;
   firstnode->link=headnode;
 int rcoef,rexp;
 PNode *p1=px->head->link;//px头节点 
 PNode *p2=qx->head->link;//qx头节点 
 
 while(p1->exp >=0)//开始计算 
 {int coef1=p1->coef;
  int exp1=p1->exp;
      while(p2->exp >=0)
      { int coef2=p2->coef;
        int exp2=p2->exp;
        rcoef=coef1*coef2;
        rexp=exp1+exp2;
        polynominal temppoly;//存放每两小项相乘的计算结果 
        PNode *temphead = (PNode*)malloc(sizeof(PNode));
        temphead->exp=-1;
        temppoly.head=temphead;
        PNode *temp = (PNode*)malloc(sizeof(PNode));
		temp->coef=rcoef;
        temp->exp=rexp;
        temp->link=temphead;
        temphead->link=temp;
		Add(&temppoly,&result);//每两小项相乘的计算结果 加到result中 
		p2=p2->link;
		}
	p2=qx->head->link;//初始化p2指针位置	
	p1=p1->link;	
	}
    Output(result); //打印乘法结果     
}
int main(){
    polynominal p,q;
    int x;
    printf("输入第一个多项式:\n");
    Create(&p);
    printf("\n输入第二个多项式:\n");
    Create(&q);
    printf("\n第一个多项式为:\n");
    Output(p);
    printf("\n第二个多项式为:\n");
    Output(q);
    printf("\n");
    printf("\n相乘为:\n");
    Multiply(&p,&q);
    printf("\n相加为:\n");
    Add(&p,&q);
    Output(q);    
    return 0;
}
