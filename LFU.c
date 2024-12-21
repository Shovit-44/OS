#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void print_frames(int frames[], int num_frames, int counts[]) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] != -1)
            printf("%d(%d) ", frames[i], counts[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int find_page_index(int page, int frames[], int num_frames, int counts[], int page_count) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            counts[i]++;
            return -1; // Page found, no replacement needed
        }
    }

    int min_count = counts[0];
    int index = 0;
    for (int i = 1; i < num_frames; i++) {
        if (counts[i] < min_count) {
            min_count = counts[i];
            index = i;
        }
    }
    
    return index; // Page index to replace
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int page_count, num_frames;
    int page_faults = 0;
    int counts[MAX_FRAMES] = {0};

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

    // Simulate LFU Page Replacement Algorithm
    printf("\nPage Reference String: ");
    for (int i = 0; i < page_count; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("\nPage Replacement Process:\n");
    for (int i = 0; i < page_count; i++) {
        int page = pages[i];
        int index = find_page_index(page, frames, num_frames, counts, page_count);
        if (index != -1) {
            frames[index] = page;
            counts[index] = 1;
            page_faults++;
            printf("Page %d causes a page fault.\n", page);
            print_frames(frames, num_frames, counts);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}