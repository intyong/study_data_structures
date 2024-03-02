#include <iostream>
#define MAX_ELEMENT 100003
using namespace std;
typedef struct {
    int heap[MAX_ELEMENT];
    int heap_size;
} HeapType;
HeapType *createHeap() {
    HeapType *h = (HeapType *)malloc(sizeof(HeapType));
    h->heap_size = 0;
    return h;
}
void insertHeap(HeapType *h, int item) {
    int i = 0;
    i = ++(h->heap_size);
    while (i != 1 && item > h->heap[i / 2]) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}
int deleteHeap(HeapType *h) {
    if (h->heap_size == 0) return 0;
    int item, temp = 0;
    int parent = 1;
    int child = 2;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child] < h->heap[(child + 1)]) child++;
        if (temp > h->heap[child]) break;
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
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 0;
    cin >> n;
    HeapType *h = createHeap();
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        if (temp == 0) cout << deleteHeap(h) << "\n";
        else insertHeap(h, temp);
    }
    free(h);
    return 0;
}