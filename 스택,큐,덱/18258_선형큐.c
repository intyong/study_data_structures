#include <stdio.h>
#include <string.h>
/* 선형 큐 구현 */
#define MAX_SIZE 2000003
int queue[MAX_SIZE] = {0};
int ffront = -1;
int rear = -1;
void push(int n) {
    if (rear != (MAX_SIZE - 1)) queue[++rear] = n;
}
int pop() {
    if (ffront == rear) return -1;
    else return queue[++ffront];
}
int size() {
    return (rear - ffront);
}
int empty() {
    if (ffront == rear) return 1;
    else return 0;
}
int front() {
    if (ffront == rear) return -1;
    else return (queue[ffront + 1]);
}
int back() {
    if (ffront == rear) return -1;
    else return (queue[rear]);
}
int main() {
    int n = 0;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        char com[10];
        scanf("%s", com);
        getchar();
        if (strcmp(com, "push") == 0) {
            int temp = 0;
            scanf("%d", &temp);
            getchar();
            push(temp);
        }
        else if (strcmp(com, "pop") == 0) {
            printf("%d\n", pop());
        }
        else if (strcmp(com, "size") == 0) {
            printf("%d\n", size());
        }
        else if (strcmp(com, "empty") == 0) {
            printf("%d\n", empty());
        }
        else if (strcmp(com, "front") == 0) {
            printf("%d\n", front());
        }
        else if (strcmp(com, "back") == 0) {
            printf("%d\n", back());
        }
    }

    return 0;
}