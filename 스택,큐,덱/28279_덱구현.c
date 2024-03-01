#include <stdio.h>
/* 원형 덱 구현
   원형 큐와 매유 유사, 하지만 맨 앞에 요소를 추가하는 것, 맨 뒤의 요소를 제거하는 기능 추가
   front == 맨 앞 요소의 앞을 가리킴, 맨 앞에 값을 추가하고, 제거할 때 이용됨
   rear == 맨 뒤 요소를 가리킴, 맨 뒤에 값을 추가하고, 제거할 때 이용됨 */
#define MAX_SIZE 1000005
int deq[MAX_SIZE] = {0};
int front = 0;
int rear = 0;
int count = 0;
void input_front(int n) {
    if ((rear + 1) % MAX_SIZE != front) {
        deq[front] = n;
        front = (front - 1 + MAX_SIZE) % MAX_SIZE;
        count++;
    }
}
void input_rear(int n) {
    if ((rear + 1) % MAX_SIZE != front) {
        rear = (rear + 1) % MAX_SIZE;
        deq[rear] = n;
        count++;
    }
}
int pop_front() {
    if (front == rear) return -1;
    else {
        front = (front + 1) % MAX_SIZE;
        count--;
        return deq[front];
    }
}
int pop_rear() {
    if (front == rear) return -1;
    else {
        int temp = deq[rear];
        rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;
        count--;
        return temp;
    }
}
int size() {
    return count;
}
int isempty() {
    if (front == rear) return 1;
    else return 0;
}
int print_front() {
    if (front != rear) return deq[(front + 1) % MAX_SIZE];
    else return -1;
}
int print_rear() {
    if (front != rear) return deq[rear];
    else return -1;
}
int main() {
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int temp = 0;
        scanf("%d", &temp);
        if (temp == 1) {
            int t = 0;
            scanf("%d", &t);
            input_front(t);
        }
        else if (temp == 2) {
            int t = 0;
            scanf("%d", &t);
            input_rear(t);
        }
        else if (temp == 3) {
            printf("%d\n", pop_front());
        }
        else if (temp == 4) {
            printf("%d\n", pop_rear());
        }
        else if (temp == 5) {
            printf("%d\n", size());
        }
        else if (temp == 6) {
            printf("%d\n", isempty());
        }
        else if (temp == 7) {
            printf("%d\n", print_front());
        }
        else if (temp == 8) {
            printf("%d\n", print_rear());
        }
    }

    return 0;
}