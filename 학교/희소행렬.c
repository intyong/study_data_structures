#include <stdio.h>
#define MAX_TERMS 101
typedef struct {
    int row;
    int col;
    int value;
} term;
term a[MAX_TERMS];
void transpose(term a[], term b[]) {
    int n, currentb;
    n = a[0].value; // 총 element 수
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;
    if (n > 0) {
        currentb = 1;
        for (int i = 0; i < a[0].col; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[currentb].value;
                    currentb++;
                }
            }
        }
    }
}
int main() {
    term a[4] = {{10, 10, 3}, {0, 0, 1}, {1, 2, 5}, {5, 3, 10}};
    term b[4];
    printf("row: %d, col: %d, value: %d\n", a[0].row, a[0].col, a[0].value);
    for (int i = 1; i < 4; i++) {
        printf(" %d, %d, %d\n", a[i].row, a[i].col, a[i].value);
    }
    printf("\n");
    transpose(a, b);
    printf("row: %d, col: %d, value: %d\n", b[0].row, b[0].col, b[0].value);
    for (int i = 1; i < 4; i++) {
        printf(" %d, %d, %d\n", b[i].row, b[i].col, b[i].value);
    }
    return 0;
}