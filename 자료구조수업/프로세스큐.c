#include <stdio.h>
#define MAX_PROCESS 100
// Structure to represent a process
typedef struct Process {
    int priority;   // 우선 순위를 저장
    int is_target;  // 타겟으로 하는 수인지 아닌지를 저장 (boolean)
} Process;
// Function to simulate process management
int process_runs(int priorities[], int n, int location) {
    Process queue[MAX_PROCESS];
    int count = 0;
    // Initailize the queue
    for (int i = 0; i < n; i++) {
        queue[i].priority = priorities[i];  // 우선 순위 저장
        queue[i].is_target = (i == location);   // i == location을 만족하면 1을 저장해줌
    }
    // Loop until the queue is empty
    while (n > 0) {
        // Pop the first process in the queue
        Process current = queue[0]; // 맨 앞의 수와 타겟 여부를 저장
        for (int i = 0; i < n - 1; i++) {
            queue[i] = queue[i + 1];    // pop을 했기 때문에 한 칸씩 땡겨주기
        }
        n--;    // pop을 했기 때문에 사이즈 하나 줄여줘야함
        // Check if there's a higher priority process waiting
        int higher_priority_wating = 0; // Using like boolean, 우선순위가 더 큰 수가 있는지를 판별
        for (int i = 0; i < n; i++) {
            if (queue[i].priority > current.priority) {
                higher_priority_wating = 1;
                break;
            }
        }
        // Check for higher priority
        if (higher_priority_wating) {
            queue[n] = current;
            n++;
        }
        // Otherwise, process runs terminates
        else {
            count++;
            if (current.is_target) return count;
        }
    }
    return -1; // Error: shouldn't reach here
}
int main() {
    // Test cases
    int priorities1[] = {2, 1, 3, 2};
    int location1 = 2;
    int n1 = sizeof(priorities1) / sizeof(priorities1[0]);
    printf("%d\n", process_runs(priorities1, n1, location1)); // Output: 1
    
    int priorities2[] = {1, 1, 9, 1, 1, 1};
    int location2 = 0;
    int n2 = sizeof(priorities2) / sizeof(priorities2[0]);
    printf("%d\n", process_runs(priorities2, n2, location2)); // Output: 5

    return 0; 
}