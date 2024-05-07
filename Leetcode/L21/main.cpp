// url: https://leetcode-cn.com/problems/merge-two-sorted-lists/

#include "../ListNode.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *temp = dummyHead;
        while (list1 && list2)
        {
            if (list1->val <= list2->val)
            {
                temp->next = list1;
                list1 = list1->next;
            }
            else
            {
                temp->next = list2;
                list2 = list2->next;
            }
            temp = temp->next;
        }
        if (list1)
            temp->next = list1;
        else
            temp->next = list2;
        return dummyHead->next;
    }
};

int main()
{
    vector<int> a{1, 2, 4};
    ListNode *aHead = ListNode::CreateList(a);
    vector<int> b{1, 3, 4};
    ListNode *bHead = ListNode::CreateList(b);
    Solution so;
    ListNode *rHead = so.mergeTwoLists(aHead, bHead);
    ListNode::PrintList(rHead);
    return 0;
}
