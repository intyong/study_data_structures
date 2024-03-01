#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;
void init(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}
void dinsert(DListNode *phead, element data) {
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
    DListNode *last = phead->llink;
    newnode->data = data;
    newnode->llink = last;
    newnode->rlink = last->rlink;
    last->rlink->llink = newnode;
    last->rlink = newnode;
}
void ddelete(DListNode *head, DListNode *removed) {
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}
void print_dlist(DListNode* phead) {
    DListNode *p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        printf("<-| |%d| |-> ", p->data);
    }
    printf("\n");
}
int main() {
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));
    init(head);
    printf("추가 단계\n");
    for (int i = 0; i < 5; i++) {
        dinsert(head, i);
        print_dlist(head);
    }
    printf("삭제 단계\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        ddelete(head, head->llink);
    }
    free(head);

    return 0;
}