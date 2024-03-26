#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L
int parent[MAX_VERTICES];   // 부모노드
/* 부모 노드를 모두 -1로 초기화 */
void set_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}
/* curr가 속하는 집합을 반환한다. */
int set_find(int curr) {
    if (parent[curr] == -1) return curr;
    while (parent[curr] == -1) curr = parent[curr];
    return curr;
}
/* 두 개의 원소가 속한 집합을 합친다. */
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2) parent[root1] = root2;
}
/* 간선을 나타내는 구조체 */
struct Edge {
    int start, end, weight;
};
typedef struct GraphType {
    int n;  // 간선의 개수
    struct Edge edges[2 * MAX_VERTICES];    // 한 정점 당 두 개의 간선이 있을 수 있으니 2 * MAX_VERTICES
} GraphType;
/* 그래프 초기화 */
void graph_init(GraphType *g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}
/* 간선 삽입 연산 */
void insert_edge(GraphType *g, int start, int end, int w) {
    g->edges[g->n].start = start;   // 간선의 시작점
    g->edges[g->n].end = end;       // 간선의 종료점
    g->edges[g->n].weight = w;      // 간선의 가중치
    g->n++; // 간선의 개수 늘려주기
}
/* 간선의 가중치를 비교하여 가중치가 더 높은 것을 반환 */
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*) a;
    struct Edge* y = (struct Edge*) b;
    return (x->weight - y->weight);
}
/* kruskal의 최소 비용 신장 트리 프로그램 */
void kruskal(GraphType *g) {
    int edge_accepted = 0;  // 현재까지 선택된 간선의 수
    int uset, vset; // 정점 u와 정점 v의 집합 번호
    struct Edge e;

    set_init(g->n); // 부모 노드 집합 초기화
    qsort(g->edges, g->n, sizeof(struct Edge), compare);
    printf("크루스칼 최소 신장 트리 알고리즘 \n");
    int i = 0;
    while (edge_accepted < (g->n - 1)) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}
int main() {
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);

    return 0;
}