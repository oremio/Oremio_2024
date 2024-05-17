/*
题目：必须拿起的最小连续卡牌数
给你一个整数数组cards，其中cards[i]表示第i张卡牌的值。如果两张卡牌的值相同，则认为这一对卡牌匹配。
返回你必须拿起的最小连续卡牌数，以使在拿起的卡牌中有一对匹配的卡牌。如果无法得到一对匹配的卡牌，返回-1。

示例 1：
输入：cards = [3,4,2,3,4,7]
输出：4
解释：拿起卡牌[3,4,2,3]将会包含一对值为3的匹配卡牌。注意，拿起[4,2,3,4]也是最优方案。

示例 2：
输入：cards = [1,0,5,3]
输出：-1
解释：无法找出含一对匹配卡牌的一组连续卡牌。
*/
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    ifstream file("input.txt");
    if (file.is_open())
        cin.rdbuf(file.rdbuf());

    int tmp;
    int res = 0x3f3f3f3f;

    vector<int> input;
    map<int, int> m;

    while (cin >> tmp)
        input.push_back(tmp);
    int len = input.size();

    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            if (j - i + 1 > res)
                break;
            for (int k = i; k <= j; k++)
            {
                m[input[k]]++;
            }
            for (auto item : m)
            {
                if (item.second > 1 && j - i + 1 < res)
                {
                    res = j - i + 1;
                    break;
                }
            }
            m.clear();
        }
    }
    cout << (res == 0x3f3f3f3f ? -1 : res) << endl;
    return 0;
}
