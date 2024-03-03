#include <iostream>
#define MAX_SIZE 100005
using namespace std;
typedef struct {
    int heap[MAX_SIZE];
    int heap_size;
} HeapType;
HeapType *create() {
    HeapType *h = (HeapType *)malloc(sizeof(HeapType));
    h->heap_size = 0;
    return h;
}
void insert_heap(HeapType *h, int item) {
    int i = ++(h->heap_size);
    while (i != 1 && abs(item) <= abs(h->heap[i / 2])) {
        if (abs(item) == abs(h->heap[i / 2])) {
            if (item < h->heap[i / 2]) {
                h->heap[i] = h->heap[i / 2];
                i /= 2;
            }
            else break;
        } 
        else if (abs(item) < abs(h->heap[i / 2])) {
            h->heap[i] = h->heap[i / 2];
            i /= 2;
        }
    }
    h->heap[i] = item;
}
int delete_heap(HeapType *h) {
    if (h->heap_size == 0) return 0;
    int item = h->heap[1];
    int temp = h->heap[(h->heap_size)--];
    int parent = 1;
    int child = 2;
    while (child <= h->heap_size) {
        if (child < h->heap_size) {
            if (abs(h->heap[child]) > abs(h->heap[child + 1])) child++;
            else if (abs(h->heap[child]) == abs(h->heap[child + 1]) && h->heap[child] > h->heap[child + 1]) child++;
        }
        if (abs(temp) < abs(h->heap[child])) break;
        else if (abs(temp) == abs(h->heap[child]) && temp < h->heap[child]) break;
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
    HeapType *h = create();
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        if (temp == 0) cout << delete_heap(h) << '\n';
        else insert_heap(h, temp);
    }
    free(h);
    return 0;
}