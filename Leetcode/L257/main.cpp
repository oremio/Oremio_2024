// url: https://leetcode.cn/problems/binary-tree-paths/

#include <iostream>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

using namespace std;

class Solution {
private:
    vector<string> res;

public:
    void traversal(TreeNode* tmp, string& s) {
        if (tmp == nullptr) return;

        int len = s.length();  // 记录当前字符串长度，用于恢复
        if (!s.empty()) s += "->";
        s += to_string(tmp->val);

        if (tmp->left == nullptr && tmp->right == nullptr) {
            res.push_back(s);  // 如果是叶节点，加入结果中
        } else {
            traversal(tmp->left, s);
            traversal(tmp->right, s);
        }

        s.erase(len);  // 撤销对字符串的修改
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        string s;
        traversal(root, s);
        return res;
    }
};
