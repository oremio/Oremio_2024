// url: https://www.acwing.com/problem/content/830/
// tutorial: https://www.acwing.com/video/256/

/*
模拟栈
*/

#include <iostream>

using namespace std;

const int N = 100010;

int stk[N], tt;

// 插入
void push(int x){
    stk[++tt] = x;
    //cout << tt <<endl;
}

// 弹出
void pop(){
    tt--;
}

// 判断为空
bool empty(){
    if(tt > 0) return 0;
    else return 1;
}
// 栈顶
int query(){
    return stk[tt];
}

int main()
{
    int m;
    cin >> m;
    tt = 0;
    while(m--){
        string op;
        int x;
        cin >> op;
        if(op == "push"){
            cin >> x;
            push(x);
        }
        else if(op == "pop") pop();
        else if(op == "empty")
        {
            string res = empty()? "YES" : "NO";
            cout << res << endl;
        }
        else cout << query() << endl;
    }
    return 0;
}
