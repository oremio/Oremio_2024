// url: https://leetcode.cn/problems/path-sum/

#include <iostream>
#include <sstream>

using namespace std;

const int N = 1010;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 根据数组构造二叉树
TreeNode *construct_binary_tree(const string &input)
{
    TreeNode *vecTree[N];
    stringstream ss(input);
    string item;

    int idx = 1; // 树根
    while (getline(ss, item, ','))
    {
        // 去除字符串前后的空格
        item.erase(0, item.find_first_not_of(" "));
        item.erase(item.find_last_not_of(" ") + 1);

        TreeNode *node = nullptr;
        if (item != "null")
        {
            int x = stoi(item);
            node = new TreeNode(x);
        }
        vecTree[idx++] = node;
    }
    int sizeTree = idx - 1;

    for (int i = 1; i * 2 <= sizeTree; i++)
    {
        if (vecTree[i] != nullptr)
        {
            // if (i * 2 <= sizeTree)
            vecTree[i]->left = vecTree[i * 2];
            if (i * 2 + 1 <= sizeTree)
                vecTree[i]->right = vecTree[i * 2 + 1];
        }
    }
    return vecTree[1];
}

class Solution
{
public:
    int target;
    bool traversal(TreeNode *cur, int sum)
    { // todo
        if (cur->left == nullptr && cur->right == nullptr && (sum + cur->val) == target)
            return true;
        bool tmp = false;
        if (cur->left != nullptr)
            tmp = traversal(cur->left, sum + cur->val);
        if (tmp)
            return true;
        if (cur->right != nullptr)
            tmp = traversal(cur->right, sum + cur->val);
        if (tmp)
            return true;
        return false;
    }
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return false;
        target = targetSum;
        return traversal(root, 0);
    }
};

int main()
{
    Solution s;
    string input{"5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1"};
    // vector<vector<int>> output;
    // output = s.levelOrder(construct_binary_tree(input));
    // for (auto i : output)
    // {
    //     for (auto j : i)
    //         cout << j << ' ';
    //     cout << endl;
    // }
    s.hasPathSum(construct_binary_tree(input), 22);
    return 0;
}
