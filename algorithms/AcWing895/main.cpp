// url: https://www.acwing.com/problem/content/897/
// tutorial: https://www.acwing.com/video/327/

/*
状态表示dp[i]：
闫式dp法——集合：所有以第i个数结尾的上升子序列
dp[i]呢：这个集合里数量最大的子序列，要的就是这个数量
状态转移方程：
我们这个集合可以根据子序列的上一个数来划分，
上一个数可能是a[0], a[1], ..., a[i - 1]
因此，状态转移方程为：
f[i] = max(f[j] + 1), j = 0, 1, 2, ..., i - 1
*/

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1010;

int n;
int a[N], dp[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1);
    }

    int res = 0;
    for (int i = 0; i < n; i++)
        res = max(res, dp[i]);
    cout << res << endl;
    return 0;
}
