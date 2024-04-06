// url: https://leetcode-cn.com/problems/reverse-linked-list-ii/comments/

#include <iostream>
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

/*
- 定位到要反转部分的头节点 2，head = 2；前驱结点 1，pre = 1；
- 当前节点的下一个节点3调整为前驱节点的下一个节点 1->3->2->4->5,
- 当前结点仍为2， 前驱结点依然是1，重复上一步操作
- 1->4->3->2->5.
*/
class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        ListNode *dummyhead = new ListNode(-1);
        dummyhead->next = head;
        ListNode *pre = nullptr, *cur = dummyhead;
        int i = 0;
        while (cur != nullptr && i < left)
        {
            pre = cur;
            cur = cur->next;
            i++;
        }
        while (cur != nullptr && cur->next != nullptr && i < right)
        {
            ListNode *tmp = pre->next;
            pre->next = cur->next;
            cur->next = cur->next->next;
            pre->next->next = tmp;
            i++;
        }
        return dummyhead->next;
    }
};

ListNode *createList(vector<int> in)
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
    Solution so;
    ListNode *head = createList({1, 2, 3, 4, 5});
    ListNode *change = so.reverseBetween(head, 2, 4);
    printList(change);
    return 0;
}
