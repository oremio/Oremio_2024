// ListNode.h
#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>
#include <vector>

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x = 0, ListNode *next = nullptr) : val(x), next(next) {}

    static ListNode *CreateList(std::vector<int> in)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *temp = dummyHead;
        int i = 0, len = in.size();
        while (i < len)
        {
            ListNode *node = new ListNode(in[i++]);
            temp->next = node;
            temp = temp->next;
        }
        ListNode *ret = dummyHead->next;
        delete dummyHead;
        return ret;
    }

    static void PrintList(ListNode *in)
    {
        while (in)
        {
            std::cout << in->val << " ";
            in = in->next;
        }
        return;
    }
};

#endif // LISTNODE_H
