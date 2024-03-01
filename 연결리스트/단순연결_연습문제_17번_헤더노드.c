#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;
/* 헤더노드 하나로 리스트의 모든 노드를 통제함
   head는 리스트의 가장 첫번째 노드를 가리킴
   tail은 리스트의 가정 마지막 노드를 가리킴 */
typedef struct ListType {
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

ListType* create() {
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}
void insert_last(ListType* plist, int n) {
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    temp->data = n;
    temp->link = NULL;
    if (plist->tail == NULL) {
        plist->head = plist->tail = temp;
    }
    else {
        /* 헤더노드의 tail (plist->tail)은 마지막 노드
           마지막 노드의 링크 (plist->tail->link는 현재
           NULL을 가리키고 있음)의 값을 temp로 연결해줌
           그리고 헤더노드의 tail을 temp를 가리키도록 함 */
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}
void alternate(ListType *plist1, ListType *plist2, ListType* plist3) {
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    int count = 1;
    /* NULL == 0, a와 b 모두 널을 가리키지 않을 때까지 반복 */
    while(a && b) {
        if (count % 2) {
            insert_last(plist3, a->data);
            a = a->link;
        }
        else {
            insert_last(plist3, b->data);
            b = b->link;
        }
        count++;
    }
    for (; a != NULL; a = a->link) {
        insert_last(plist3, a->data);
    }
    for (; b != NULL; b = b->link) {
        insert_last(plist3, b->data);
    }
}
void print_list(ListType *plist) {
    ListNode* p = plist->head;
    for (; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}
int main() {
    ListType *a, *b, *c;
    a = create();
    b = create();
    c = create();

    insert_last(a, 1);
    insert_last(a, 2);
    insert_last(a, 3);
    insert_last(a, 4);
    
    insert_last(b, 5);
    insert_last(b, 6);
    insert_last(b, 7);
    insert_last(b, 8);

    print_list(a);
    print_list(b);

    alternate(a, b, c);
    print_list(c);

    free(a);
    free(b);
    free(c);
}