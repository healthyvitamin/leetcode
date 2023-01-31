
/*
* 1.首先是直覺的做法 1.去數這個鏈結串列有多少節點 2.總數/2 +1 便是中間節點，那麼接下來移動head即可
*/
struct ListNode* middleNode(struct ListNode* head) {
    int index = 1;
    struct ListNode* curr = head;
    while (curr->next != NULL)
    {
        index++;
        curr = curr->next;
    }

    int middle = (index / 2) + 1;

    for (int i = 1; i < middle; i++)
    {

        head = head->next;
    }
    //  printf("%d \n", middle);
   //   printf("%d \n", head->val);



    return head;
}

/*
* 2. two pointers: slow and fast
*  有兩個指標A、B
* 讓A一次走一個，B一次走兩個
* 當B走到底(=NULL)或是在NULL的前一個時(fast->next=NULL)時，A便是題目要的中間位子
*/
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* fast = head;
    struct ListNode* slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
}
