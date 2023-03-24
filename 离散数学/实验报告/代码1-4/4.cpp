#include <iostream>
#include <stack>
#include<cstring> 

#define INF 100000

using namespace std;

int G[100][100];
int m;int n;//m为边数,n为点数，

int path[50], k = 0;  //记录欧拉路的路径
int visitEdge[100][100];
bool visted[50];  //标记点是否被访问
int begin1;  //判是否为连通图，搜索的起点

stack<int> s;//fluery

int fa[INF]={0};//并查集

void allDfs(int x,int edgeNumber=0)//dfs输出全部欧拉路 
{if(edgeNumber==0){k=0;} //每次从一个新的起点开始时，初始化 
   path[k++]=x;
  if (edgeNumber==m)
  {
    for(int i=0;i<m+1;i++)
    {cout<<path[i]<<" ";
	}
	cout<<endl;
	return;
  }
  else 
  {for(int i=0;i<n;i++)
  {
   if(G[x][i])
  
     { G[x][i]--;G[i][x]--;
       
      allDfs(i,edgeNumber+1);
      G[x][i]++;G[i][x]++;
       k--;
      }
  }
  }
}

void DFS(int x)
{   
    visted[x] = true;
    for(int i = 0; i < n; i++)
        if(!visted[i] && G[x][i])
            DFS(i);
}   
 
//从所设定的起点深度优先遍历图，若有一个点没被访问，则为非连通图
bool Judge()//dfs判断图连通性
{
    DFS(0);
    for(int i = 0; i < n; i++)
        if(!visted[i])
            return false;
    return true;
}

void init()//并查集初始化，每个结点各自为一个集合
{
    for (int i = 0; i < n; ++i)
        fa[i] = i;
}

int find(int x)//寻找x的祖先
{    

    if(fa[x]==x) return fa[x];
    else 
	{fa[x]=find(fa[x]);//路径压缩
	  return fa[x];}
		
}
int unionn(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx==fy) return 0;
    fa[fx]=fy;
    return 1;
}

void dfsfleury(int x)
{
    s.push(x);

    for(int i = 0; i < n; i++)
    {
        if(G[i][x] > 0)
        {
            G[x][i] --;
            G[i][x] --;
            dfsfleury(i);
            break;
        }
    }
}

void fleury(int x)
{
    int b;
    s.push(x);

    while(!s.empty())
    {
        b = 0;
        for(int i =0 ; i < n; i++)
        {
            if(G[s.top()][i] > 0)
            {
                b = 1;
                break;
            }
        }
        if(b == 0)//栈顶元素没有边与i相连 ，则输顶元素出栈 
        {
            cout << s.top() << " ";
            s.pop();
        }
        else//栈顶元素与i相连，则以该元素为起点，遍历一条路径直到无路，该路径入栈，路径上的所有边删除 
        {
            int t = s.top();
            s.pop();
            dfsfleury(t);
        }
    }
}

int main()
{   int num = 0;//奇数结点个数
    int start[50]= {0};int j=0;//欧拉路开始结点 和数组指针j 
    cout<<"请输入点数和边数"<<endl;
    
    while(cin >> n >> m,n)
    {   
		int l=0;//用于连通性判断 
        while(!s.empty())//初始化栈s
            s.pop();
        memset(G,0,sizeof(G));
		init();//初始化并查集
		k=0;j=0;num = 0;//初始化k ,j,num
		cout<<"请输入各边（结点编号从0开始）"<<endl;
        for(int i = 0; i < m; i++)
        {
            int a,b;

            cin >> a >> b;
            G[a][b] ++;
            G[b][a] ++;
			l+=unionn(a,b); 
        }
     if(l!=n-1)//如果一个图是连通图，其各结点的最小生成树的边数为点数-1 即n-1 
	{cout << "Non-connected graph" << endl;
	 cout<<"请输入点数和边数"<<endl;
       continue; 
	 } 
	  /*if(!Judge())// dfs判断连通性 
    {
        cout << "Non-connected graph" << endl;
		cout<<"请输入点数和边数"<<endl;
         continue;   
    }*/
        
        for(int i = 0; i <= n-1; i++)
        {
            int d = 0;//每个点度数
            for(int j = 0; j <= n-1; j++)
                d += G[i][j];
            if(d % 2 == 1)//如果度数为奇数
            {   num++;
                if(num>2){break;}
                start[j++] = i;
               
            }
        }
		
        if(num == 0 || num == 2)
            {
		     if(num == 0)
			 {cout << "欧拉回路是" << endl;
			 for(int i=0;i<n;i++)
			   {allDfs(i,0);
			   //fleury(i);
			   }
			}
			  else 
			 {cout << "欧拉路是（无回路）" << endl;
			   for(int i=0;i<2;i++)
			   {allDfs(start[i],0);
			   //fleury(start[i]);
			   }
			   }
			 
			  
		     
			 cout<<endl;}
        else
            cout << "No Euler path" << endl;

		cout<<"请输入点数和边数"<<endl;
    }
    return 0;
}