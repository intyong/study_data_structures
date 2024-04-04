#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode *link;
} QueueNode;
typedef struct {
    QueueNode *front, *rear;
} LinkedQueueType;
void init(LinkedQueueType *q) {
    q->front = NULL;
    q->rear = NULL;
}
int is_empty(LinkedQueueType *q) {
    return (q->front == NULL);
}
void enqueue(LinkedQueueType *q, element item) {
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->data = item;
    temp->link = NULL;
    if (is_empty(q)) {
        q->front = temp;
        q->rear = temp;
    }
    else {
        q->rear->link = temp;
        q->rear = temp;
    }
}
element dequeue(LinkedQueueType *q) {
    if (is_empty(q)) {
        fprintf(stderr, "큐가 비어있습니다.\n");
        exit(1);
    }
    else {
        QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
        temp = q->front;
        int item = temp->data;
        q->front = temp->link;
        free(temp);
        return item;
    }
}
void print_queue(LinkedQueueType *q) {
    for (QueueNode *p = q->front; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}
int main() {
    LinkedQueueType q;
    init(&q);

    enqueue(&q, 10);
    print_queue(&q);
    enqueue(&q, 20);
    print_queue(&q);
    enqueue(&q, 30);
    print_queue(&q);

    dequeue(&q);
    print_queue(&q);
    dequeue(&q);
    print_queue(&q);
    dequeue(&q);
    print_queue(&q);

    return 0;
}