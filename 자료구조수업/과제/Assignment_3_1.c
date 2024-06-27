#include <stdio.h>
#include <stdlib.h>
#define VERTICES 16
#define EDGES 24

typedef struct Edge {
    int start;
    int end;
    int weight;
} Edge;

Edge edges[EDGES];
int parent[VERTICES];

void init_parent() {
    for (int i = 0; i < VERTICES; i++) {
        parent[i] = -1;
    }
}

void set_edge(Edge *edges, int n, int start, int end, int weight) {
    edges[n].start = start;
    edges[n].end = end;
    edges[n].weight = weight;
}

int find_parent(int n) {
    if (parent[n] == -1) return n;
    else {
        while (parent[n] != -1) n = parent[n];
        return n;
    }
}

void set_union(int a, int b) {
    int root_a = find_parent(a);
    int root_b = find_parent(b);
    if (root_a != root_b) parent[root_a] = root_b;
}

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

void find_MST() {
    int selected_edge = 0;
    int u, v = 0;
    int i = 0;
    int total_cost = 0;
    init_parent();
    qsort(edges, EDGES, sizeof(Edge), compare);

    while (selected_edge < VERTICES - 1) {
        Edge temp = edges[i];
        u = find_parent(temp.start);
        v = find_parent(temp.end);
        if (u != v) {
            printf("Edge from %d to %d is selected\n", temp.start, temp.end);
            total_cost += temp.weight;
            selected_edge++;
            set_union(u, v);
        }
        i++;
    }
    printf("Total cost of MST: %d\n", total_cost);
}

int main() {
    set_edge(edges, 0, 1, 2, 3);
    set_edge(edges, 1, 2, 3, 1);
    set_edge(edges, 2, 3, 4, 4);
    set_edge(edges, 3, 1, 5, 2);
    set_edge(edges, 4, 2, 6, 5);
    set_edge(edges, 5, 3, 7, 1);
    set_edge(edges, 6, 4, 8, 6);
    set_edge(edges, 7, 5, 6, 1);
    set_edge(edges, 8, 6, 7, 5);
    set_edge(edges, 9, 7, 8, 8);
    set_edge(edges, 10, 5, 9, 3);
    set_edge(edges, 11, 6, 10, 4);
    set_edge(edges, 12, 7, 11, 2);
    set_edge(edges, 13, 8, 12, 6);
    set_edge(edges, 14, 9, 10, 2);
    set_edge(edges, 15, 10, 11, 4);
    set_edge(edges, 16, 11, 12, 6);
    set_edge(edges, 17, 9, 13, 2);
    set_edge(edges, 18, 10, 14, 6);
    set_edge(edges, 19, 11, 15, 4);
    set_edge(edges, 20, 12, 16, 4);
    set_edge(edges, 21, 13, 14, 3);
    set_edge(edges, 22, 14, 15, 5);
    set_edge(edges, 23, 15, 16, 7);

    find_MST();

    return 0;
}