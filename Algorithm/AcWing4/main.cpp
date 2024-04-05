// url: https://www.acwing.com/problem/content/4/
// tutorial: https://www.acwing.com/video/216/
// TC: nvs

/*
多重背包问题
*/

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int dp[N];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int v, w, s;
        cin >> v >> w >> s;
        for (int j = m; j >= 0; j--) // 前两个循环参照01背包
            for (int k = 1; k <= s && k * v <= j; k++)
            // 第一个判定条件是：物品i的数量k不应该超过给定的总数s
            // 第二个判定条件是：数量k乘以物品i的体积v不应该超过此时正在计算的背包体积j
                dp[j] = max(dp[j], dp[j - k * v] + k * w);
    }
    cout << dp[m] << endl;
    return 0;
}
