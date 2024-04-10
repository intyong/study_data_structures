#include <stdio.h>
#define MAX_TERMS 101
#define MAX_COL 50
typedef struct term {
    int row;
    int col;
    int value;
} term;
term a[MAX_TERMS];  // 배열 a의 0번째에는 행, 열, 요소의 개수가 저장되어 있음
void fast_transpose(term a[], term b[]) {
    /* 이 둘을 통해서 행렬의 전치 속도를 높일 수 있음 */
    int row_terms[MAX_COL]; // 기존 행렬의 열마다 non-zero element가 몇 번 나오는지 저장
    int starting_pos[MAX_COL];  // 기존 행렬에서 이전 열의 non-zero element의 개수 누적합
    
    int num_cols = a[0].col;    // 기존 행렬의 열의 개수 저장
    int num_terms = a[0].value; // 기존 행렬의 term의 개수 저장 (non-zero element의 개수)
    if (num_terms > 0) {
        /* 기존 행렬의 열의 개수만큼 row_terms를 초기화.
           row_terms는 기존 행렬의 열마다 non-zero element가 몇 번 나오는지를 저장하기 위한 것이기 때문이다. */
        for (int i = 0; i < num_cols; i++) row_terms[i] = 0;

        /* non-zero element만큼 반복하여 a[i].col을 인덱스로 row_terms의 개수를 더해줌 */
        for (int i = 1; i <= num_terms; i++) row_terms[a[i].col]++;

        starting_pos[0] = 1;
        /* starting_pos는 인덱스에 해당하는 열을 가진 요소가 전치 행렬에서 몇 번째에 위치하는지를 저장하고 있음
           starting_pos[i - 1] + row_terms[i -1] (이전 요소의 개수)을 통해서 그 위치를 정해줄 수 있음 */
        for (int i = 1; i < num_cols; i++) starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
    }
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;
    /* i는 a를 순회하기 위한 인덱스 */
    for (int i = 1; i <= num_terms; i++) {
        /* a[i]를 순회하며 a[i].col을 j에 저장
           그 인덱스 값으로 b[] 전치 
           마지막에 starting_pos[a[i].col]를 1만큼 늘려 
           다음에 그 행에 접근할 때는 그 다음 위치에 저장되도록 함 */
        int j = starting_pos[a[i].col];
        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
        starting_pos[a[i].col]++;
        printf("%d %d에 있던 %d를 %d %d에 저장\n", a[i].row, a[i].col, a[i].value, b[j].row, b[j].col);
    }
}
int main() {
    term a[9] = {{6,6,8}, {0,0,15}, {0,3,22}, {0,5,-15}, {1,1,11}, {1,2,3}, {2,3,-6}, {4,0,91}, {5,2,28} };
    term b[9];
    printf("row: %d, col: %d, value: %d\n", a[0].row, a[0].col, a[0].value);

    fast_transpose(a,b);

    return 0;
}