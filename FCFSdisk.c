#include <stdio.h>
#include <stdlib.h>

void FCFS(int requests[], int num_requests, int initial_head) {
    int i;
    int total_head_movement = 0;
    int current_head = initial_head;

    printf("FCFS Disk Scheduling:\n");

    for (i = 0; i < num_requests; i++) {
        printf("Move from %d to %d\n", current_head, requests[i]);
        total_head_movement += abs(current_head - requests[i]);
        current_head = requests[i];
    }

    printf("Total Head Movement: %d\n", total_head_movement);
}

int main() {
    int num_requests;
    int initial_head;

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    int requests[num_requests];
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("Enter the disk requests: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    FCFS(requests, num_requests, initial_head);
    return 0;
}
