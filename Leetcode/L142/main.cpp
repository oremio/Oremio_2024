// url: https://leetcode-cn.com/problems/linked-list-cycle-ii/

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
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *achilles, *tortoise;
        if (head && head->next)
            achilles = head;
        else
            return NULL;
        // tortoise = head->next;
        tortoise = head; // 乌龟和阿喀琉斯出发于同一起跑线。
        while (tortoise && tortoise->next)
        {
            tortoise = tortoise->next->next;
            achilles = achilles->next;
            if (achilles == tortoise)
                break;
        }
        if (achilles == tortoise)
        {
            achilles = head;
            while (achilles != tortoise)
            {
                achilles = achilles->next;
                tortoise = tortoise->next;
            }
            return achilles;
        }
        else
            return NULL;
    }
};
