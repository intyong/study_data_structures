#include <stdio.h>
#include <stdlib.h>
#define ROW 5
#define COL 7
#define SIZE ROW * COL
char maze[ROW][COL] = {
     {'S', '0','0','1','0','0','0'},
     {'1', '1', '0', '1', '0', '1', '0'},
     {'0', '0', '0', '0', '1', '0', 'F'},
     {'0', '1', '1', '1', '1', '0', '1'},
     {'0', '0', '0', '0', '0', '0', '1'}
};
typedef struct Position {
    int x;
    int y;    
} Position;
Position stack[SIZE];
int top = -1;
void push(Position pos) {
    if (top < (SIZE) - 1) stack[++top] = pos;
}
Position pop() {
    if (top >= 0) return stack[top--];
    Position invalid = {-1, -1};
    return invalid;
}
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

void searchMaze(int startX, int startY) {
    push((Position){startX, startY});
    while (top != -1) {
        Position current = pop();
        int x = current.x;
        int y = current.y;
        if (maze[y][x] == 'F') {
            printf("목표점에 도달했습니다.\n");
            return;
        }
        maze[y][x] = '1';
        for (int i = 0; i < 4; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if (nextX >= 0 && nextY < COL && nextY >= 0 && nextY < ROW &&
            (maze[nextY][nextX] == '0' || maze[nextY][nextX] == 'F')) {
                push((Position){nextX, nextY});
            }
        }
    }
    printf("목표점에 도달할 수 없습니다.\n");
}
int main() {
    searchMaze(0, 0);
}