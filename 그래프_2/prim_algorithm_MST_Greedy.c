/* ⭐️ 시작점을 기준으로 가장 가까운 노드 선택
   선택한 노드를 집합 Y에 넣어주고
   V - Y에서 다시 가장 가까운 노드를 선택
   V == Y가 되면 MST 완성 ⭐️ */
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L
typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int seleted[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n) {
    /* 방문하지 않은 정점까지의 거리 비교를 위하여 v에다가 방문하지 않은 정점 아무거나 하나를 담음
       이후 v를 초기값으로 최소 거리 비교를 거듭하며 아직 방문하지 않은 정점 중에서 최소 거리인 정점을 반환
       방문하지 않은 정점을 기반으로 경로를 탐색하기 때문에 사이클이 형성되지 않음 */
    int v;
    for (int i = 0; i < n; i++) {
        if (!seleted[i]) {
            v = i;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        /* 인접하지 않은 정점일 경우 distance[]가 INF이기 때문에 애초에 인접 여부를 검사할 필요 없음
           INF보다 작은 값으로 넘어올 경우 애초에 인접한 것임 */
        if (!seleted[i] && (distance[i] < distance[v])) v = i;
    }
    return v;
}
void prim(GraphType *g, int s) {
    /* 모든 정점의 거리를 무한대로 초기화 */
    for (int u = 0; u < g->n; u++) {
        distance[u] = INF;
    }
    distance[s] = 0;    // 시작 정점의 거리를 0으로 초기화
    /* 각 반복마다 아직 선택되지 않은 정점 중에서 최소 거리를 가진 정점을 선택 */
    for (int i = 0; i < g->n; i++) {
        int u = get_min_vertex(g->n);   // 맨 처음 i = 0일 때 u = 0이 반환됨, 아직 선택되지 않은 정점 중 최소 거리를 가진 정점 받아옴
        seleted[u] = TRUE;  // 반환된 정점을 방문 처리
        if (distance[u] == INF) return;
        printf("정점 %d 추가 \n", u);
        /* 모든 정점을 순환하며 방문한 정점을 기준으로 연결되어 있는 곳들의 거리를 업데이트 */
        for (int v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF) {
                /* 아직 방문하지 않았고, 현재 저장되어 있는 v의 거리 (웬만해서는 무한대) 보다
                   현재 정점에서부터 v까지의 거리가 더 짧을 경우 거리를 업데이트 */
                if (!seleted[v] && g->weight[u][v] < distance[v]) distance[v] = g->weight[u][v];
            }
        }
    }
}
int main() {
    GraphType g = { 7,
    {{ 0, 29, INF, INF, INF, 10, INF },
    { 29, 0, 16, INF, INF, INF, 15 },
    { INF, 16, 0, 12, INF, INF, INF },
    { INF, INF, 12, 0, 22, INF, 18 },
    { INF, INF, INF, 22, 0, 27, 25 },
    { 10, INF, INF, INF, 27, 0, INF },
    { INF, 15, INF, 18, 25, INF, 0 } }
    };
    prim(&g, 0);

    return 0;
}