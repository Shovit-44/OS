#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void print_frames(int frames[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int find_page_index(int pages[], int page_count, int frames[], int num_frames, int current_index) {
    int index = -1, farthest = current_index;
    for (int i = 0; i < num_frames; i++) {
        int j;
        for (j = current_index; j < page_count; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == page_count) // Page not found in future references
            return i;
    }
    return (index == -1) ? 0 : index;
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int page_count, num_frames;
    int page_faults = 0;

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

    // Simulate Optimal Page Replacement Algorithm
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
                found = 1;
                break;
            }
        }
        if (!found) {
            int index = find_page_index(pages, page_count, frames, num_frames, i + 1);
            frames[index] = page;
            page_faults++;
            printf("Page %d causes a page fault.\n", page);
            print_frames(frames, num_frames);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}