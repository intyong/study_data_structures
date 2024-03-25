#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
/* 큐 구현 */
#define MAX_QUEUE_SIZE 10
int queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;
void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
int is_empty() {
    return (front == rear);
}
int is_full() {
    return ((rear + 1) % MAX_QUEUE_SIZE == front);
}
void enqueue(int item) {
    if (is_full()) error("큐가 포화상태입니다");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}
int dequeue() {
    if (is_empty()) error("큐가 공백상태입니다");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}
/* bfs 구현 */
#define MAX_VERTICES 50
typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];
void graph_init(GraphType *g) {
    g->n = 0;
    for (int r = 0; r < MAX_VERTICES; r++) {
        for (int c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}
void insert_vertex(GraphType *g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}
void insert_edge(GraphType *g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}
void bfs_mat(GraphType *g, int v) {
    visited[v] = TRUE;
    printf("%d 방문 -> ", v);
    enqueue(v); // 탐색 시작 노드 삽입
    /* 탐색 시작 */
    while(!is_empty()) {
        v = dequeue();  // 현재 위치한 정점을 v에 저장
        /* 0부터 정점 모두 탐색 */
        for (int w = 0; w < g->n; w++) {
            /* 만약 현재 정점과 탐색으로 찾은 정점이 연결되어 있고, 그 정점에 아직 방문하지 않은 경우 */
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE; // 그 정점을 방문했다고 표시
                printf(" %d 방문 ->", w);
                enqueue(w); // 연결된 정점을 큐에 저장
            }
        }
    }
}
int main() {
    GraphType *g;
    g = (GraphType*)malloc(sizeof(GraphType));
    for (int i = 0; i < 6; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    printf("너비 우선 탐색\n");
    bfs_mat(g, 0);
    printf("\n");
    free(g);

    return 0;
}