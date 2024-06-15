#include <stdio.h>
#include <stdlib.h>

#define INF 1000000 // 무한대를 나타내기 위한 큰 값

struct Edge {
    int u, v, weight;
};

void bellmanFord(int vertices, int edges, struct Edge edgeList[], int start) {
    int distance[vertices];
    for (int i = 0; i < vertices; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;

    // 벨만-포드 알고리즘의 핵심 반복문
    for (int k = 0; k < vertices - 1; k++) {
        for (int i = 0; i < edges; i++) {
            int u = edgeList[i].u;
            int v = edgeList[i].v;
            int weight = edgeList[i].weight;
            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // 음의 사이클 검출
    for (int i = 0; i < edges; i++) {
        int u = edgeList[i].u;
        int v = edgeList[i].v;
        int weight = edgeList[i].weight;
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            printf("Graph contains a negative-weight cycle\n");
            return;
        }
    }

    // 결과 출력
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; i++) {
        if (distance[i] == INF) {
            printf("%d \t\t INF\n", i);
        } else {
            printf("%d \t\t %d\n", i, distance[i]);
        }
    }
}

int main() {
    int vertices = 5;
    int edges = 8;
    struct Edge edgeList[] = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
        {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    bellmanFord(vertices, edges, edgeList, 0);
    return 0;
}
