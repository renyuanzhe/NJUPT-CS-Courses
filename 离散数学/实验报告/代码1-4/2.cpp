#include <iostream>
using namespace std;

#define MAX 1000
bool flag_ref, flag_irr, flag_sym, flag_dis, flag_tra;  //判断自反性、反自反性、对称性、反对称性、传递性的 flag
int matrix[MAX][MAX];
int n;


//自反性
void Reflexive(){
	flag_ref = true;
	for(int i = 0; i < n; ++i){
		if(matrix[i][i] != 1){  //只要有一个对角线元素为 0：即不满足
			flag_ref = false;
			break;
		}
	}
}


//反自反性
void Irreflexive(){
	flag_irr = true;
	for(int i = 0; i < n; ++i){
		if(matrix[i][i] == 1){  //只要有一个对角线元素为 1：即不满足
			flag_irr = false;
			break;
		}
	}
}


//对称性
void Symmetrical(){
	flag_sym = true;
	for(int i = 0 ; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(matrix[i][j] != matrix[j][i]){  //只要有一对对称元素不相等：即不满足对称性
				flag_sym = false;
				break;
			}
		}
	}
}


//反对称性
void Dissymmetrical(){
	flag_dis = true;
	for(int i = 0 ; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(matrix[i][j] == matrix[j][i]&&matrix[j][i]==1&&i!=j){  //只要有一对对称元素相等且等于1：即不满足反对称性
				flag_dis = false;
				break;
			}
		}
	}
}


//传递性
void Transitive(){
	
	flag_tra = true;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k){
				if(matrix[i][j] && matrix[j][k] && !matrix[i][k]){  //前两个为 1，第三个为 0
					flag_tra = false;
					break;
				}
			}
		}
	}
}


//求闭包 warshall
void Closure(){
	for(int i = 0; i < n; ++i){  //列
		for(int j = 0; j < n; ++j){  //行
			if(matrix[j][i] == 1){
				for(int k = 0 ; k < n; ++k){
					matrix[j][k]=matrix[j][k]|matrix[i][k];
					 /* if(matrix[j][k] == 0 && matrix[i][k] == 0){
						matrix[j][k] = 0;
					}
					else if(matrix[j][k] == 0 && matrix[i][k] == 1){
						matrix[j][k] = 1;
					}
					else if(matrix[j][k] == 1 && matrix[i][k] == 0){
						matrix[j][k] = 1;
					}
					else if(matrix[j][k] == 1 && matrix[i][k] == 1){
						matrix[j][k] = 1;
					}*/
					
				}
			}
		}
	}
}
int bb1[MAX][MAX];
void zfbb( int (*a)[1000])
{    
        for(int i=0;i<n;i++)
		  {for(int j=0;j<n;j++)
		{ bb1[i][j]=a[i][j];}}
	
	for(int i=0;i<n;i++)
	{
		if(!bb1[i][i])
		{
			bb1[i][i]=1;
		}
	}
	cout<<"自反闭包为："<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<bb1[i][j]<<"  ";
		cout<<endl;
	}
}

int bb2[MAX][MAX];
void dcbb( int (*a)[1000])
{   
        for(int i=0;i<n;i++)
		  {for(int j=0;j<n;j++)
		{ bb2[i][j]=a[i][j];}}
	
		for(int i=0;i<n;i++)
		  for(int j=0;j<n;j++)
			if(bb2[i][j]!=bb2[j][i])
			{
				bb2[i][j]=1;
				bb2[j][i]=1;
			}
	cout<<"对称闭包为："<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<bb2[i][j]<<"  ";
		cout<<endl;
	}
}

int main(){

	cout << "请输入集合元素个数:" << endl;
	cin >> n;
	
	cout << "请输入关系矩阵:" << endl;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> matrix[i][j];
		}
	}
	cout << endl;
	Reflexive();
	Irreflexive();
	Symmetrical();
	Dissymmetrical();
	Transitive();
	cout << "集合的性质:" << endl; 
	if(flag_ref == true){
		cout << "自反性" << endl;
	}
	if(flag_irr == true){
		cout << "反自反性" << endl;
	}
	if(flag_sym == true){
		cout << "对称性" << endl;
	}
	if(flag_dis == true){
		cout << "反对称性" << endl;
	}
	if(flag_tra == true){
		cout << "传递性" << endl;
	}
	cout << endl;
	zfbb(matrix);
	dcbb(matrix); 
	cout << "传递闭包为:" << endl;
	Closure();
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
