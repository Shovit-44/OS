  #include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n;
    struct process processes[MAX_PROCESSES];
    bool completed[MAX_PROCESSES] = {false};
    int current_time = 0;
    int shortest_index;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
	
	int i;
    for ( i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i+1;
        processes[i].remaining_time = processes[i].burst_time;
    }  

    printf("\n");

    int completed_count = 0;
    while (completed_count < n) {
        shortest_index = -1;
        int min_remaining_time = 10000;

        for ( i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                shortest_index = i;
            }
        }

        if (shortest_index != -1) {
            processes[shortest_index].remaining_time--;
            if (processes[shortest_index].remaining_time == 0) {
                completed[shortest_index] = true;
                completed_count++;
                processes[shortest_index].turnaround_time = current_time + 1 - processes[shortest_index].arrival_time;
                processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
            }
        }

        current_time++;
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for ( i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    float avg_waiting_time = (float) total_waiting_time / n;
    float avg_turnaround_time = (float) total_turnaround_time / n;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
