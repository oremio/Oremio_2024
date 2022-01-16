//url:https://leetcode-cn.com/problems/merge-k-sorted-lists/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *temp = dummyHead;
        auto cmp = [](ListNode* left, ListNode* right) { return left->val > right->val; };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> q(cmp);
        for (int i = 0; i < lists.size(); i++)
        {
            if(lists[i]) q.push(lists[i]);
        }
        while(!q.empty()){
            ListNode *node = q.top();
            q.pop();
            temp->next = node;
            temp = node;
            if(node->next) q.push(node->next);
        }
        return dummyHead->next;
    }
};

ListNode *createList(vector<int> &in)
{
    ListNode *dummyHead = new ListNode(0);
    ListNode *temp = dummyHead;
    int i = 0;
    while (i < in.size())
    {
        ListNode *node = new ListNode(in[i++]);
        temp->next = node;
        temp = temp->next;
    }
    return dummyHead->next;
}

void printList(ListNode *in)
{
    while (in)
    {
        cout << in->val << " ";
        in = in->next;
    }
    return;
}

int main()
{
    vector<int> a{1, 4, 5};
    vector<int> b{1, 3, 4};
    vector<int> c{2, 6};
    vector<ListNode *> lists{createList(a), createList(b), createList(c)};
    Solution so;
    so.mergeKLists(lists);
    return 0;
}