#include <vector>

using namespace std;

class Solution
{
private:
    int n{};
    int pre[100010]{};

public:
    int maxSubArray(vector<int> &nums)
    {
        n = nums.size();

        pre[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            pre[i] = pre[i - 1] + nums[i];
        }

        int sum = 0x80808080;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                int tmp = pre[j] - pre[i] + nums[i];
                if (tmp > sum)
                {
                    sum = tmp;
                }
            }
        }
        return sum;
    }
};
