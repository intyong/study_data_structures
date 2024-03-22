#include <stdio.h>
#define MAX_TERMS 101
#define MAX_COL 50
typedef struct {
    int row;
    int col;
    int value;
} term;
term a[MAX_TERMS];
void fast_transpose(term a[], term b[]) {
    int row_terms[MAX_COL]; // 원래 행렬의 열마다 non-zero element가 몇 번 나오는지 저장
    int starting_pos[MAX_COL];  // 원래 행렬의 열에서 이전 열의 non-zero element의 개수 누적합
    /* 이 둘을 통해서 행렬의 전치 속도를 높일 수 있음 */
    int num_cols = a[0].col;
    int num_terms = a[0].value;
    if (num_terms > 0) {
        for (int i = 0; i < num_cols; i++) row_terms[0] = 0;
        for (int i = 1; i <= num_terms; i++) row_terms[a[i].col]++;

        starting_pos[0] = 1;
        for (int i = 1; i < num_cols; i++) starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
    }
    for (int i = 1; i <= num_terms; i++) {
        int j = starting_pos[a[i].col];
        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
        starting_pos[a[i].col]++;
    }
}
int main() {
    term a[9] = {{6,6,8}, {0,0,15}, {0,3,22}, {0,5,-15}, {1,1,11}, {1,2,3}, {2,3,-6}, {4,0,91}, {5,2,28} };
    term b[9];
    fast_transpose(a,b);
}