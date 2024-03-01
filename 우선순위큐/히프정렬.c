#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
    int key;
} element;
typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}
void init(HeapType* h) {
    h->heap_size = 0;
}
/* 새로운 값을 추가하는 경우, 가장 아래부터 값을 비교하며 올라옴
   i = ++(h->heap_size)를 통해서 (item.key) 값을 가진 단말 노드로 시작
   만약 새로 추가된 노드[i]가 부모노드[i / 2]보다 크다면, 새로 추가된 노드는 부모 노드의 값으로 변경
   이후 i /= 2를 통해서 계속 노드를 타고 올라가면서 비교
   적절한 위치를 찾으면 그 위치에 item 값을 넣어줌으로써 완료 */
void insert_max_heap(HeapType* h, element item) {
    int i = 0;
    i = ++(h->heap_size);
    while ((i != 1) && (item.key > h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}
/* 가장 우선 순위에 있는 노드의 값을 반환하는 함수, 가장 마지막에 있는 노드를 맨 위로 올린 후 쭉 내려옴
   parent, child를 통해서 가장 앞 순위에 있는 노드의 값을 반환함과 동시에 히프가 흐트러지지 않도록 해줌
   item은 반환하고자 하는 노드를 저장, temp에는 가장 마지막에 있는 노드를 저장함과 동시에 heap_size를 1만큼 줄여줌
   while()을 통해서 왼쪽과 오른쪽 자식 노드의 key 값을 비교 후, 오른쪽 값이 더 크면 child++를 통해서 오른쪽 노드와 temp.key의 값을 비교
   만약 temp.key의 값이 더 크면 그대로 그 위치에 temp가 저장되고, 작을 경우 1번 노드의 값에 (삭제된 값) 자식 노드의 값을 저장
   이후 parent = child, child *= 2를 통해서 부모, 자식 관계를 유지하며 계속 내려감 */
element delete_max_heap(HeapType* h) {
    int parent, child = 0;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        /* 오른쪽에 자식 노드가 있는지 확인 &&
           왼쪽과 오른쪽 자식 노드의 key 값을 비교한 후, 만약 오른쪽 값이 더 크면 child++를 통해서 오른쪽 노드와 비교 */
        if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key) child++;
        if (temp.key >= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}
void heap_sort(element a[], int n) {
    int i;
    HeapType* h;
    h = create();
    init(h);
    for (i = 0; i < n; i++) insert_max_heap(h, a[i]);
    for (i = (n - 1); i >= 0; i--) a[i] = delete_max_heap(h);
    free(h);
}
#define SIZE 8
int main() {
    element list[SIZE] = { 23, 56, 11, 9, 56, 99, 27, 34 };
    heap_sort(list, SIZE);
    for (int i = 0; i < SIZE; i++) printf("%d ", list[i].key);
    printf("\n");

    return 0;
}