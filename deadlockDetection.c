#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int numProcesses, int numResources) {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool deadlockDetection(int processes[], int available[], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int numProcesses, int numResources) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allocation, numProcesses, numResources);

    bool finished[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    int deadlocked[MAX_PROCESSES];
    int deadlockCount = 0;

    while (true) {
        bool found = false;

        for (int p = 0; p < numProcesses; p++) {
            if (!finished[p]) {
                int j;
                for (j = 0; j < numResources; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                if (j == numResources) {
                    for (int k = 0; k < numResources; k++) {
                        work[k] += allocation[p][k];
                    }
                    finished[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    for (int i = 0; i < numProcesses; i++) {
        if (!finished[i]) {
            deadlocked[deadlockCount++] = i;
        }
    }

    if (deadlockCount > 0) {
        printf("Deadlock detected. Deadlocked processes are: ");
        for (int i = 0; i < deadlockCount; i++) {
            printf("%d ", deadlocked[i]);
        }
        printf("\n");
        return true;
    } else {
        printf("No deadlock detected.\n");
        return false;
    }
}

int main() {
    int numProcesses, numResources;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    int processes[MAX_PROCESSES];
    for (int i = 0; i < numProcesses; i++) {
        processes[i] = i;
    }

    int available[MAX_RESOURCES];
    printf("Enter the available resources: ");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    int max[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter the maximum demand of each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    deadlockDetection(processes, available, max, allocation, numProcesses, numResources);

    return 0;
}
