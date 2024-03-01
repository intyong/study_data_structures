#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
int poly_eval(ListType* poly, int n) {
    int temp = 0;
    /* ListType*을 매개변수로 받았기 때문에 ListNode* p에 poly를 배정해버리면 오류가 발생
       (poly는 헤더노드이기 때문에 구조체 포인터 형태이기 때문) 따라서 poly->head를 통해서 poly->head가 가리키는 것,
       리스트의 첫번째 노드를 p로 배정하여 반복문 시작 */
    for (ListNode* p = poly->head; p != NULL; p = p->link) {
        temp += (p->coef * pow(n, p->expon));
    }
    return temp;
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
    ListType *list1;
    list1 = create();

    insert_last(list1, 3, 2);
    insert_last(list1, 2, 1);
    insert_last(list1, 1, 0);
    poly_print(list1);

    printf("input the number you wanna put in ");
    int n = 0;
    scanf("%d", &n);
    int ans = poly_eval(list1, n);
    printf("the answer is %d\n", ans);
    free(list1);
}