// url: https://www.acwing.com/problem/content/2/
// tutorial: https://www.acwing.com/video/214/
// TC: nm

/*
01背包问题。递推思路：
1. 不选第 i 个物品：f[i][j] = f[i - 1][j]
2. 选第 i 个物品：f[i][j] = f[i - 1][j - v[i]] + w[i]
3. 选择上面两个结果中较大的结果

用一维数组来优化：
1. 不选第 i 个物品：f[j] = f[j] (废话！)
2. 选第 i 个物品：f[j] = 上一轮算出来的f[j - v[i]] + w[i]
3. 如何才能使用上一轮算出来的f[j - v[i]]？
    观察这个式子，我们会发现，左边是f[j]，右边是f[j - v[i]]
    也就是，左边的下标是一定大于右边的
    换言之，如果我们先算数组右边的元素，就可以使用上一轮算出来的f[j - v[i]]了
4. 选择上面两个结果中较大的结果

思考：当题目的问法是“物品的总体积不超过背包容量”而不是“物品的总体积刚好装满背包容量”时，我们选择将f[i]全部初始化为0，但是为什么？
更进一步：如果除f[0]以外，其他的f[i]我们全部初始化为负无穷，这意味着什么？
提示：负无穷 + w[i] 还是负无穷
*/
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int dp[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> v[i] >> w[i];
    }
    for (int i = 1; i <= n;i++)
        for (int j = m; j >= v[i];j--)
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
    cout << dp[m] << endl;
    return 0;
}
