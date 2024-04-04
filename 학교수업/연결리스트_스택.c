#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode *link;
} StackNode;
typedef struct LinkedStackType {
    StackNode *top;
} LinkedStackType;
void init(LinkedStackType *s) {
    s->top = NULL;
}
int is_empty(LinkedStackType *s) {
    return (s->top == NULL);
}
void push(LinkedStackType *s, element item) {
    StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}
void print_stack(LinkedStackType *s) {
    for (StackNode *p = s->top; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}
element pop(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else {
        StackNode *temp = s->top;
        int item = temp->data;
        s->top = temp->link;
        free(temp);
        return item;
    }
}
element peek(LinkedStackType *s) {
    StackNode *temp = s->top;
    int item = temp->data;
    free(temp);
    return item;
}
int main() {
    LinkedStackType s;
    init(&s);
    push(&s, 1);
    print_stack(&s);
    push(&s, 2);
    print_stack(&s);
    push(&s, 3);
    print_stack(&s);

    pop(&s);
    print_stack(&s);
    pop(&s);
    print_stack(&s);
    pop(&s);
    print_stack(&s);

    return 0;
}