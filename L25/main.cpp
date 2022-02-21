//url:https://leetcode-cn.com/problems/reverse-nodes-in-k-group/

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

class Solution
{
private:
    ListNode *reverse(ListNode *a, ListNode *b)
    {
        ListNode *pre = a;
        ListNode *cur = a->next;
        while (cur != b)
        {
            ListNode *temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }

public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (head == nullptr)
            return nullptr;
        ListNode *a, *b;
        a = b = head;
        for (int i = 0; i < k; i++)
        { // base case
            if (b == nullptr)
                return head;
            b = b->next;
        }
        ListNode *newHead = reverse(a, b); // 左闭右开
        a->next = reverseKGroup(b, k);
        return newHead;
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
    ListNode *in = createList({1, 2, 3, 4, 5});
    Solution so;
    ListNode *out = so.reverseKGroup(in, 2);
    printList(out);
    return 0;
}