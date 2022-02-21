//url:https://leetcode-cn.com/problems/reverse-linked-list/submissions/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
            return head; //最末端的结点将传给last
        }
        ListNode* last = reverseList(head->next); //递归入口
        head->next->next = head;
        head->next = nullptr;
        return last;
    }
};