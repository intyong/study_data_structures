#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
int list[MAX_SIZE];
int n;
/* 첫번째 요소를 least로 배정한 후, n - 1까지 순회하면서 가장 작은 요소를 선택하여 맨 앞의 요소와 바꾸어줌 */
void selection_sort(int list[], int n) {
    int least, temp;
    for (int i = 0; i < n - 1; i++) {
        least = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[least]) least = j;
        }
        SWAP(list[i], list[least], temp);
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
    printf("\nafter selection sorting\n");
    selection_sort(list, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    return 0;
}