#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;
/* ⭐️ 헤더노드를 초기화해줌
   이 안에는 어떠한 값도 들어있지 않음
   헤더노드를 통해서 손쉽게 새로운 노드를 추가하거나 삭제할 수 있음 ⭐️ */
void init(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}
void dinsert(DListNode *before, element data) {
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
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
        ddelete(head, head->rlink);
    }
    free(head);

    return 0;
}