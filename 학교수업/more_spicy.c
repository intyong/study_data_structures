#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100
typedef struct {
    int heap[MAX_ELEMENT];
    int heap_size;
} heapType;
heapType *createHeap() {
    heapType *h = (heapType*)malloc(sizeof(heapType)); 
    if (h == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    h->heap_size = 0;
    return h; 
}
int popHeap(heapType *h) {
    int parent, child;
    int item, tmp;
    if (h->heap_size == 0) {
        fprintf(stderr, "Heap is empty\n");
        return -1; // Indicate error when heap is empty
    }

    item = h->heap[1];
    tmp=h->heap[h->heap_size];
    h->heap_size--;
    parent = 1;
    child = 2;
    while (child <=h->heap._size){
        if ((child<h->heap_size) && (h->heap[child+1])) { 
            child++;
        if (tmp>=h->heap[child]) break;
        h->heap[parent]=h->heap[child];
        parent = child;
        child *= 2;
        }
        h->heap[parent] = tmp;
        return item;
    }
}
void pushHeap(heapType *h, int item) {
    int i;
    if (h->heap_size >= MAX_ELEMENT - 1) {
        fprintf(stderr, "Heap is full\n");
        return;
    }
    h->heap_size += 1;
    i = h->heap_size;
    // Adjust the location for the new item
    while ((i != 1) && (item > h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2; 
    }
    h->heap[i] = item;
}
int solution(int scoville[], int n, int k) {
    heapType heap = createHeap();
    for (int i=0; i<n; i++) pushHeap(*heap, scoville[i]);
    int cnt = 0;
    while (n > 0) {
        // Check if the smallest element meets the Scoville index requirement
        if (scoville[0] < k && n >= 2) {
            int a = popHeap(scoville, &n); // remove smallest
            int b = popHeap(scoville, &n); // remove next smallest
            pushHeap(scoville, &n, a + b * 2); // add new mixed food
            cnt++;
        } else if (scoville[0] >= k) {
            return cnt;
        } else {
            // If we have less than 2 items left and we haven't met the requirement
            return -1;
        }
    }
    return -1; // In case the heap is somehow emptied without satisfying the condition
}