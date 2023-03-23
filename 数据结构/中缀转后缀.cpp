#include<iostream>
#include<string>
#include<stack>

using namespace std;

int Priority(char op) {                 //给运算符优先级排序（栈内优先顺序） 
    int priority;
    if (op == '*' || op == '/')
        priority = 2;
    if (op == '+' || op == '-')
        priority = 1;
    if (op == '(')
        priority = 0;
    return priority;
}
bool Transform(string &str,string &str1) {   
    stack<char> s;                   //定义一个char类型的栈s
    int i;
    for (i = 0; i<str.size(); i++) {
        if ((str[i] >= '0' && str[i] <= '9')||(str[i]>='a'&&str[i]<='z')) {    //如果是操作数，直接入栈
            str1+=str[i];
        }
        else {                        //否则不是数字
            if (s.empty())            //栈空则入站
                s.push(str[i]);
            else if (str[i] == '(')   //左括号入栈
                s.push(str[i]);
            else if (str[i] == ')') {  //如果是右括号，只要栈顶不是左括号，就弹出并输出
                while (s.top() != '(') {  
                    str1+= s.top();
                    s.pop();
                }
                s.pop();                 //弹出左括号，但不输出
            }
            else {
                while (Priority(str[i]) <= Priority(s.top())) { //栈顶优先级大于等于当前运算符，则弹出 
                    str1+= s.top();
                    s.pop();
                    if (s.empty())      //栈为空，停止
                        break;
                }
                s.push(str[i]);   //把当前运算符入栈
            }
        }
    }
    while (!s.empty()) {      //最后，如果栈不空，则弹出所有元素并输出
        str1+= s.top();
        s.pop();
    }
    return true;
}
int main() {                
    string infix;
    string postfix;
    cout << "请输入中缀表达式：" << infix << endl;
    cin >> infix;
    Transform(infix,postfix);
    cout << "后缀表达式为：" << postfix << endl;
    return 0;
}
