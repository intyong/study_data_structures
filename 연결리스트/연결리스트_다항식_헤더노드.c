#include <stdio.h>
#include <stdlib.h>
typedef struct ListNode {
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;
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
void insert_last(ListType* plist, int coef, int expon) {
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;
    if (plist->tail == NULL) {
        plist->head = plist-> tail = temp;
    }
    else {
        /* 헤더노드의 tail (plist->tail)은 마지막 노드.
           마지막 노드의 링크 (plist->tail->link는 현재
           NULL을 가리키고 있음)의 값을 temp로 연결해줌.
           그리고 헤더노드의 tail을 temp를 가리키도록 함.*/
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}
void poly_add (ListType* plist1, ListType* plist2, ListType* plist3) {
    ListNode* a = plist1->head;
    ListNode* b = plist2->head;
    int sum = 0;
    /* NULL == 0, a와 b 모두 널을 가리키지 않을 때까지 반복 */
    while (a && b) {
        if (a->expon == b->expon) {
            sum = a->coef + b->coef;
            if (sum != 0) insert_last(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
        }
        else if (a->expon > b->expon) {
            insert_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        else {
            insert_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }
    for (; a != NULL; a = a->link) {
        insert_last(plist3, a->coef, a->expon);
    }
    for (; b !=  NULL; b = b->link) {
        insert_last(plist3, b->coef, b->expon);
    }
}
void poly_print(ListType* plist) {
    ListNode* p = plist->head;
    printf("Polynominal = ");
    for (; p; p = p->link) {
        printf("%d^%d + ", p->coef, p->expon);
    }
    printf("\n");
}
int main() {
    ListType *list1, *list2, *list3;
    list1 = create();
    list2 = create();
    list3 = create();

    insert_last(list1, 3, 12);
    insert_last(list1, 2, 8);
    insert_last(list1, 1, 0);

    insert_last(list2, 8, 12);
    insert_last(list2, -3, 10);
    insert_last(list2, 1, 0);

    poly_print(list1);
    poly_print(list2);

    poly_add(list1, list2, list3);
    poly_print(list3);
    
    free(list1);
    free(list2);
    free(list3);
}