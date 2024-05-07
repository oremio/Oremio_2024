// url: https://leetcode.cn/problems/sum-of-left-leaves/

#include "../TreeNode.h"
#include <iostream>
#include <sstream>

using namespace std;

class Solution
{
public:
    int traversal(TreeNode *tmp)
    {
        if (tmp == nullptr)
            return 0;
        if (tmp->left == nullptr && tmp->right == nullptr)
            return 0;

        int l = traversal(tmp->left);
        if (tmp->left && !tmp->left->left && !tmp->left->right)
            l = tmp->left->val;
        int r = traversal(tmp->right);
        return l + r;
    }
    int sumOfLeftLeaves(TreeNode *root)
    {
        return traversal(root);
    }
};

int main()
{
    string s{"3,9,20,null,null,15,7"};
    TreeNode *root = TreeNode::construct_binary_tree(s);
    Solution so;
    cout << so.sumOfLeftLeaves(root);
    return 0;
}
