#include<iostream>
#include <stack>
#include <vector>
#include<queue>
using namespace std;

void print_situation(queue<int> enter,vector< stack<int> > temp, queue<int> ready,int k)//这里采用传值方式 ,打印各个区域的情况 
{   
    cout<<endl; 
	cout<<"入轨区（左边为队列首）：";
	while(!enter.empty())
	{
		cout<<enter.front();
		enter.pop();
	}

	for(int j=0;j<k;j++)
    {   stack<int> s=temp[j];
        cout<<endl<<j+1<<"号缓冲区（左边为缓冲区顶部）："; 
        while(!s.empty())
        { 
          cout<<s.top();
          s.pop();
	    }	
	}
	cout<<endl; 
	
	cout<<"出轨区（左边为队列首）：";
	while(!ready.empty())
	{
		cout<<ready.front();
		ready.pop();
	}
	
	
	cout<<endl<<"-----------------------------------------"<<endl<<endl;
	//getchar(); 
}	
	


int solution(int *train,int num,int k)// num为车箱数， k为缓冲区个数 
{   vector< stack<int> > temp;//缓冲区 
    for(int j=0;j<k;j++)
    {   stack<int> s;
    	temp.push_back(s);
	}
	queue<int>enter;//入轨区
	queue<int>ready;//出轨区 
	for(int i=0;i<num;i++)
	{
		enter.push(train[i]);//初始化入轨区 
    }
    
	int correct_id=1;//按顺序下应该一个出轨车厢的id 
	int min_id=100000;//待在缓冲区里的最小id，初始化为比最大编号更大的数 
	int min_k_id=-1;///min_id车厢对应的缓冲区号（下标是从0开始的） ，这里初始化为一个不可能的数-1 
	print_situation(enter,temp,ready,k);
	for(int i=0;i<num;i++)
	{
		int id=train[i];
		if(id==correct_id)//如果当前车厢正好可以接上出轨区 
		{   
		    enter.pop(); //驶离入轨区 
		    ready.push(correct_id);//更新出轨区 
		    cout << "操作：将车厢 " << id << " 从入轨区 " "移至出轨区 "  << endl;
		    print_situation(enter,temp,ready,k);
		    
			correct_id=id+1;//只要有车厢进入出轨取，correct_id就要增加 
			
			while(min_id==correct_id)//如果缓冲区里最小的车厢id可以接上出轨区 
			{ 
			 
			 //出栈，更新 
			 temp[min_k_id].pop();//出栈(移入出轨区) 
			 ready.push(correct_id);//更新出轨区 
			 cout << "操作：将车厢 " << min_id << " 从缓冲区 " << min_k_id << " 移至出轨区" << endl;
			 print_situation(enter,temp,ready,k);
			 
			 min_id=100000; //先假设 min_id为比最大编号更大的数 
			 for (int j = 0; j <k; j++)//遍历所有的缓冲区，更新出栈后的缓冲区 
			 {
                  if (!temp[j].empty() ) //如果遍历到的不是空栈 
				  {     
				        if(temp[j].top() < min_id)////如果栈顶元素比当前的min_id小 
                        {
						  min_id = temp[j].top();
                          min_k_id = j;
                        }
				  }
             }
             correct_id++; //只要有车厢进入出轨取，correct_id就要增加
			}
		}
		else//如果当前车厢不能正好接上出轨区，则要将其入栈 
		{   int Best_id = 100000; // 缓冲区中最优插入位置是Best_id车厢的上面(最小的大于id车厢).初始值设为比num还大 
		    int Best_k_id = -1; //最优插入位置 （哪个缓冲区） 
            
			for(int j=0;j<k;j++)
			{ 
			  
			  if (!temp[j].empty() ) //如果遍历到的不是空栈 
			  {
			  	if (id < temp[j].top() && temp[j].top() < Best_id) //要找出缓冲区中刚大于id的那个车厢和位置，然后把新车厢放在上面 
				  {
                     Best_id=temp[j].top(); 
                     Best_k_id=j;
			      }
				
			  }
			  else //遍历到空栈 
			  {
			  	if (Best_k_id==-1)//还没找到可以插入的位置 
			  	{
				 Best_k_id=j; 
			    }
			  }
			  
		   }
		   if(Best_id==100000&&Best_k_id==-1)
		   {
		   	 cout<<"缓冲区数量不够"<<endl; 
		   	 return 0;
		   }
		   else//缓冲区数量够 
		   {
		     enter.pop(); //驶离入轨区 
		     temp[Best_k_id].push(id);//把id车厢插入缓冲区最优位置 
		     cout << "操作：将车厢 " << id << " 从入轨区 " "移至缓冲区 " << Best_k_id << endl;
		     print_situation(enter,temp,ready,k);
		   
		     if(id<min_id)//入栈后更新缓冲区的最小车厢id和对应的缓冲区号 
		     { 
		      min_id=id;
		      min_k_id=Best_k_id;
		     }
		     
	       }
	   }
   }
   return 1; 
}

int main()
{   //int train[9]={5,8,1,7,4,2,9,6,3};
    int train[9]={3,6,9,2,4,7,1,8,5};
    int number=9;//车箱数 
    int k;//缓冲区数量 
    cout<<"请输入缓冲区数量"<<endl;
    cin>>k;
    cout<<endl;
    getchar();//吃掉回车符 
    
	if(solution(train,number,k)==1)
	{
		cout<<endl<<"调度成功"; 
	}
	else
	{
		cout<<endl<<"调度失败";
	}
	cout<<endl;
    system("pause");
	return 0;
}
