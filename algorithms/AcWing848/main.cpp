// url: https://www.acwing.com/problem/content/850/
// tutorial: https://www.acwing.com/video/280/

/*
1. 将所有入度为0的点加入queue
2. while queue非空
2-1. tmp = queue队头的点
2-2. 枚举tmp的所有出边，然后删掉
2-3. 被删掉的边的另一个点的入度减1，如果这个点的入度减成0了，加入队列
*/

#include <iostream>
#include <string.h>

using namespace std;

const int N = 100010;
int n, m;
int h[N], e[N], ne[N], idx; // 邻接表, 要注意的是，h的下标就是顶点
int q[N];                   // 队列
int degsub[N];              // 入度

void add(int a, int b)
{                   // 头插
    e[idx] = b;     // e
    ne[idx] = h[a]; // ne
    h[a] = idx;     // h
    idx++;          // idx
}

bool topsort()
{
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i++) // 注意i要从1开始计数
        if (!degsub[i])
            q[++tt] = i;
    while (hh <= tt)
    {
        int tmp = q[hh++];
        for (int i = h[tmp]; i != -1; i = ne[i])
        {
            int j = e[i];
            degsub[j]--;
            if (degsub[j] == 0)
                q[++tt] = j;
        }
    }
    return tt == n - 1;
}

int main()
{
    cin >> n >> m;

    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
        degsub[b]++; // 不要忘了更新入度
    }
    if (topsort())
    {
        for (int i = 0; i < n; i++)
            cout << q[i] << ' ';
        cout << endl;
    }
    else
        cout << -1 << endl;
    return 0;
}
