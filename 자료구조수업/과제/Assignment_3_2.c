#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VERTICES 17
#define INF INT_MAX

typedef struct Graph {
    int n;
    int weight[VERTICES][VERTICES];
} Graph;

int distance[VERTICES];
int visit[VERTICES];

void init_graph(Graph *g) {
    for (int i = 1; i < VERTICES; i++) {
        for (int j = 1; j < VERTICES; j++) {
            if (i == j) g->weight[i][j] = 0;
            else g->weight[i][j] = INF;
        }
    }
    g->n = VERTICES;
}
void set_graph(Graph *g, int start, int end, int weight) {
    g->weight[start][end] = weight;
}

int choose(int distance[], int visit[], int n) {
    int min = INF;
    int minpos = -1;
    for (int i = 1; i < n; i++) {
        if (distance[i] < min && !visit[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void Dijkstra(Graph *g, int start) {
    int u;
    for (int i = 1; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        visit[i] = 0;
    }
    visit[start] = 1;
    distance[start] = 0;

    for (int i = 1; i < g->n - 1; i++) {
        u = choose(distance, visit, g->n);
        visit[u] = 1;

        for (int v = 1; v < g->n; v++) {
            if (!visit[v] && g->weight[u][v] != INF && distance[u] + g->weight[u][v] < distance[v]) {
                distance[v] = distance[u] + g->weight[u][v];
            }
        }
    }

    for (int i = 1; i < g->n; i++) {
        printf("Distance from 1 to %d is %d\n", i, distance[i]);
    }
    printf("\n");
}

int main() {
    Graph g;
    init_graph(&g);
    
    set_graph(&g, 1, 2, 3);
    set_graph(&g, 2, 3, 1);
    set_graph(&g, 3, 4, 4);
    set_graph(&g, 1, 5, 2);
    set_graph(&g, 2, 6, 5);
    set_graph(&g, 3, 7, 1);
    set_graph(&g, 4, 8, 6);
    set_graph(&g, 5, 6, 1);
    set_graph(&g, 6, 7, 5);
    set_graph(&g, 7, 8, 8);
    set_graph(&g, 5, 9, 3);
    set_graph(&g, 6, 10, 4);
    set_graph(&g, 7, 11, 2);
    set_graph(&g, 8, 12, 6);
    set_graph(&g, 9, 10, 2);
    set_graph(&g, 10, 11, 4);
    set_graph(&g, 11, 12, 6);
    set_graph(&g, 9, 13, 2);
    set_graph(&g, 10, 14, 6);
    set_graph(&g, 11, 15, 4);
    set_graph(&g, 12, 16, 4);
    set_graph(&g, 13, 14, 3);
    set_graph(&g, 14, 15, 5);
    set_graph(&g, 15, 16, 7);

    Dijkstra(&g, 1);

    return 0;
}
