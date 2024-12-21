#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void print_frames(int frames[], int num_frames, int reference_bits[]) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] != -1)
            printf("%d(%d) ", frames[i], reference_bits[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int page_count, num_frames;
    int page_faults = 0;
    int reference_bits[MAX_FRAMES] = {0};
    int front = 0, rear = 0;

    // Initialize frames
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    // Get input from user
    printf("Enter the number of pages: ");
    scanf("%d", &page_count);
    printf("Enter the page reference string (space-separated): ");
    for (int i = 0; i < page_count; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    // Simulate Second Chance Page Replacement Algorithm
    printf("\nPage Reference String: ");
    for (int i = 0; i < page_count; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("\nPage Replacement Process:\n");
    for (int i = 0; i < page_count; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                reference_bits[j] = 1;
                found = 1;
                break;
            }
        }

        if (!found) {
            while (reference_bits[front] == 1) {
                reference_bits[front] = 0;
                front = (front + 1) % num_frames;
            }
            frames[front] = page;
            reference_bits[front] = 1;
            front = (front + 1) % num_frames;
            page_faults++;
            printf("Page %d causes a page fault.\n", page);
            print_frames(frames, num_frames, reference_bits);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
