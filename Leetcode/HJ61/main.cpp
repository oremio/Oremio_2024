// url: https://www.nowcoder.com/practice/bfd8234bb5e84be0b493656e390bdebf

#include <iostream>
using namespace std;

const int N = 11;
int dp[N][N]; // 将i个苹果放到j个盘子里的分法


int main() {
    int m, n;
    cin >> m >> n;

    for(int j = 1; j <= n; j++) dp[0][j] = 1;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (i < j) dp[i][j] = dp[i][i];
            else {
                /*
                划分集合的方法：是否用完盘子
                用完 == 每个盘子至少一个苹果
                不用完 == 少一个盘子也没问题
                */
                dp[i][j] = dp[i - j][j] + dp[i][j - 1];
            }
        }
    cout << dp[m][n] << endl;
    return 0;
}
