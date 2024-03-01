#include <stdio.h>
int stack[1000004] = {0};
int ttop = -1;
/* 1 */
void push(int n) {
    stack[++ttop] = n;
}
/* 2 */
int pop() {
    if (ttop == -1) return (-1);
    else return stack[ttop--];
}
/* 3 */
int size() {
    return (ttop + 1);
}
/* 5 */
int top() {
    if (ttop == -1) return (-1);
    else return stack[ttop];
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
            push(t);
        }
        else if (temp == 2) {
            printf("%d\n", pop());
        }
        else if (temp == 3) {
            printf("%d\n", size());
        }
        else if (temp == 4) {
            if (ttop == -1) printf("%d\n", 1);
            else printf("%d\n", 0);
        }
        else if (temp == 5) {
            printf("%d\n", top());
        }
    }

    return 0;
}