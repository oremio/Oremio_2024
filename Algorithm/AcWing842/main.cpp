// url: https://www.acwing.com/problem/content/844/
// tutorial: https://www.acwing.com/video/274/
// TC

/*
回溯的过程中，一定不要忘了恢复现场！
*/

#include <iostream>

using namespace std;

const int N = 10;

int n;
int path[N];
bool used[N];

void dfs(int u)
{
    if (u == n)
    {
        for(int i = 0; i < n; i ++ ) cout << path[i] << ' ';
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i ++ )
    if (!used[i])
    {
        path[u] = i;
        used[i] = true;
        dfs(u + 1);
        // path[u] = 0;
        used[i] = false;
    }
}

int main()
{
    cin >> n;

    dfs(0);

    return 0;
}
