// url: https://leetcode.cn/problems/combination-sum-iii

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    int _k, _n, target;
    vector<int> tmp;
    vector<vector<int>> res;

public:
    void traversal(int idx, int cnt, int state)
    {
        if (cnt + _n - idx + 1 < _k)
            return;
        if (cnt == _k)
        {
            int sum = 0;
            for (int i = 1; i <= _n; i++) // 用n代替9，起到剪枝效果
                if (state >> i & 1)
                {
                    sum += i;
                    tmp.push_back(i);
                }
            if (sum == target)
                res.push_back(tmp);
            tmp.clear();
            return;
        }

        traversal(idx + 1, cnt + 1, state | (1 << idx)); // 选
        traversal(idx + 1, cnt, state);                  // 不选
    }
    vector<vector<int>> combinationSum3(int k, int n)
    {
        _k = k;
        _n = n > 9 ? 9 : n;
        target = n;
        traversal(1, 0, 0);
        return res;
    }
};

int main()
{
    Solution so;
    vector<vector<int>> res{so.combinationSum3(9, 45)};
    for (auto i : res)
    {
        for (auto j : i)
            cout << j << ' ';
        cout << endl;
    }
    return 0;
}
