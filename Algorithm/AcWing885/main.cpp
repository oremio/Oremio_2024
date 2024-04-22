// url: https://www.acwing.com/problem/content/887/
// tutorial: https://www.acwing.com/video/306/

/*
求组合数 I
回忆一下高中的排列组合知识：
C(a, b) = C(a - 1, b - 1) + C(a - 1, b)
a个物品里取b个，可以划分为两个集合，一个是一定取某个物品X，另一个是一定不取物品X
*/

#include <iostream>

using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;

int com[N][N];

void init()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (!j)
                com[i][0] = 1; // 初始化
            else
                com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % mod; // 右边的值要么我们算过，要么不合法（那就是0）
}

int main()
{
    int n;
    cin >> n;

    init();

    while (n--)
    {
        int x, y;
        cin >> x >> y;
        cout << com[x][y] << endl;
    }
    return 0;
}
