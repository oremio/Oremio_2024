// url: https://leetcode.cn/problems/add-two-numbers

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int val=0, ListNode next=null) {
 *         this.val = val;
 *         this.next = next;
 *     }
 * }
 */
public class Solution {
    public ListNode AddTwoNumbers(ListNode l1, ListNode l2) {
        int singleDigit;
        int tenDigit = 0;
        ListNode dummyHead = new ListNode(-1), node = dummyHead;
        while( l1 != null || l2 != null || tenDigit != 0){
            // 构造新节点的条件：两数有节点不为空，或者有进位
            int sum = tenDigit;
            if(l1 != null){
                sum += l1.val;
                l1 = l1.next;
            }
            if(l2 != null){
                sum += l2.val;
                l2 = l2.next;
            }
            singleDigit = sum % 10;
            tenDigit = sum / 10;

            ListNode newNode = new ListNode( singleDigit );
            node.next = newNode;
            node = newNode;
        }
        return dummyHead.next;
    }
}
