/*
给你两个整数 left 和 right ，表示区间 [left, right] ，
返回此区间内所有数字 按位与 的结果（包含 left 、right 端点）。

示例 1：

输入：left = 5, right = 7
输出：4
示例 2：

输入：left = 9, right = 10
输出：8
示例 3：

输入：left = 1, right = 2147483647
输出：0


提示：

0 <= left <= right <= 231 - 1
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        // 待补充
    }
};
*/
#include <iostream>

using namespace std;

class Solution
{
public:
    // unsigned int rangeBitwiseAnd(unsigned int left, unsigned int right) {
    //     auto res = left;
    //     for (auto i = left; i <= right; i++) {
    //         res = res & i;
    //     }
    //     return res;
    // }
    int rangeBitwiseAnd(int left, int right)
    {
        int shift = 0, res = left;
        while (left < right)
        {
            left >>= 1;
            right >>= 1;
            ++shift;
        }
        return res & (0xffff << shift);
    }
};

int main()
{
    Solution so;
    unsigned int left, right;
    cin >> left >> right;
    // 0 <= left <= right <= 231 - 1
    cout << so.rangeBitwiseAnd(left, right) << endl;
    return 0;
}
