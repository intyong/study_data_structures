#include <stdio.h>
#define MAX_TERMS 101
typedef struct term {
    int row;
    int col;
    int value;
} term;
term a[MAX_TERMS];  // 배열 a의 0번째에는 행, 열, 요소의 개수가 저장되어 있음
void transpose(term a[], term b[]) {
    int n;  // element의 개수를 저장하는 변수
    int currentb;   // 전치 행렬의 인덱스가 되는 변수
    n = a[0].value; // 전체 element 개수
    b[0].row = a[0].col;    // 기존 행렬의 열의 개수를 "전치 행렬의 행의 개수로 배정"
    b[0].col = a[0].row;    // 기존 행렬의 행의 개수를 "전치 행렬의 열의 개수로 배정"
    b[0].value = n; // 전체 element 개수 배정
    if (n > 0) {
        currentb = 1;
        /* a[]의 열의 개수만큼 반복 == b[]의 행만큼 반복 */
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