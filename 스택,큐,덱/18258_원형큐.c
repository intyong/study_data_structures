/* 선형큐와의 차이점
   * 삽입과 제거 시 단순하게 늘려주는 것이 아닌, MAX_SIZE로 나눈 나머지 값을 늘려줘야함 (큐의 재사용을 위해서)
   * front와 rear 인덱스의 초기값이 -1이 아닌 0 
   * front와 rear가 같을 경우에는 비어있는 상태
   * 원형큐의 포화를 판별하기 위해서는 front의 값을 (rear + 1) % MAX_SIZE 만큼 늘린 후, front의 값과 같은지 확인 */
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 2000003
int queue[MAX_SIZE] = {0};
int ffront = 0;
int rear = 0;
void push(int n) {
    if (ffront != (rear + 1) % MAX_SIZE) {
        rear = (rear + 1) % MAX_SIZE;
        queue[rear] = n;
    }
}
int pop() {
    if (ffront != rear) {
        ffront = (ffront + 1) % MAX_SIZE;
        return queue[ffront];
    }
    else return -1;
}
int size() {
    return (rear - ffront);
}
int empty() {
    if (rear == ffront) return 1;
    else return 0;
}
int front() {
    if (ffront != rear) return queue[ffront + 1];
    else return 0;
}
int back() {
    if (ffront != rear) return queue[rear];
    else return 0;
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