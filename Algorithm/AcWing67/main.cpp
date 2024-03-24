// url: https://www.acwing.com/problem/content/63/
// tutorial: https://www.acwing.com/video/191/
// TC: logn

/*
回忆一下upper_bound和lower_bound。
本题要求数字在排序数组中出现的次数，本质就是求该数字对应的序列的左端点和右端点。
左端点怎么求？本质是问，通过二分计算左端点时，nums[mid]的性质是什么？
答案是，nums[mid]如果小于k，那么它在左端点的左边，也就是应该选择右边序列继续二分，反之同理。
右端点么求？本质是问，通过二分计算右端点时，nums[mid]的性质是什么？
答案是，nums[mid]如果小于等于k，那么它在右端点的左边，也就是应该选择右边序列继续二分，反之同理。
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int getNumberOfK(vector<int> &nums, int k)
    {
        if (nums.empty())
            return 0; // 防一手空数组

        int l = 0, r = nums.size() - 1;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (nums[mid] < k)
                l = mid + 1; // mid不可能是左端点
            else
                r = mid;
        }
        if (nums[l] != k)
            return 0; // 防一手不存在的数。你可以试试去掉这行代码的测试结果

        int left = l;
        l = 0, r = nums.size() - 1;
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (nums[mid] <= k)
                l = mid; // mid可能是右端点
            else
                r = mid - 1;
        }
        int right = l;

        return right - left + 1;
    }
};

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    string input;
    getline(cin, input);
    input = input.substr(1, input.size() - 2); // 去除输入的第一行的字符串中的方括号

    // 创建字符串流，并使用逗号作为分隔符进行字符串拆分
    istringstream iss(input);
    string token;
    vector<int> nums;
    while (getline(iss, token, ','))
    {
        // 将拆分的字符串转换为整数，并存储到vector中
        nums.push_back(stoi(token));
    }

    int k;
    cin >> k;

    // test
    // for (int i = 0; i < nums.size(); i++)
    // {
    //     cout << nums[i] << ' ';
    // }

    Solution s;
    cout << s.getNumberOfK(nums, k) << endl;

    return 0;
}
