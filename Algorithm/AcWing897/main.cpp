// url: https://www.acwing.com/problem/content/899/
// tutorial: https://www.acwing.com/video/946/

/*
状态表示：
闫式dp中，先分析集合：序列A[1 ~ i]和B[1 ~ j]的公共子序列的集合
因此，dp[i][j]：这个集合里的公共子序列的最大长度

状态方程：
集合该如何划分？答案是，根据我们的公共子序列中的a[i]和b[j]的有无
那么只有四种划分法：00（均无）、01、10、11（均有）
如果是00，那么dp[i][j] = dp[i - 1][j - 1]
如果是01，那么dp[i][j] = dp[i - 1][j]（注意，这个值其实已经包含了00的情况）
如果是10，那么dp[i][j] = dp[i][j - 1]
如果是11，那么dp[i][j] = dp[i - 1][j - 1] + 1，但需注意，11的话要先判定a[i] == b[j]
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int dp[N][N];
char a[N], b[N];

int main()
{
    cin >> n >> m >> a + 1 >> b + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++){
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if(a[i] == b[j])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
        }
    cout << dp[n][m] << endl;
    return 0;
}
