#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* 동적 배열 구현 */
typedef struct DynamicArray {
    int *nums;    // 배열 요소들을 저장할 포인터
    int size;     // 현재 배열의 요소 개수
    int capacity; // 배열의 최대 용량
} DynamicArray;

/* 동적 배열을 생성 */
DynamicArray *initialize_Array(int capacity) {
    if (capacity < 1) {
        capacity = 1;  // 최소 크기를 1로 설정
    }
    DynamicArray *DyArray = malloc(sizeof(DynamicArray)); // 동적 할당을 이용하여 동적 배열 생성
    if (DyArray == NULL) {
        perror("Failed to allocate memory\n"); // 메모리 할당 실패시 에러 메시지 출력
        exit(1);
    }
    DyArray->nums = malloc(capacity * sizeof(int)); // 주어진 용량만큼 메모리 할당
    if (DyArray->nums == NULL) { // 메모리 할당 실패 검사
        free(DyArray); // DyArray 메모리 해제
        perror("Failed to allocate memory for array elements\n"); // 메모리 할당 실패시 에러 메시지 출력
        exit(1);
    }
    DyArray->size = 0; // 초기 요소의 개수는 0개
    DyArray->capacity = capacity; // 매개 변수로 받은 값으로 초기 용량 설정
    /* 이 프로그램에서 0은 비어있는 것을 의미 */
    memset(DyArray->nums, 0, capacity * sizeof(int));
    return DyArray;
}

/* 배열의 용량을 두 배로 확장 */
void realloc_Array(DynamicArray *DyArray) {
    int new_capacity = DyArray->capacity * 2; // 새로운 배열 용량
    int *new_array = realloc(DyArray->nums, new_capacity * sizeof(int)); // 메모리 재할당, 용량이 두 배로 늘어남
    if (new_array == NULL) {
        perror("Failed to expand array\n"); // 메모리 재할당 실패 시 에러 메시지 출력
        return;
    }
    DyArray->nums = new_array;
    DyArray->capacity = new_capacity;   
    memset(DyArray->nums + DyArray->capacity, 0, (new_capacity - DyArray->capacity) * sizeof(int)); // 확장된 부분을 0으로 초기화
}

/* 배열이 가득 찼는지 확인 */
int isFull(DynamicArray *DyArray) {
    return DyArray->size == DyArray->capacity;
}

/* 배열의 맨 앞에 요소 추가 */
void insertFront_Array(DynamicArray *DyArray, int value) {
    if (isFull(DyArray)) realloc_Array(DyArray); // 배열이 가득 찼다면 용량 확장
    for (int i = DyArray->size; i > 0; i--) {
        DyArray->nums[i] = DyArray->nums[i - 1]; // 요소들을 한 칸씩 뒤로 이동
    }
    DyArray->nums[0] = value; // 새 요소를 첫번째 위치에 삽입
    DyArray->size++; // 배열의 현재 요소 개수를 늘려줌
}

/* 배열의 뒤에 요소 추가 */
void insertBack_Array(DynamicArray *DyArray, int value) {
    if (isFull(DyArray)) realloc_Array(DyArray); // 배열이 가득 찼다면 용량 확장
    DyArray->nums[DyArray->size] = value; // 새 요소를 마지막 위치에 추가
    DyArray->size++; // 배열의 현재 요소 개수를 늘려줌
}

/* 특정 인덱스에 요소 추가 */
void insertSpecific_Array(DynamicArray *DyArray, int value, int idx) {
    if (idx < 0 || idx > DyArray->size) {  // 인덱스가 0보다 작거나 배열의 현재 크기보다 클 경우 에러 메시지 출력
        printf("Not a valid index!\n");
        return;
    }
    if (isFull(DyArray)) realloc_Array(DyArray); // 배열이 가득 찼다면 용량 확장
    for (int i = DyArray->size; i > idx; i--) {
        DyArray->nums[i] = DyArray->nums[i - 1]; // idx 이후의 요소들을 한 칸씩 뒤로 이동
    }
    DyArray->nums[idx] = value; // 새 요소를 idx 위치에 삽입
    DyArray->size++; // 배열의 현재 요소 개수를 늘려줌
}

/* 배열의 첫번째 요소 삭제 */
void deleteFront_Array(DynamicArray *DyArray) {
    if (!DyArray->size) {
        printf("Array is already empty!\n"); // 배열이 비어있다면 메세지 출력
        return;
    }
    for (int i = 0; i < DyArray->size - 1; i++) {
        DyArray->nums[i] = DyArray->nums[i + 1]; // 모든 요소를 한 칸씩 앞으로 이동
    }
    DyArray->nums[DyArray->size - 1] = 0;
    DyArray->size--; // 배열의 현재 요소 개수를 줄여줌
}

/* 배열의 마지막 요소 삭제 */
void deleteBack_Array(DynamicArray *DyArray) {
    if (!DyArray->size) {
        printf("Array is already empty!\n"); // 배열이 비었다면 메시지 출력
        return;
    }
    DyArray->nums[DyArray->size - 1] = 0; // 배열의 마지막 요소를 0 (비어있는 것을 의미)으로 저장
    DyArray->size--; // 배열의 현재 요소 개수를 줄여줌
}

/* 특정 인덱스의 요소 삭제 */
void deleteSpecific_Array(DynamicArray *DyArray, int idx) {
    if (idx < 0 || idx >= DyArray->size) {
        printf("Not a valid index!\n"); // 인덱스가 범위를 벗어났다면 메시지 출력
        return;
    }
    if (!DyArray->size) {
        printf("Array is already empty!\n"); // 배열이 비었다면 메시지 출력
        return;
    }
    for (int i = idx; i < DyArray->size - 1; i++) {
        DyArray->nums[i] = DyArray->nums[i + 1]; // idx 이후의 요소들을 한 칸씩 앞으로 이동
    }
    DyArray->nums[DyArray->size - 1] = 0;
    DyArray->size--; // 배열의 현재 요소 개수를 줄여줌
}

/* 특정 인덱스의 요소에 접근 */
void access_Array(DynamicArray *DyArray, int idx) {
    if (idx < 0 || idx >= DyArray->size) {
        printf("Not a valid index!\n"); // 인덱스가 범위를 벗어났다면 메시지 출력
        return;
    }
    printf("%d\n", DyArray->nums[idx]); // 해당 인덱스의 요소 출력
}

/* 배열의 모든 요소 출력 */
void print_Array(DynamicArray *DyArray) {
    for (int i = 0; i < DyArray->capacity; i++) {
        printf("|%d|", DyArray->nums[i]); // 배열의 모든 요소를 출력
    }
    printf("\n");
}
/* 동적 배열 구현 완료 */

/* 단일 연결 리스트 구현, 구조체 ListNode는 단일 연결 리스트의 노드를 의미 */
typedef struct ListNode {
    int data;               // 노드가 저장할 데이터
    struct ListNode *link;  // 다음 노드를 가리키는 링크
} ListNode;

/* 비어 있는 리스트 초기화 */
ListNode* initialize_List() {
    return NULL; // 빈 리스트로 초기화
}

/* 리스트 길이 계산 */
int ListLength(ListNode *head) {
    int length = 0;
    for (ListNode *t = head; t != NULL; t = t->link) {
        length++; // 리스트를 순회하며 길이를 측정
    }
    return length; // 리스트의 길이 반환
}

/* 리스트의 앞에 노드 추가 */
ListNode *insertFront_List(ListNode *head, int value) {
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode)); // 동적할당을 통해 새로운 노드 생성
    if (new_node == NULL) {
        printf("Failed to allocate memory\n"); // 메모리 할당 실패 시 메시지 출력
        return head;
    }
    new_node->data = value; // 새 노드의 값을 매개 변수의 값으로 할당
    new_node->link = head; // 새 노드를 기존의 첫번째 노드 앞에 위치
    head = new_node; // 새 노드를 새로운 헤드로 설정
    return head;
}

/* 리스트의 뒤에 노드 추가 */
ListNode *insertBack_List(ListNode *head, int value) {
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode)); // 동적할당을 통해 새로운 노드 생성
    if (new_node == NULL) {
        printf("Failed to allocate memory\n"); // 메모리 할당 실패 시 메시지 출력
        return head;
    }
    new_node->data = value; // 새 노드의 값을 매개 변수의 값으로 할당
    new_node->link = NULL; // 리스트의 마지막에 노드가 추가되는 것이므로 NULL을 가리키고 있음
    if (head == NULL) head = new_node; // 리스트가 비어 있으면 새 노드를 헤드로 설정
    else {
        ListNode *pre = head;
        /* 이 반복문을 통하여 pre는 가장 마지막 노드를 가리킴 */
        for (ListNode *t = head; t != NULL; t = t->link) {
            pre = t;
        }
        pre->link = new_node; // 마지막 노드의 다음으로 새 노드 연결
    }
    return head;
}

/* 특정 위치에 노드 추가 */
ListNode *insertSpecific_List(ListNode *head, int value, int idx){
    int length = ListLength(head); // 리스트의 현재 길이 계산
    if (idx == 0) {
        head = insertFront_List(head, value); // 인덱스가 0이면 리스트 맨 앞에 요소를 추가하는 함수 호출
        return head;
    }
    else if (idx == length) {
        head = insertBack_List(head, value); // 인덱스가 리스트 길이와 같으면 리스트의 맨 뒤에 요소를 추가하는 함수 호출
        return head;
    }
    else if (idx > length || idx < 0) {
        printf("Not a valid index!\n"); // 인덱스가 리스트 길이를 초과하면 오류 메시지 출력
        return head;
    }
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode)); // 동적할당을 통해 새로운 노드 생성
    if (new_node == NULL) {
        printf("Failed to allocate memory\n"); // 메모리 할당 실패 시 메시지 출력
        return head;
    }
    new_node->data = value; // 새 노드의 값 할당
    new_node->link = NULL;
    ListNode *pre = head;
    for (int i = 1; i < idx; i++) {
        pre = pre->link; // 지정된 인덱스의 바로 전 위치까지 이동
    }
    new_node->link = pre->link; // 새 노드가 이전 노드가 가리키는 노드를 가리킴
    pre->link = new_node; // 새 노드의 이전 노드는 다시 새 노드를 가리킴으로써 노드 추가
    return head;
}

/* 리스트의 첫번째 노드 삭제 */
ListNode *deleteFront_List(ListNode *head) {
    if (head == NULL) {
        printf("List is already empty!\n"); // 리스트가 비어 있으면 메시지 출력
        return NULL;
    }
    ListNode *removed = head; // 노드 삭제를 위한 임시 노드 포인터
    head = head->link; // 헤드를 다음 노드로 이동
    free(removed); // 기존 헤드 노드 메모리 해제
    return head;
}

/* 리스트의 마지막 노드 삭제 */
ListNode *deleteBack_List(ListNode *head) {
    if (head == NULL) {
        printf("List is already empty!\n"); // 리스트가 비어 있으면 메시지 출력
        return NULL;
    }
    if (head->link == NULL) {
        free(head); // 리스트에 노드가 하나만 있으면 그 노드 해제
        return NULL;
    }
    ListNode *pre = head; // 삭제하고자 하는 노드의 이전 노드를 가리키기 위한 포인터
    for (ListNode *t = head; t->link != NULL; t = t->link) {
        pre = t;    // 마지막 노드의 이전 노드까지 이동
    }
    ListNode *removed = pre->link; // 노드 삭제를 위한 임시 노드 포인터
    pre->link = NULL; // 마지막 노드를 제거
    free(removed); // 메모리 해제
    return head;
}

/* 특정 인덱스의 노드 삭제 */
ListNode *deleteSpecific_List(ListNode *head, int idx) {
    if (head == NULL || idx < 0) {
        printf("Not a valid index!\n"); // 리스트가 비어 있거나 인덱스가 음수면 오류 메시지 출력
        return head;
    }
    if (idx == 0) return deleteFront_List(head); // 첫번째 노드를 삭제하는 경우 첫번째 노드를 삭제하는 함수 호출
    ListNode *pre = head;
    for (int i = 0; i < idx - 1; i++) {
        if (pre->link == NULL) {
            printf("Not a valid index!\n"); // 인덱스가 리스트 길이를 초과하면 오류 메시지 출력
            return head;
        }
        pre = pre->link; // 지정된 인덱스의 이전 노드까지 이동
    }
    ListNode *removed = pre->link; // 삭제할 노드
    if (removed == NULL) {
        printf("No node exists in this %d index\n", idx); // 인덱스에 해당하는 노드가 없으면 오류 메시지 출력
        return head;
    }
    pre->link = removed->link; // 노드 연결 해제
    free(removed); // 메모리 해제
    return head;
}

/* 리스트의 헤드 데이터 접근 */
void access_head(ListNode *head) {
    if (head == NULL) {
        printf("head is NULL\n");
        exit(1);
    }
    else printf("%d\n", head->data); // 헤드 노드의 데이터 반환
}

/* 리스트의 특정 데이터 접근 */
void access_node(ListNode *head, int idx) {
    if (head == NULL) {
        printf("head is NULL\n");
        exit(1);
    }
    ListNode* t = head;
    /* 인덱스 값만큼 반복하여 특정 인덱스의 주소를 얻어옴 */
    for (int i = 0; i < idx; i++) {
        t = t->link;
        if (t->link == NULL) {
            printf("Not a valid index!\n");
            return;
        }
    }
    printf("%d\n", t->data);
}
/* 리스트 출력 */
void print_List(ListNode *head) {
    for (ListNode *t = head; t != NULL; t = t->link) {
        printf("%d->", t->data); // 모든 노드의 데이터를 출력
    }
    printf("NULL\n");
}

/* 리스트의 모든 노드 메모리 해제 */
void freeList(ListNode *head) {
    while (head != NULL) {
        ListNode *temp = head;
        head = head->link;
        free(temp);
    }
}

/* 단일 연결 리스트 구현 완료 */
void test_Array() {
    DynamicArray *DyArray = initialize_Array(5); // 다섯칸짜리 배열 생성

    /* 동적 배열 요소 삽입 테스트 */
    insertBack_Array(DyArray, 10); // 배열 맨 뒤에 10 추가, 현재 배열 [10, 0, 0, 0, 0] (0은 비어있는 칸을 의미)
    insertBack_Array(DyArray, 20); // 배열 맨 뒤에 20 추가, 현재 배열 [10, 20, 0, 0, 0]
    insertBack_Array(DyArray, 30); // 배열 맨 뒤에 30 추가, 현재 배열 [10, 20, 30, 0, 0]
    insertBack_Array(DyArray, 40); // 배열 맨 뒤에 40 추가, 현재 배열 [10, 20, 30, 40, 0]
    printf("요소 삽입 결과: ");
    print_Array(DyArray);

    insertFront_Array(DyArray, 5); // 배열 맨 앞에 5 추가, 현재 배열 [5, 10, 20, 30, 40]

    printf("요소 삽입 결과: ");
    print_Array(DyArray);

    insertSpecific_Array(DyArray, 8, 1); // 배열 [1]번째에 8 추가, 배열의 크기가 넘치므로 배열 크기 재할당
    printf("요소 삽입 결과: ");
    print_Array(DyArray);

    printf("\n");

    /* 동적 배열 요소 삭제 테스트 */
    
    deleteBack_Array(DyArray); // 배열 맨 뒤의 값 삭제

    printf("요소 삭제 결과: ");
    print_Array(DyArray);

    deleteFront_Array(DyArray); // 배열 맨 앞의 값 삭제

    printf("요소 삭제 결과: ");
    print_Array(DyArray);

    deleteSpecific_Array(DyArray, 2); // [2]번째 요소 삭제
    printf("요소 삭제 결과: ");
    print_Array(DyArray);

    free(DyArray);
}
void test_List() {
    ListNode *head = initialize_List(); // 비어있는 초기 리스트 생성
    
    head = insertFront_List(head, 10); // 리스트 앞에 10 삽입, 현재 리스트: 10->NULL
    head = insertFront_List(head, 20); // 리스트 앞에 20 삽입, 현재 리스트: 20->10->NULL
    head = insertFront_List(head, 30); // 리스트 앞에 30 삽입, 현재 리스트: 30->20->10->NULL

    head = insertBack_List(head, 100); // 리스트 뒤에 100 삽입, 현재 리스트: 30->20->10->100->NULL
    head = insertBack_List(head, 50);  // 리스트 뒤에 50 삽입, 현재 리스트: 30->20->10->100->50->NULL

    head = insertSpecific_List(head, 15, 1); // 리스트의 1번 인덱스에 15 삽입, 현재 리스트: 30->15->20->10->100->50->NULL
    head = insertSpecific_List(head, 25, 2); // 리스트의 2번 인덱스에 25 삽입, 현재 리스트: 30->15->25->20->10->100->50->NULL
    head = insertSpecific_List(head, 35, 3); // 리스트의 3번 인덱스에 35 삽입, 현재 리스트: 30->15->25->35->20->10->100->50->NULL

    print_List(head);
    printf("%d\n", ListLength(head)); // 현재 리스트 길이 출력

    head = deleteSpecific_List(head, 5); // 5번 인덱스 노드 삭제, 현재 리스트: 30->15->25->35->20->100->50->NULL

    print_List(head);
    printf("%d\n", ListLength(head)); // 변경된 리스트 길이 출력

    head = deleteFront_List(head); // 리스트의 첫번째 노드 삭제, 현재 리스트: 15->25->35->20->100->50->NULL

    head = deleteBack_List(head); // 리스트의 마지막 노드 삭제, 현재 리스트: 15->25->35->20->100->NULL

    print_List(head); // 최종 리스트 상태 출력

    access_head(head); // 리스트의 헤드 데이터 출력
    access_node(head, 3); // 리스트의 3번째 요소 출력

    free(head);
}
void compare_time_complexity() {
    DynamicArray *DyArray = initialize_Array(0);
    ListNode *head = initialize_List();

    clock_t start, end = 0; // 시간 측정을 위해 사용되는 변수
    double used_time = 0; // 사용된 시간을 저장하는 변수

    int data_size = 0;
    printf("삽입 함수 시간 복잡도 비교 시작\n");

    printf("자료구조에 입력할 데이터 양을 입력하세요. "); // 사용자로부터 수를 입력 받음
    scanf("%d", &data_size);
    
    /* 동적 배열의 삽입 시간 복잡도 측정 시작 */
    start = clock();
    for (int i = 0; i < data_size; i++) {
        insertFront_Array(DyArray, i); // 맨 앞에 요소를 삽입하는 경우
    }
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터를 동적 배열의 front 삽입에 걸린 시간: %f seconds\n", data_size, used_time);
    free(DyArray);
    
    DyArray = initialize_Array(0);
    start = clock();
    for (int i = 0; i < data_size; i++) {
        insertBack_Array(DyArray, i); // 맨 뒤에 요소를 삽입하는 경우
    }
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터를 동적 배열의 end 삽입에 걸린 시간: %f seconds\n", data_size, used_time);
    free(DyArray);
    
    DyArray = initialize_Array(0);
    start = clock();
    for (int i = 0; i < data_size; i++) {
        int idx = DyArray->size / 2; // 시간 차이를 확실히 보여주기 위해 배열 중간 즈음에 요소를 삽입
        insertSpecific_Array(DyArray, 1, idx);
    }
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC; // 시작 시간을 종료 시간에서 빼어 걸린 시간 체크
    printf("%d개의 데이터를 동적 배열의 특정 인덱스 삽입에 걸린 시간: %f seconds\n", data_size, used_time);
    
    /* 동적 배열의 삽입 시간 복잡도 측정 완료 */
    printf("\n");

    /* 단순 연결 리스트의 삽입 시간 복잡도 측정 시작 */
    start = clock();
    for (int i = 0; i < data_size; i++) {
        head = insertFront_List(head, i); // 맨 앞에 요소를 삽입하는 경우
    }
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터를 단순 연결 리스트의 front 삽입에 걸린 시간: %f seconds\n", data_size, used_time);
    freeList(head);
    
    head = initialize_List();
    start = clock();
    for (int i = 0; i < data_size; i++) {
        head = insertBack_List(head, i); // 맨 뒤에 요소를 삽입하는 경우
    }
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터를 단순 연결 리스트의 end 삽입에 걸린 시간: %f seconds\n", data_size, used_time);
    freeList(head);
    
    head = initialize_List();
    start = clock();
    for (int i = 0; i < data_size; i++) {
        int idx = i / 2; // 시간 차이를 확실히 보여주기 위해 리스트 중간 즈음에 요소를 삽입
        head = insertSpecific_List(head, 1, idx);
    }
    end = clock();
    used_time = ((double) (end - start)) / (CLOCKS_PER_SEC * 2);
    printf("%d개의 데이터를 단순 연결 리스트의 특정 인덱스 삽입에 걸린 시간: %f seconds\n", data_size, used_time);
    /* 단순 연결 리스트의 삽입 시간 복잡도 측정 완료 */
    printf("\n");

    /* 동적 배열의 삭제 시간 복잡도 측정 시작 */
    printf("삭제 함수 시간 복잡도 비교 시작\n");
    start = clock();
    deleteFront_Array(DyArray); // 맨 앞의 요소를 삭제
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 동적 배열의 front 삭제에 걸린 시간: %f seconds\n", data_size, used_time);
    insertFront_Array(DyArray, 1);
    
    start = clock();
    deleteBack_Array(DyArray); // 맨 뒤의 요소를 삭제
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 동적 배열의 end 삭제에 걸린 시간: %f seconds\n", data_size, used_time);
    insertFront_Array(DyArray, 1);
    
    start = clock();
    int idx = DyArray->size / 2;
    deleteSpecific_Array(DyArray, idx); // 배열 중간 즈음의 요소를 삭제
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 동적 배열의 특정 인덱스 삭제에 걸린 시간: %f seconds\n", data_size, used_time);
    insertFront_Array(DyArray, 1);

    /* 동적 배열의 삭제 시간 복잡도 측정 완료 */
    printf("\n");

    /* 단순 연결 리스트의 삭제 시간 복잡도 측정 시작 */
    start = clock();
    head = deleteFront_List(head); // 맨 앞의 요소를 삭제
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 단순 연결 리스트의 front 삭제에 걸린 시간: %f seconds\n", data_size, used_time);
    head = insertFront_List(head, 1);
    
    start = clock();
    head = deleteBack_List(head); // 맨 뒤의 요소를 삭제
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 단순 연결 리스트의 end 삭제에 걸린 시간: %f seconds\n", data_size, used_time);
    head = insertFront_List(head, 1);
    
    idx = ListLength(head) / 2;
    start = clock();
    head = deleteSpecific_List(head, idx); // 리스트 중간 즈음의 요소를 삭제
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 단순 연결 리스트의 특정 인덱스 삭제에 걸린 시간: %f seconds\n", data_size, used_time);
    head = insertFront_List(head, 1);
    
    /* 단순 연결 리스트의 삭제 시간 복잡도 측정 완료 */
    printf("\n");
    printf("접근 함수 시간 복잡도 비교 시작\n");
    /* 동적 배열의 접근 시간 복잡도 측정 시작 */
    start = clock();
    access_Array(DyArray, data_size / 2); // 배열의 중간 즈음에 요소에 접근
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 동적 배열의 특정 요소 접근에 걸린 시간: %f seconds\n", data_size, used_time);
    /* 동적 배열의 접근 시간 복잡도 측정 종료 */
    
    /* 단순 연결 리스트의 접근 시간 복잡도 측정 시작 */
    start = clock();
    access_head(head); // 리스트의 head에 접근
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 단순 연결 리스트의 헤드 노드 접근에 걸린 시간: %f seconds\n", data_size, used_time);

    start = clock();
    access_node(head, data_size / 2); // 리스트의 중간 즈음 노드에 접근
    end = clock();
    used_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d개의 데이터에서 단순 연결 리스트의 특정 요소 접근에 걸린 시간: %f seconds\n", data_size, used_time);
    /* 단순 연결 리스트의 접근 시간 복잡도 측정 종료 */
}

int main() {
    test_Array();
    test_List();
    compare_time_complexity();
    return 0;
}