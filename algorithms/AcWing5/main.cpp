// url: https://www.acwing.com/problem/content/5/
// tutorial: https://www.acwing.com/video/217/

/*
依旧是多重背包问题，但这次，
我们可以使用一个类似于二进制的拆分方法，
将同种类的物品也拆成多种，
例如，如果一个物品的数量是10，可以拆成
1 + 2 + 4 + 3，
也就是数量上限分别是1、2、4、3的四种物品
如何用代码表示出它们是四种物品呢？
答案是
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 2010;

struct Good
{
    int v, w;
};

int n, m;
int dp[N];

int main()
{
    cin >> n >> m;

    vector<Good> goods;

    for (int i = 0; i < n; i++)
    {
        int v, w, s;
        cin >> v >> w >> s;
        for (int k = 1; k <= s; k *= 2)
        {
            goods.push_back({k * v, k * w});
            s -= k;
        }
        if (s > 0)
            goods.push_back({s * v, s * w});
    }

    for (auto i : goods)
        for (int j = m; j >= i.v; j--)
            dp[j] = max(dp[j], dp[j - i.v] + i.w);

    cout << dp[m] << endl;
    return 0;
}
