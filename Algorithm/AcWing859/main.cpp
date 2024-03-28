// url: https://www.acwing.com/problem/content/861/
// tutorial: https://www.acwing.com/problem/content/861/

/*
kruskal:
1.将所有边按权重从小到大排序
2.枚举每条边a,b，如果点a和点b现在是不连通的，将a,b这条边加入集合
如何实现这些操作？答案是并查集！
*/

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 200010;
int n, m;
int p[N];

struct edge
{
    int a, b, w;
    bool operator<(const edge &x) const
    {
        return w < x.w;
    }
} e[N];

void init()
{
    for (int i = 1; i <= n; i++)
    {
        // sizeP[i] = 1;
        p[i] = i;
    }
}

int find(int x)
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void merge(int x, int y)
{
    int px = find(x), py = find(y);
    // if (px != py)
    //     sizeP[py] += sizeP[px];
    p[px] = py; // 在同一个集合也没关系 → 为什么？
}

bool query(int x, int y)
{
    return find(x) == find(y);
}

int kruskal()
{
    // 没法写在函数里
}

int main()
{
    cin >> n >> m;
    init();

    for (int i = 1; i <= m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        e[i] = {a, b, w};
    }
    sort(e + 1, e + m + 1); // 当你从1开始计数，那么你的sort应该……

    int res = 0, cnt = 0; // 思考：为什么需要count？
    for (int i = 1; i <= m && cnt <= n - 1; i++)
    {
        if (!query(e[i].a, e[i].b))
        {
            merge(e[i].a, e[i].b);
            res += e[i].w;
            cnt++;
        }
    }
    if (cnt < n - 1)
        cout << "impossible" << endl;
    else
        cout << res << endl;
    return 0;
}
