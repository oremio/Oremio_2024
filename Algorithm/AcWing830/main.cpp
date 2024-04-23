// url: https://www.acwing.com/problem/content/832/
// tutorial: https://www.acwing.com/video/258/

/*
单调栈：
顾名思义，栈内元素具有单调性
本题场景：需要输出序列中每个数左边第一个比它小的数
*/

#include <iostream>

using namespace std;

const int N = 100010;

int n;
int st[N], tt;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) { // 可以边读数据边处理
        int x;
        cin >> x;
        while (tt && st[tt] >= x)
            tt--;
        if(tt)
            cout << st[tt] << ' ';
        else
            cout << -1 << ' ';
        st[++tt] = x;
    }
    return 0;
}
