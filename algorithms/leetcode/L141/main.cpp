// url: https://leetcode-cn.com/problems/linked-list-cycle/

#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *achilles, *tortoise;
        if (head)
            achilles = head;
        else
            return false;
        tortoise = head->next;
        while (tortoise && tortoise->next && achilles != tortoise)
        {
            tortoise = tortoise->next->next;
            achilles = achilles->next;
        }
        if (achilles == tortoise)
            return true;
        else
            return false;
    }
};
