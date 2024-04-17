// url: https://www.acwing.com/problem/content/898/
// tutorial: https://www.acwing.com/video/328/

/*
在AcWing895.最长上升子序列的基础上，
我们维护一个严格单调递增的数组dp。
这个数组是什么呢？它的下标是序列长度，
存储的值是所有 长度等于这个下标的子序列 中，最后一个数的最小值（思考：为什么是最小值？）
通过反证法，我们可以证明这个数组是严格单调递增的。（试想，如果dp[i + 1]等于甚至小于dp[i]，
那么我们一定可以找到一个dp[i]比当前的dp[i]还要小）

二分的检查属性：小于num[i]（也就是我们当前检查的数）的dp[i]
二分的目标：最大的小于num[i]的dp[i]（是不是想到某个库函数了？）

几个注意点：
0.dp数组一定是严格单调递增的
1.需要一个哨兵，也就是dp[0] = -2e9;（题目的数据范围是-1e9到1e9）
2.使用lower_bound来实现二分时，注意前闭后开
3.注意指针相减得到的数的类型是long long（毕竟你用的是64位的电脑）
*/

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

const int N = 100010;

int n;
int dp[N], num[N];

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> num[i];
    int len = 0;
    dp[0] = -2e9;

    for (int i = 0; i < n; i++)
    {
        /*
        int l = 0, r = len;
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (dp[mid] < num[i]) // 小于num[i]（也就是我们当前检查的数）的dp[i]，但不知道是不是最大的，所以选右区间
                l = mid;
            else
                r = mid - 1;
        }
        */
        auto l = dp, r = dp + len + 1;        // 前闭后开，和我们自己写的二分不一样
        auto res = lower_bound(l, r, num[i]); // 返回大于等于num[i]的dp
        res--;                                // 最大的小于num[i]的dp

        auto idx = static_cast<int>(res - l);
        len = max(len, idx + 1);
        dp[idx + 1] = num[i];
    }
    cout << len << endl;
    return 0;
}
