// url: https://www.acwing.com/problem/content/9/
// tutorial: https://www.acwing.com/video/221/

/*
分组背包问题。
与多重背包问题的区别：
多重背包问题是物品的数量有多个
分组背包问题是有多个组，每个组有多个种类的物品
分组背包问题大概没有较好的优化方法，我们选择直接暴力三重循环
*/
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int dp[N], v[N], w[N];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int s;
        cin >> s;
        for (int j = 0; j < s; j++)
            cin >> v[j] >> w[j];
        for (int j = m; j > 0; j--)
        {
            for (int k = 0; k < s; k++)
            {
                if (j >= v[k])
                    dp[j] = max(dp[j], dp[j - v[k]] + w[k]);
            }
        }
    }
    cout << dp[m] << endl;
    return 0;
}
