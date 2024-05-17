// url: https://leetcode-cn.com/problems/intersection-of-two-linked-lists/

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        // 思路：计算两条链表的长度，然后先让较长的那个链表的指针先走一段它们的差值的距离，然后再齐头并进。
    }
};
