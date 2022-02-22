//url:https://leetcode-cn.com/problems/palindrome-linked-list/
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
    ListNode *left;
    bool traverse(ListNode* right){
        if(right == nullptr)
            return true;
        bool res = traverse(right->next);
        res = res && (right->val == left->val);
        left = left->next;
        return res;
    }
public:
    bool isPalindrome(ListNode *head)
    {
        // 把原始链表反转存入一条新的链表，然后比较这两条链表是否相同。
        // 将上面的思路更进一步：我们可以直接后序遍历来获得右边节点的值
        left = head;
        return traverse(head);
    }
};

int main(){
    return 0;
}