#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // 시작 정점으로부터의 최단 경로 거리

void print_status(GraphType *g) {
    static int step = 1;
    printf("STEP %d: ", step++);
    printf("distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) printf(" * ");
        else printf("%2d ", distance[i]);
    }
    printf("\n\n");
}

void bellman_ford(GraphType *g, int start) {
    // 시작 정점부터의 최단 경로 초기화
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;

    // (V-1)번 반복하면서 각 간선을 모두 검사
    for (int i = 0; i < g->n - 1; i++) {
        for (int u = 0; u < g->n; u++) {
            for (int v = 0; v < g->n; v++) {
                if (g->weight[u][v] != INF) {
                    if (distance[u] != INF && distance[v] > distance[u] + g->weight[u][v]) {
                        distance[v] = distance[u] + g->weight[u][v];
                    }
                }
            }
        }
        print_status(g);
    }

    // 음의 가중치 순환 검사
    for (int u = 0; u < g->n; u++) {
        for (int v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && distance[v] > distance[u] + g->weight[u][v]) {
                printf("Graph contains a negative-weight cycle\n");
                return;
            }
        }
    }
}

int main() {
    GraphType g = {
        7,
        {{ 0, 7, INF, INF, 3, 10, INF },
        { 7, 0, 4, 10, 2, 6, INF },
        { INF, 4, 0, 2, INF, INF, INF },
        { INF, 10, 2, 0, 11, 9, 4 },
        { 3, 2, INF, 11, 0, INF, 5 },
        { 10, 6, INF, 9, INF, 0, INF },
        { INF, INF, INF, 4, 5, INF, 0 }}
    };

    bellman_ford(&g, 0);
    return 0;
}