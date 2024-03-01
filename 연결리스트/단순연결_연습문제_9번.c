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
void print_list(ListNode *head) {
    for (ListNode *p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL \n");
}
int main() {
    ListNode *head = NULL;
    ListNode *t = NULL;
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int temp = 0;
        scanf("%d", &temp);
        if (i == 0) {
            head = insert_first(head, temp);
            t = head;
        }
        else {
            insert(head, t, temp);
            t = t->link;
        }
    }
    print_list(head);
}