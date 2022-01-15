#include <vector>
#include <iostream>

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
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *temp = dummyHead;
        while(list1 && list2){
            if (list1->val <= list2->val){
                temp->next = list1;
                list1 = list1->next;
            }
            else{
                temp->next = list2;
                list2 = list2->next;
            }
            temp = temp->next;
        }
        if(list1)
            temp->next = list1;
        else
            temp->next = list2;
        return dummyHead->next;
    }
};

ListNode* createList(vector<int> in){
    ListNode* dummyHead = new ListNode(0);
    ListNode* temp = dummyHead;
    int i = 0;
    while(i < in.size()){
        ListNode* node = new ListNode(in[i++]);
        temp->next = node;
        temp = temp->next;
    }
    return dummyHead->next;
}

void printList(ListNode* in){
    while(in){
        cout << in->val << " ";
        in = in->next;
    }
    return;
}

int main(){
    vector<int> a{1,2,4};
    ListNode* aHead = createList(a);
    vector<int> b{1,3,4};
    ListNode* bHead = createList(b);
    Solution so;
    ListNode* rHead = so.mergeTwoLists(aHead, bHead);
    printList(rHead);
    return 0;
}