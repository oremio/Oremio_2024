// url: https://www.acwing.com/problem/content/831/
// tutorial: https://www.acwing.com/video/257/

/*
模拟队列
*/

#include <iostream>

using namespace std;

const int N = 100010;
int m;
int q[N], hh, tt = -1; // 为空的情况下，队尾在队头的左边的1个位置

void push(int x)
{
    q[++tt] = x;
}

void pop()
{
    hh++;
}

bool empty()
{
    if (hh <= tt)
        return false;
    else
        return true;
}

int query()
{
    return q[hh];
}

int main()
{

    cin >> m;
    while (m--)
    {
        string op;
        int x;
        cin >> op;
        if (op == "push")
        {
            cin >> x;
            push(x);
        }
        else if (op == "pop")
            pop();
        else if (op == "empty")
            cout << (empty() ? "YES" : "NO") << endl;
        else
            cout << query() << endl;
    }
    return 0;
}
