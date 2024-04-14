#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
int list[MAX_SIZE] = {5, 4, 3, 2, 1};
int n;
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;
    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        /* low를 증가시키며 pivot보다 큰 값을 찾고, high를 감소시키며 pivot보다 작은 값을 찾는다
           둘 다 찾은 경우 서로의 값을 교환, 이를 반복하여 정렬해줌 */
        do low++;
        while (list[low] < pivot && low < MAX_SIZE);
        do high--;
        while (list[high] > pivot && low >= 0);
        if (low < high) SWAP(list[low], list[high], temp);
    } while(low < high);
    /* do, while()문의 반복을 통해 low와 high를 적절한 위치로 보낸 다음,
       low, high의 값이 교차할 경우 반복문을 종료한 후 <피봇과 high가 가리키는 숫자와 위치를 변경> */
    SWAP(list[left], list[high], temp);
    /* high의 위치를 반환해줌으로써 high 위치에 있는 수는 정렬된 수가 됨 */
    for (int i = 0; i < MAX_SIZE; i++) printf("%d ", list[i]);
    printf("\n");
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
    printf("\nafter quick sorting\n");
    quick_sort(list, 0, n - 1);
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", list[i]);
    }
    return 0;
}