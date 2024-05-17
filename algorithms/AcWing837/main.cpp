// url: https://www.acwing.com/problem/content/839/
// tutorial: https://www.acwing.com/video/262/
// TC: 近乎1

/*
并查集：
基本原理：
1.每个集合用一棵树来表示，树根的编号就是整个集合的编号。
2.每个结点存储它的父节点，p[x]表示x的父节点（树根除外）
问题1：如何判断树根：if(p[x] == x)
问题2：如何求x的集合编号：while(p[x] != x) x = p[x]
问题3：如何合并两个集合：p[x]是x的集合编号，p[y]是y的集合编号，令p[x] = y
优化1：路径压缩：p[x] = find(p[x]);
优化2：按秩合并
*/

#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int p[N], sizeP[N];

void init()
{
    for (int i = 1; i <= n; i++)
    {
        sizeP[i] = 1;
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
    if (px != py)
        sizeP[py] += sizeP[px];
    p[px] = py; // 在同一个集合也没关系 → 为什么？
}

bool query(int x, int y)
{
    return find(x) == find(y);
}

int main()
{
    cin >> n >> m;

    init();

    while (m--)
    {
        string op;
        cin >> op;
        if (op == "C")
        {
            int x, y;
            cin >> x >> y;
            merge(x, y);
        }
        else if (op == "Q1")
        {
            int x, y;
            cin >> x >> y;
            if (query(x, y))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        else
        {
            int a;
            cin >> a;
            cout << sizeP[find(a)] << endl;
        }
    }
    return 0;
}
