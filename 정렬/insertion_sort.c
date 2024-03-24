#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
int list[MAX_SIZE];
int n;
/* 0번째 요소부터 i - 1번째 요소까지는 정렬되어 있는 상태임
   i번째부터 n - 1번째 요소까지는 정렬되어 있지 않음
   i번째 요소를 key에 저장한 후, i - 1부터 0번째 요소까지 순회하며
   만약 key값이 어떤 요소보다 크면 그 앞 자리에 저장, 작으면 계속 순회 */
void insertion_sort(int list[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = key;
    }
}
int main() {
    n = MAX_SIZE;
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 100;
    }
    printf("original list\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\nafter insertion sorting\n");
    insertion_sort(list, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    return 0;
}