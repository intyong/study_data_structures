#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 9
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
int list[MAX_SIZE] = {5, 3, 8, 4, 9, 1, 6, 2, 7};
int n;
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;
    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        /* low를 증가시키며 pivot보다 큰 값을 찾고, high를 증가시키며 pivot보다 작은 값을 찾는다
           둘 다 찾은 경우 서로의 값을 교환, 이를 반복하여 정렬해줌 */
        do low++;
        while (list[low] < pivot && low < MAX_SIZE);
        do high--;
        while (list[high] > pivot && low >= 0);
        if (low < high) SWAP(list[low], list[high], temp);
    } while(low < high);
    /* low, high의 값이 교차할 경우 반복문을 종료한 후 피봇을 적절한 위치로 변경 */
    SWAP(list[left], list[high], temp);
    return high;
}
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}
int main() {
    n = MAX_SIZE;
    printf("original list\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\nafter bubble sorting\n");
    quick_sort(list, 0, n - 1);
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", list[i]);
    }
    return 0;
}