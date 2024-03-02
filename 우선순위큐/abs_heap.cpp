#include <iostream>
#include <cstdlib>
#define MAX_SIZE 100003
using namespace std;
typedef struct {
    int heap[MAX_SIZE];
    int size;
} HeapType;
HeapType* createHeap() {
    HeapType* h = (HeapType *)malloc(sizeof(HeapType));
    h->size = 0;
    return h;
}
/* modify soon */
void insertHeap(HeapType *h, int item) {
    int i = 0;
    i = ++(h->size);
    while (i != 1 && abs(item) <= abs(h->heap[i / 2])) {
        if (abs(item) <= abs(h->heap[i / 2]) && item < h->heap[i / 2]) {
            h->heap[i] = h->heap[i / 2];
            i /= 2;
        }
    }
    h->heap[i] = item;
}
/* modify soon */
int deleteHeap(HeapType *h) {
    if (h->size == 0) return 0;
    int item = h->heap[1];
    int temp = h->heap[(h->size)--];
    int parent = 1;
    int child = 2;
    while (child <= h->size) {
        if (child < h->size) {
            if (abs(h->heap[child]) > abs(h->heap[child + 1])) child++;
            else if (abs(h->heap[child]) == abs(h->heap[child + 1])) {
                if (h->heap[child] > h->heap[child + 1]) child++;
            }
        }
        if (temp < h->heap[child]) break;
        else {
            h->heap[parent] = h->heap[child];
            parent = child;
            child *= 2;
        }
    }
    h->heap[parent] = temp;
    return item;
}
int main() {
    int n = 0;
    cin >> n;
    HeapType *h = (HeapType *)malloc(sizeof(HeapType));
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        if (temp == 0) cout << deleteHeap(h) << endl;
        else insertHeap(h, temp);
    }
    free(h);
    return 0;
}