#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;
void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
ListNode* insert_first(ListNode *head, int value) {
    ListNode* p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}
ListNode* insert(ListNode *head, ListNode *pre, element value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}
ListNode* delete_first(ListNode *head) {
    ListNode *removed;
    if (head == NULL) return NULL;
    removed = head;
    head = head->link;
    free(removed);
    return head;
}
ListNode* delete(ListNode *head, ListNode *pre) {
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}
ListNode* delete_odd(ListNode *head) {
    ListNode *cur = head;
    ListNode *pre = NULL;
    int count = 1;
    while (cur != NULL) {
        if (count % 2 == 1) {
            if (count == 1) {
                head = delete_first(head);
                cur = head;
            }
            else {
                head = delete(head, pre);
                cur = pre->link;
            }
        }
        else {
            pre = cur;
            cur = cur->link;
        }
        count++;
    }
    return head;
}
void print_list(ListNode *head) {
    for (ListNode *p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL \n");
}
int main() {
    ListNode *head = NULL;
    
    head = insert_first(head, 40);
    head = insert_first(head, 30);
    head = insert_first(head, 20);
    head = insert_first(head, 10);
    print_list(head);
    
    head = delete_odd(head);
    print_list(head);
}