#include <stdio.h>
/* hanoi_tower(n을 from에서 tmp를 거쳐 to로 옮긴다) */
void hanoi_tower(int n, char from, char tmp, char to) {
    if (n == 1) printf("원판 1을 %c에서 %c로 옮긴다.\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        printf("원판 %d를 %c에서 %c로 옮긴다.\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
}
int main() {
    hanoi_tower(3, 'A', 'B', 'C');
    return 0;
}