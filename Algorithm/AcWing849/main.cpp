// url: https://www.acwing.com/problem/content/851/
// tutorial: https://www.acwing.com/video/281/
// TC: n^2

/*
1.dist[1] = 0, 其他正无穷
2.循环n次，n为点集V的基数
2-1.计算各个点的dist，将距离最近的点tmp加入迪克斯特拉的点集V'
2-2.用tmp更新其他点的dist
*/

#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

const int N = 510;

int n, m;
int g[N][N]; // 500个点，10万条边，稠密图，用邻接矩阵
int dist[N];
bool isShortest[N]; // 是否在迪克斯特拉的点集V'可以用一个bool数组来表示

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for (int i = 0; i < n; i++)
    {
        int tmp = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!isShortest[j] && (tmp == -1 || dist[tmp] > dist[j])) // 要么tmp == -1，也就是第一个发现的幸运儿，要么就是距离最近的点
                tmp = j;
        }
        isShortest[tmp] = true; // 别忘了将tmp加入迪克斯特拉的点集V'
        for (int j = 1; j <= n; j++)
            if (!isShortest[j])
                dist[j] = min(dist[j], dist[tmp] + g[tmp][j]); //更新dist的计算方法
    }
    if (dist[n] != 0x3f3f3f3f)
        return dist[n];
    else
        return -1;
}

int main()
{
    cin >> n >> m;

    memset(g, 0x3f, sizeof g);

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c); // 通过这种方法可以去掉重边
    }

    cout << dijkstra();

    return 0;
}
