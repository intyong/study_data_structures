/* ⭐️ 원형 연결리스트는 head가 마지막 노드를 가리키고, 
   마지막 노드는 맨 앞의 노드와 연결되어 있음 ⭐️ */
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;
ListNode* insert_first(ListNode* head, element data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    if (head == NULL) {
        head = node;
        node->link = head;
    }
    else {
        node->link = head->link;
        head->link = node;
    }
    return head;
}
ListNode* insert_last(ListNode* head, element data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    if (head == NULL) {
        head = node;
        node->link = head;
    }
    else {
        node->link = head->link;
        head->link = node;
        head = node;
    }
    return head;
}
int get_length(ListNode *head) {
    int result = 0;
    if (head == NULL) return result;
    else {
        ListNode *p;
        p = head -> link;
        for (; p != head; p = p->link) result++;
        if (p == head) result++;    
    }
    return result;
}
void print_list(ListNode *head) {
    if (head == NULL) return;
    ListNode *p;
    p = head->link;
    do {
        printf("%d->", p->data);
        p = p->link;
    } while (p != head);
    printf("%d->", p->data);
}
int main() {
    ListNode *head = NULL;
    head = insert_last(head, 20);
    head = insert_last(head, 30);
    head = insert_last(head, 40);
    head = insert_first(head, 10);
    print_list(head);

    return 0;
}