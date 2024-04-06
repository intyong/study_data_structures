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
int found[MAX_VERTICES];    // 방문한 정점 표시
void shortest_path(GraphType *g, int start) {
    int u;
    /* 변수로 받은 시작 정점부터 다른 정점까지의 거리 초기화
       동시에 found[] 초기화 */
    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE;
    distance[start] = 0;
    /* 변수로 받은 시작 정점으로 반복문 시작 */
    for (int i = 0; i < (g->n) - 1; i++) {
        print_status(g);
        /* distance[] 배열과 found[] 배열을 참고하여 모든 정점을 탐색하는 함수
           가장 최단 거리에 있는 정점의 인덱스가 반환됨 */
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        /* 모든 정점을 탐색하며 u를 기준으로 인접 정점인 경우
           현재 저장되어 있는 그 인접 정점까지의 거리보다
           u를 거쳐 인접 정점으로 가는 게 더 짧으면 최단 거리 업데이트 */
        for (int w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }
    }
}
int choose(int distance[], int n, int found[]) {
    /* 현재 방문하지 않은 정점들 중에서 가장 거리가 짧은 정점을 탐색
       탐색된 정점을 기준으로 계속 탐색을 하는 것임 */
    int min = INT_MAX;  // 최소 거리를 저장하는 변수
    int minpos = -1;    // 현재 정점과의 가장 최소 거리인 정점 위치
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}
void print_status(GraphType *g) {
    static int step = 1;
    printf("STEP %d: ", step++);
    printf("distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) printf(" * ");
        else printf("%2d ", distance[i]);
    }
        printf("\n");
        printf(" found: ");
        for (int i = 0; i < g->n; i++) {
            printf("%2d ", found[i]);
        }
        printf("\n\n");
}
int main() {
    GraphType g = { 7,
    {{ 0, 7, INF, INF, 3, 10, INF },
    {7, 0, 4, 10, 2, 6, INF },
    {INF, 4, 0, 2, INF, INF, INF },
    {INF, 10, 2, 0, 11, 9, 4 },
    {3, 2, INF, 11, 0, INF, 5},
    {10, 6, INF, 9, INF, 0, INF},
    {INF, INF, INF, 4, 5, INF, 0} }
    };
    shortest_path(&g, 0);
    
    return 0;
}