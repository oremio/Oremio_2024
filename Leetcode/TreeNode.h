// TreeNode.h
#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <sstream>

class TreeNode
{
public:
    int val;
    TreeNode *left, *right;

    TreeNode(int x = 0, TreeNode *left = nullptr, TreeNode *right = nullptr)
        : val(x), left(left), right(right) {}

    static TreeNode *ConstructBinaryTree(const std::string &input)
    {
        TreeNode *vecTree[1010];
        std::stringstream ss(input);
        std::string item;

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
};

#endif // TREENODE_H
