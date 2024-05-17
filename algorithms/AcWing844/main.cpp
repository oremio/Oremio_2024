// url: https://www.acwing.com/problem/content/846/
// tutorial: https://www.acwing.com/video/276/

/*
走迷宫，BFS
大致思路：
1.往queue里插个初始坐标
2.while queue非空
2-1.把队头拿出来
2-2.拓展队列（具体到本题：判断上下左右能否进队列）
*/

#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

const int N = 110;
int n, m;
int g[N][N]; // graph
int d[N][N]; // distance
queue<pair<int, int>> q;

int bfs()
{
    memset(d, -1, sizeof d); // 初始化距离

    q.push({0, 0}); // 手动往队列插入第一个序偶
    d[0][0] = 0;

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    while (!q.empty())
    {
        auto tmp = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = tmp.first + dx[i], y = tmp.second + dy[i];
            if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1)
            {
                d[x][y] = d[tmp.first][tmp.second] + 1;
                q.push({x, y});
            }
        }
    }
    return d[n - 1][m - 1];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> g[i][j];
    cout << bfs() << endl;
    return 0;
}
