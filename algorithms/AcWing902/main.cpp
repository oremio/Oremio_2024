// url: https://www.acwing.com/problem/content/904/
// tutorial: https://www.acwing.com/video/334/

/*
最短编辑距离（闫式DP分析法）：
集合：所有将a[1 ~ i]到b[1 ~ j]的操作方式
属性：最少的操作次数
划分集合：
1.最后一步是对a的最后一个字符进行操作
1-1.增：如果是增加最后一个字符，也就是a少了一个字符，换言之，b多了一个字符，
    那么如果没少这个字符就需要操作dp[i][j - 1]次，少了所以再加个1
1-2.删：如果是删除最后一个字符，也就是a多了一个字符，
    那么如果没多这个字符就需要操作dp[i - 1][j]次，多了所以再加个1
1-3.改：a和b的字符数量相等，但是最后一个字符不同，
    显然，dp[i][j] = dp[i - 1][j - 1] + 1
2.最后一步不是对a的最后一个字符进行操作
    显然，dp[i][j] = dp[i - 1][j - 1]
*/

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1010;

int n, m;
char a[N], b[N];
int dp[N][N];

int main()
{
    cin >> n >> a + 1 >> m >> b + 1;

    // 做dp就牢记初始化问题
    for (int i = 1; i <= n; i++)
        dp[i][0] = i;
    for (int j = 1; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            if (a[i] == b[j])
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            else
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
        }

    cout << dp[n][m] << endl;
    return 0;
}
