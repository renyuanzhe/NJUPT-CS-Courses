
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;
int count = 0;  //从 0 开始计数
int n;  //正整数
int elements[100];  //存因子
int matrixs[100][100] = {0};  //初始化为 0 

void element()//分解n的因数 
{
    cout << "整数 " << n << " 的因子: ";
    for(int i = 1; i <= n/2; i++){ 
        if(n % i == 0){
            elements[count++] = i; 
            cout << i << ", ";
        }
    }
    elements[count] = n;  
    cout << n << endl << endl;
}



//盖住关系
void cover(){
	//关系矩阵初始化
	for(int i = 0; i < count+1; ++i){
		for(int j = 0; j < count+1; ++j){
			if(elements[j] % elements[i] == 0){  //如果满足整除关系，就设为 1
				matrixs[i][j] = 1;
			}
		}
	}
	//开始判断
	for(int i = 0; i < count+1; ++i){
		for(int j = 0; j < count+1; ++j){
			for(int k = 0; k < count+1; ++k){
				matrixs[k][k] = 0;  //先去掉自反性
				if(matrixs[i][j] && matrixs[j][k]){
					matrixs[i][k] = 0;  //再去掉传递性
				}
			}
		}
	}
	cout << "盖住关系是: {";
	for(int i = 0; i < count+1; ++i){
		for(int j = 0; j < count+1; ++j){
			if(matrixs[i][j]){  //除去前面去掉的，其他就满足盖住关系了
				cout << " <" << elements[i] << "," << elements[j] << ">";
			}
		}
	}
	cout << " }" << endl;
}

//求最大公约数
int gcd(int x, int y){
	int m;
	//辗转相除法
	while(m != 0){
		m = x % y;
		x = y;
		y = m;
	}
	return x;
}

//判断有补格
void IFcomplemented_lattice(){
    bool flag;
    int Gcd, Lcm;
    for(int i = 1; i < count-1; i++){  //判断有补格时不需要考虑最大元和最小元 
        flag = false; // 初始化 flag = false 
        for(int j = 1; j < count-1; j++){
            if(i == j)
                continue;
            Gcd = gcd(elements[i], elements[j]); // 最大公约数，即最大下界
            Lcm = elements[i]*elements[j] / Gcd; // 最小公倍数，即最小上界
            if(Gcd == 1 && Lcm == n){ // 若是补元，flag = true 
                flag = true;
                break;
            }
            if(!flag){ // 若存在元素没有补元，则此格不是有补格
                cout << "这不是有补格" << endl;
                return;
            } 
        }
    }
    // 若所有元素均有补元，则此格是有补格
    cout << "这是有补格" << endl;
    return;
}


int main(){
	cout << "请输入一个正整数: ";
	cin >> n;
	cout << endl;
    element();
	cover();
	cout << endl;
	IFcomplemented_lattice();
	cout << endl;
	return 0;
}




