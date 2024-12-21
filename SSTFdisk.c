#include <stdio.h>
#include <stdlib.h>

void SSTF(int requests[], int num_requests, int initial_head) {
    int i, j, min_dist, total_head_movement = 0;
    int visited[num_requests];
    int current_head = initial_head;
    int num_visited = 0;

    for (i = 0; i < num_requests; i++) {
        visited[i] = 0;
    }

    printf("SSTF Disk Scheduling:\n");

    while (num_visited < num_requests) {
        min_dist = 10000; 
        int closest = -1;

        for (i = 0; i < num_requests; i++) {
            if (!visited[i] && abs(requests[i] - current_head) < min_dist) {
                min_dist = abs(requests[i] - current_head);
                closest = i;
            }
        }

        if (closest != -1) {
            printf("Move from %d to %d\n", current_head, requests[closest]);
            total_head_movement += min_dist;
            current_head = requests[closest];
            visited[closest] = 1;
            num_visited++;
        }
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

    SSTF(requests, num_requests, initial_head);
    return 0;
}
