#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define empty(item) (strlen((item).key) == 0)
#define equal(item1, item2) (!strcmp((item1).key, (item2).key))
#define KEY_SIZE 10 // 탐색키의 최대 길이
#define TABLE_SIZE 13   // 해싱 테이블의 크기 = 소수

typedef struct {
    char key[KEY_SIZE];
} element;

element hash_table[TABLE_SIZE];

/* 해시 테이블 초기화 */
void init_table(element ht[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht[i].key[0] = '\0';  // '\n'에서 '\0'으로 변경
    }
}

/* 문자로 된 키를 숫자로 변환 */
int transform(char *key) {
    int number = 0;
    while (*key) {
        number = 31 * number + *key++;
    }
    return number;
}

/* 제산 함수 */
int hash_function(char *key) {
    return transform(key) % TABLE_SIZE;
}

void hash_lp_add(element item, element ht[]) {
    int i, hash_value = 0;
    hash_value = i = hash_function(item.key);   // 해시 함수를 한 번만 호출함으로써 효율성 향상
    while (!empty(ht[i])) {
        if (equal(item, ht[i])) {
            fprintf(stderr, "탐색키가 중복되었습니다\n");
            exit(1);
        }
        i = (i + 1) % TABLE_SIZE;
        if (i == hash_value) {
            fprintf(stderr, "테이블이 가득찼습니다\n");
            exit(1);
        }
    }
    ht[i] = item;
}

void hash_lp_search(element item, element ht[]) {
    int i, hash_value;
    hash_value = i = hash_function(item.key);
    while (!empty(ht[i])) {
        if (equal(item, ht[i])) {
            printf("탐색 %s: 위치 = %d\n", item.key, i); // 수정: fprintf -> printf
            return; 
        }
        i = (i + 1) % TABLE_SIZE;
        if (i == hash_value) {
            printf("찾는 값이 테이블에 없음\n"); // 수정: fprintf -> printf
            return;
        }
    }
    printf("찾는 값이 테이블에 없음\n"); // 수정: fprintf -> printf
}

void hash_lp_print(element ht[]) {
    printf("\n====================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d] %s\n", i, ht[i].key);
    }
    printf("\n====================\n");
}

int main() {
    char *s[7] = { "do", "for", "if", "case", "else", "return", "function" };
    element e;

    // 해시 테이블 초기화
    init_table(hash_table);

    for (int i = 0; i < 7; i++) {
        strcpy(e.key, s[i]);
        hash_lp_add(e, hash_table);
        hash_lp_print(hash_table);
    }
    for (int i = 0; i < 7; i++) {
        strcpy(e.key, s[i]);
        hash_lp_search(e, hash_table);
    }
    return 0;
}
