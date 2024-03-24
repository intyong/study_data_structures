#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
int list[MAX_SIZE];
int n;
void bubble_sort(int list[], int n) {
    int temp;
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                SWAP(list[j], list[j + 1], temp);
            }
        }
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
    printf("\nafter bubble sorting\n");
    bubble_sort(list, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    return 0;
}