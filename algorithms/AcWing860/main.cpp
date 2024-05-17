// url: https://www.acwing.com/problem/content/862/
// tutorial: https://www.acwing.com/video/289/

/*
二分图当且仅当图中不含奇数环。
而，如果染色法中没有出现矛盾（即，染过颜色的点又要染另一种颜色），则图中不含奇数环。
因此，染色法可以判断二分图。
染色法的步骤：
for(i = 1; i <= n; i++){
    if(i未染色）
        dfs(i) // dfs可以将i所在的连通块都染一遍
}
*/

#include <iostream>
#include <string.h>

using namespace std;

const int N = 100010, M = 200010; // 思考：题设里明明n和m的上限都是10^5，为什么这里M要设为200010？

int n, m;
int h[N], e[M], ne[M], idx;
int colored[N];

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool dfs(int x, int c)
{
    colored[x] = c;
    for (int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!colored[j])
        {
            if (!dfs(j, 3 - c))
                return false;
        }
        else if (colored[j] == c)
            return false;
    }
    return true;
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a); // 注意是无向图
    }

    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        if (!colored[i])
        {
            flag = dfs(i, 1);
            if (!flag)
                break;
        }
    }
    if (flag)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
