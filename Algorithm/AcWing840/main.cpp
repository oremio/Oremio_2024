// url: https://www.acwing.com/problem/content/842/
// tutorial: https://www.acwing.com/video/266/

#include <iostream>
#include <cstring>

using namespace std;

/* 拉链法
const int N = 100003; // 质数

int h[N], e[N], ne[N], idx;

void insert(int x)
{
    int k = (x % N + N) % N;
    e[idx] = x;

    // 单链表头插
    ne[idx] = h[k];
    h[k] = idx ++;
}

bool find(int x)
{
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i])
        if(e[i] == x)
            return true;
        return false;
}
*/

// 开放寻址法
const int N = 200003, null = 0x3f3f3f3f;

int h[N];

int find(int x)
{
    int k = (x % N + N) % N;
    while (h[k] != null && h[k] != x)
    {
        k ++ ;
        if (k == N) k = 0; // 注意这个边界问题！
    }
    return k;
}

int main()
{
    int n;
    cin >> n;

    memset(h, 0x3f, sizeof h); // 对于整形数组，一般只用来初始化0、-1、0x3f这几个数字，其他的建议使用循环初始化

    while (n -- )
    {
        char op;
        int x;
        cin >> op >> x;

        int k = find(x);
        if (op == 'I') h[k] = x;
        else
        {
            if (h[k] != null) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
}
