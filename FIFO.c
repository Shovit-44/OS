#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int front = 0, rear = 0, pageFaults = 0;
    int isFull = 0;

    // Initialize frames to -1 (indicating empty frames)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    printf("Page Frames at each step:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not in the frames, replace the oldest one
        if (!found) {
            frames[rear] = page;
            rear = (rear + 1) % capacity;
            if (rear == front) {
                isFull = 1;
                front = (front + 1) % capacity; // Move front if rear catches up
            }
            pageFaults++;
        }

        // Print current state of frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1) {
                printf(" - ");
            } else {
                printf("%2d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string (space-separated page numbers): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    fifoPageReplacement(pages, n, capacity);

    return 0;
}
