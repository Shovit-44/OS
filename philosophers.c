#include <stdio.h>
#include <windows.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_id + 1) % NUM_PHILOSOPHERS

HANDLE mutex;                       // Mutex to protect critical sections
HANDLE semaphores[NUM_PHILOSOPHERS]; // Semaphores for each philosopher
int state[NUM_PHILOSOPHERS];         // State array to track each philosopher

void test(int philosopher_id) {
    if (state[philosopher_id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopher_id] = EATING;
        printf("Philosopher %d is EATING\n", philosopher_id + 1);
        ReleaseSemaphore(semaphores[philosopher_id], 1, NULL); // Signal semaphore to eat
    }
}

void take_forks(int philosopher_id) {
    WaitForSingleObject(mutex, INFINITE); // Wait for mutex
    state[philosopher_id] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", philosopher_id + 1);
    test(philosopher_id);                 // Try to acquire forks
    ReleaseMutex(mutex);                  // Release mutex
    WaitForSingleObject(semaphores[philosopher_id], INFINITE); // Wait to eat
}

void put_forks(int philosopher_id) {
    WaitForSingleObject(mutex, INFINITE); // Wait for mutex
    state[philosopher_id] = THINKING;
    printf("Philosopher %d is THINKING\n", philosopher_id + 1);
    test(LEFT);  // Check if the left neighbor can eat
    test(RIGHT); // Check if the right neighbor can eat
    ReleaseMutex(mutex);                  // Release mutex
}

DWORD WINAPI philosopher(LPVOID num) {
    int philosopher_id = *(int*)num;
    while (1) {
        Sleep(1000); // Simulate thinking
        take_forks(philosopher_id);
        Sleep(1000); // Simulate eating
        put_forks(philosopher_id);
    }
    return 0;
}

int main() {
    HANDLE threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    mutex = CreateMutex(NULL, FALSE, NULL); // Create a mutex
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        semaphores[i] = CreateSemaphore(NULL, 0, 1, NULL); // Create a semaphore for each philosopher
        philosopher_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        threads[i] = CreateThread(NULL, 0, philosopher, &philosopher_ids[i], 0, NULL);
    }

    // Wait for all threads to finish (they won't in this infinite loop)
    WaitForMultipleObjects(NUM_PHILOSOPHERS, threads, TRUE, INFINITE);

    // Close handles (will not be reached in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        CloseHandle(threads[i]);
        CloseHandle(semaphores[i]);
    }
    CloseHandle(mutex);

    return 0;
}
