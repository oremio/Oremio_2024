/*
目录：
1.二分查找
2.虚拟头结点
3.反转链表
4.nSum
5.双指针、滑动窗口
6.二叉树遍历（递归与迭代）
7.二叉搜索树
8.回溯算法
9.BFS，拓扑排序
10.动态规划
11.数学
12.常用排序算法（见Sort）
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*1.二分查找（左闭右开）
①算middle
②比较
*/
int binarySearch(vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size(); // 右开
    while (left < right)
    {
        int middle = left + ((right - left) >> 1);
        if (nums[middle] > target)
            right = middle;
        else if (nums[middle] < target)
            left = middle + 1;
        else
            return middle;
    }
    return -1;
}

// 左闭右闭
int binarySearch(vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1; // 右闭
    while (left <= right)
    {
        int middle = left + ((right - left) >> 1);
        if (nums[middle] > target)
            right = middle - 1;
        else if (nums[middle] < target)
            left = middle + 1;
        else
            return middle;
    }
    return -1;
}

// 寻找左侧边界（左闭右闭）
int leftBound(vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1; // 右闭
    while (left <= right)
    {
        int middle = left + ((right - left) >> 1);
        if (nums[middle] > target)
            right = middle - 1;
        else if (nums[middle] < target)
            left = middle + 1;
        else
            right = middle - 1; // 别返回，锁定左侧边界
    }
    // 最后要检查 left 越界的情况
    if (left >= nums.size() || nums[left] != target) // 边界处理放在左边
        return -1;
    return left;
}

// 寻找右侧边界（左闭右闭）
int rightBound(vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1; // 右闭
    while (left <= right)
    {
        int middle = left + ((right - left) >> 1);
        if (nums[middle] > target)
            right = middle - 1;
        else if (nums[middle] < target)
            left = middle + 1;
        else
            left = middle + 1; // 别返回，锁定右侧边界
    }
    // 最后要检查 right 越界的情况
    if (right < 0 || nums[right] != target) // 边界处理放在左边
        return -1;
    return right;
}

/*
2.虚拟头结点：利用虚拟头结点移除链表某元素，从而可以不单独处理头结点
*/
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *removeElements(ListNode *head, int val)
{
    ListNode *dummyHead = new ListNode(0);
    dummyHead->next = head;
    ListNode *p = dummyHead;
    while (p->next != nullptr)
    {
        if (p->next->val == val)
        {
            ListNode *temp = p->next;
            p->next = p->next->next;
            delete temp;
        }
        else
            p = p->next;
    }
    head = dummyHead->next;
    delete dummyHead;
    return head;
}

/*3.反转链表
①双指针
②将每个next反转，例如，1->2变成1<-2，其他都不变
*/
ListNode *reverseList(ListNode *head)
{
    ListNode *pre = nullptr, *cur = head;
    while (cur)
    {
        ListNode *tmp = cur->next; // 保存后继
        cur->next = pre; // 关键的反转
        pre = cur; // 当前结点成为前驱
        cur = tmp; // 原后继结点成为当前结点，如果原后继结点为null则退出循环
    }
    return pre;
}

/*
4.nSum
left, right
i, left, right
i, j, left, right
...
*/
// 例题：fourSum
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        // 去重
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (j > i + 1 && nums[j] == nums[j - 1])
                continue;
            int left = j + 1;
            int right = nums.size() - 1;
            while (right > left)
            {
                if (nums[i] + nums[j] + nums[left] + nums[right] > target)
                    right--;
                else if (nums[i] + nums[j] + nums[left] + nums[right] < target)
                    left++;
                else
                {
                    result.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                    // 去重逻辑放在这里
                    while (right > left && nums[right] == nums[right - 1])
                        right--;
                    while (right > left && nums[left] == nums[left + 1])
                        left++;
                    // 至少缩一次
                    right--;
                    left++;
                }
            }
        }
    }
    return result;
}

// 5.滑动窗口框架
/*
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

            // debug 输出的位置
            printf("window: [%d, %d)\n", left, right);

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
*/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// 6.二叉树遍历（递归与迭代）
/*
关于递归：
每次写递归，都按照这三要素来写框架：
    1.确定递归函数的参数和返回值：确定哪些参数是递归的过程中需要处理的，那么就在递归函数里加上这个参数，
        并且还要明确每次递归的返回值是什么进而确定递归函数的返回类型。
    2.确定终止条件：写完了递归算法, 运行的时候，经常会遇到栈溢出的错误，
        就是没写终止条件或者终止条件写的不对，操作系统也是用一个栈的结构来保存每一层递归的信息，
        如果递归没有终止，操作系统的内存栈必然就会溢出。
    3.确定单层递归的逻辑：确定每一层递归需要处理的信息。在这里也就会重复调用自己来实现递归的过程。
递归的思路则是：
    1.明确traversal()的功能
    2.寻找递推公式
    3.将递推公式转换为代码
    4.分析时间复杂度（和空间复杂度），判断这个问题是否适合递归
*/
/*
迭代：
前序：中右左入栈
中序：先找到最左，再中右
后序：中左右入栈（和前序完全一致），再反转
层序：队列
*/
vector<int> preorderTraversal(TreeNode *root)
{
    stack<TreeNode *> st;
    vector<int> res;
    if (root == nullptr)
        return res;
    st.push(root);
    while (!st.empty())
    {
        TreeNode *cur = st.top(); // 中
        st.pop();
        res.push_back(cur->val);
        if (cur->right)
            st.push(cur->right); // 右
        if (cur->left)
            st.push(cur->left); // 左
    }
    return res;
}

vector<int> inorderTraversal(TreeNode *root)
{
    stack<TreeNode *> st;
    vector<int> res;
    if (root == nullptr)
        return res;

    TreeNode *cur = root;
    while (cur != nullptr || !st.empty())
    { // 中序需要增加一个cur != nullptr
        if (cur != nullptr)
        {
            st.push(cur);
            cur = cur->left; // 左
        }
        else
        {
            cur = st.top(); // 中
            st.pop();
            res.push_back(cur->val);
            cur = cur->right; // 右，无需判断是否为空
        }
    }
    return res;
}

vector<vector<int>> levelOrder(TreeNode *root)
{
    queue<TreeNode *> que;
    if (root != nullptr)
        que.push(root);
    vector<vector<int>> result;
    while (!que.empty())
    {
        int size = que.size();
        vector<int> vec;
        for (int i = 0; i < size; i++)
        {
            TreeNode *node = que.front();
            que.pop();
            vec.push_back(node->val);
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        result.push_back(vec);
    }
    return result;
}

// 测试方法：层序创建二叉树
TreeNode *createLevelTree(vector<int> &s)
{
    int p = 0;
    TreeNode *root = NULL;

    TreeNode *t, *i, *j;
    queue<TreeNode *> qTree; // 定义一个队列，存储节点

    while (true)
    {
        if (p == s.size())
            break;
        if (p == 0) // 当头结点未创建
        {
            t = new TreeNode(s[p]);
            qTree.push(t); // 头结点进队
            root = t;
            p++;
        }
        else
        {
            t = qTree.front(); // 该节点出队
            if (p == s.size())
                break;      // 树的构建完毕
            if (s[p] == -1) // 不存在左节点
            {
                t->left = NULL;
                p++;
            }
            else // 存在左节点
            {
                i = new TreeNode(s[p]);
                t->left = i; // 左节点进队
                qTree.push(i);
                p++;
            }

            if (p == s.size())
                break;
            if (s[p] == -1) // 不存在右节点
            {
                t->right = NULL;
                p++;
            }
            else // 存在右节点
            {
                j = new TreeNode(s[p]);
                t->right = j;
                qTree.push(j);
                p++;
            }

            qTree.pop(); // 节点左右节点已创建，该节点出队
        }
    }

    return root;
}

// 例题：判断平衡二叉树
class BalancedTree
{
public:
    // 返回以该节点为根节点的二叉树的高度，如果不是二叉搜索树了则返回-1
    int getDepth(TreeNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        int leftDepth = getDepth(node->left);
        if (leftDepth == -1)
            return -1; // 说明左子树已经不是二叉平衡树
        int rightDepth = getDepth(node->right);
        if (rightDepth == -1)
            return -1; // 说明右子树已经不是二叉平衡树
        return abs(leftDepth - rightDepth) > 1 ? -1 : 1 + max(leftDepth, rightDepth);
    }
    bool isBalanced(TreeNode *root)
    {
        return getDepth(root) == -1 ? false : true;
    }
};

/*
7.二叉搜索树
关键：一切二叉搜索树都可以通过中序遍历变成一个有序数组。
*/
// 例题：删除二叉搜索树中的节点
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == nullptr)
        return root; // 第一种情况：没找到删除的节点，遍历到空节点直接返回了
    if (root->val == key)
    {
        // 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
        // 第三种情况：其左孩子为空，右孩子不为空，删除节点，右孩子补位 ，返回右孩子为根节点
        if (root->left == nullptr)
            return root->right;
        // 第四种情况：其右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
        else if (root->right == nullptr)
            return root->left;
        // 第五种情况：左右孩子节点都不为空，则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
        // 并返回删除节点右孩子为新的根节点。
        else
        {
            TreeNode *cur = root->right; // 找右子树最左面的节点
            while (cur->left != nullptr)
            {
                cur = cur->left;
            }
            cur->left = root->left; // 把要删除的节点（root）左子树放在cur的左孩子的位置
            TreeNode *tmp = root;   // 把root节点保存一下，下面来删除
            root = root->right;     // 返回旧root的右孩子作为新root
            delete tmp;             // 释放节点内存（这里不写也可以，但C++最好手动释放一下吧）
            return root;
        }
    }
    if (root->val > key)
        root->left = deleteNode(root->left, key);
    if (root->val < key)
        root->right = deleteNode(root->right, key);
    return root;
}

/*
8.回溯算法（DFS）
void backtracking(参数){
    if(终止条件){
        存放结果;
        return;
    }
    for(选择: 本层集合中元素){
        处理节点;
        backtracking(路径，选择列表);
        回溯，撤销处理结果;
    }
}
回溯算法常见题型：
    1.组合问题：N个数里面按一定规则找出k个数的集合
    2.切割问题：一个字符串按一定规则有几种切割方式
    3.子集问题：一个N个数的集合里有多少符合条件的子集
    4.排列问题：N个数按一定规则全排列，有几种排列方式
    5.棋盘问题：N皇后，解数独等等
*/

// 例题：组合问题
class Combinations
{
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startIndex)
    {
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++)
        {                      // 优化的地方
            path.push_back(i); // 处理节点
            backtracking(n, k, i + 1);
            path.pop_back(); // 回溯，撤销处理的节点
        }
    }

public:
    vector<vector<int>> combine(int n, int k)
    {
        backtracking(n, k, 1);
        return result;
    }
};

// 例题：切割问题（分割回文子串）
class Partition
{
private:
    vector<vector<string>> result;
    vector<string> path;
    bool isPalindrome(const string &s, int start, int end)
    {
        for (int i = start, j = end; i < j; i++, j--)
        {
            if (s[i] != s[j])
            {
                return false;
            }
        }
        return true;
    }
    void backtracking(const string &s, int startIndex)
    {
        if (startIndex >= s.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++)
        {
            if (isPalindrome(s, startIndex, i))
            {
                // 获取[startIndex,i]在s中的子串
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
            }
            else
            { // 不是回文，跳过
                continue;
            }
            backtracking(s, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s)
    {
        result.clear();
        path.clear();
        backtracking(s, 0);
        return result;
    }
};

// 例题：子集问题
class Subsets
{
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int> &nums, int startIndex)
    {
        result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己
        if (startIndex >= nums.size())
        { // 终止条件可以不加
            return;
        }
        for (int i = startIndex; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};

// 例题：排列问题
class Permutations
{
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int> &nums, vector<bool> &used)
    {
        // 此时说明找到了一组
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i] == true)
                continue; // path里已经收录的元素，直接跳过
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};

/*
9.BFS，拓扑排序
BFS：类层序遍历，可以使用队列
拓扑排序：根据入度进行判断
*/
// 例题：课程表
vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<vector<int>> graph(numCourses, vector<int>());
    vector<int> indegree(numCourses, 0), res;
    for (auto i : prerequisites)
    {
        graph[i[1]].push_back(i[0]);
        ++indegree[i[0]]; // 入度+1
    }
    queue<int> q;
    for (int i = 0; i < indegree.size(); i++)
    {
        if (!indegree[i])
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        res.push_back(u);
        q.pop();
        for (auto v : graph[u])
        {
            --indegree[v];
            if (!indegree[v])
                q.push(v);
        }
    }
    // 检测有无因为循环导致有节点仍存在入度，比如[[1,0],[0,1]]就永远无法加入队列
    for (int i = 0; i < indegree.size(); i++)
    {
        if (indegree[i])
            return vector<int>();
    }
    return res;
}

/*
10.动态规划
    1.确定dp数组以及下标的含义
    2.确定递推公式
    3.dp数组如何初始化
    4.确定遍历顺序
    5.自己举例推到一个dp，推清楚再开始写代码
常见题型：
    1.01背包、完全背包
    2.股票问题
    3.打家劫舍问题
    4.子序列问题
*/

// 例题：01背包
int zeroOnePack()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    // init
    vector<int> dp(bagWeight + 1, 0);
    for (int i = 0; i < weight.size(); i++)
    {
        for (int j = bagWeight; i >= weight[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

// 例题：完全背包
int completePack()
{
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    // init
    vector<int> dp(bagWeight + 1, 0);
    for (int i = 0; i < weight.size(); i++)
    { // 遍历物品
        for (int j = weight[i]; j <= bagWeight; j++)
        { // 遍历背包容量，这里和上面的01不同
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

// 多重背包：01背包的进阶版，把有多个数量的同一种物品拆开

// 股票问题：
int bestTimeToBuyAndSellStockIII(vector<int> &prices)
{
    if (prices.size() == 0)
        return 0;
    // 1.无操作；买一；卖一；买二；卖二
    vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
    // 3.初始化：
    dp[0][1] = -prices[0];
    dp[0][3] = -prices[0];
    // 2 & 4：
    for (int i = 1; i < prices.size(); i++)
    {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
        dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
        dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
    }
    return dp[prices.size() - 1][4];
}

// 打家劫舍问题：
int rob(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    if (nums.size() == 1)
        return nums[0];
    // 1.dp[i]：考虑下标i（包括i）以内的房屋，最多可以偷窃的金额为dp[i]。
    // 2.dp[i] = max(dp[i - 2] + nums[i], dp[i - 1])
    vector<int> dp(nums.size());
    // 3.初始化
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    // 4.
    for (int i = 2; i < nums.size(); i++)
    {
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
    }
    return dp[nums.size() - 1];
}

// 编辑距离：
int minDistance(string word1, string word2)
{
    // 1.dp[i][j] 表示以下标i - 1为结尾的字符串word1，和以下标j - 1为结尾的字符串word2，最近编辑距离为dp[i][j]。
    /*
    2.
    if (word1[i - 1] == word2[j - 1])
        不操作
    if (word1[i - 1] != word2[j - 1])
        增
        删
        换
    */
    vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
    // 3.初始化
    for (int i = 0; i <= word1.size(); i++)
        dp[i][0] = i;
    for (int j = 0; j <= word2.size(); j++)
        dp[0][j] = j;
    // 4.
    for (int i = 1; i <= word1.size(); i++)
    {
        for (int j = 1; j <= word2.size(); j++)
        {
            if (word1[i - 1] == word2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
            }
        }
    }
    return dp[word1.size()][word2.size()];
}

/*
11.数学
12.常用排序算法（见Sort-SortTheory）
*/

int main()
{
}
