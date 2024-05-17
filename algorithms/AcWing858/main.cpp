// url: https://www.acwing.com/problem/content/860/
// tutorial: https://www.acwing.com/video/287/

/*
注意，此处的dist和dijkstra不同，后者是到起始点的distance，Prim则是到Prim集合的distance
1.dist[1] = 0, 其他正无穷
2.循环n次，n为点集V的基数
2-1.计算各个点的dist，将距离最近的点tmp加入Prim的点集V'
2-2.用tmp更新其他点的dist
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int N = 510, INF = 0x3f3f3f3f;

int n, m;
int g[N][N];
int dist[N];
bool isPrim[N];

int prim()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        int tmp = -1;
        for (int j = 1; j <= n; j++)
            if (!isPrim[j] && (tmp == -1 || dist[tmp] > dist[j]))
                tmp = j;

        if (dist[tmp] == INF)
            return INF;
        isPrim[tmp] = true;
        res += dist[tmp];

        for (int j = 1; j <= n; j++)
            if (!isPrim[j])
                dist[j] = min(dist[j], g[tmp][j]);
    }
    return res;
}

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
    {
        cin.rdbuf(file.rdbuf());
    }

    cin >> n >> m;

    memset(g, 0x3f, sizeof g);

    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = min(g[u][v], w); // 无向图时的邻接矩阵是对称矩阵
    }

    int p = prim();
    if (p != INF)
        cout << p;
    else
        cout << "impossible";
    return 0;
}
