#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

void ContiguousAllocation(int file_sizes[], int num_files, int disk_size) {
    int i, j;
    int disk[MAX_BLOCKS];
    int file_start[MAX_FILES];
    
    // Initialize disk
    for (i = 0; i < disk_size; i++) {
        disk[i] = -1;
    }

    printf("Contiguous File Allocation:\n");

    for (i = 0; i < num_files; i++) {
        int size = file_sizes[i];
        int start_block = -1;

        for (j = 0; j < disk_size; j++) {
            if (disk[j] == -1) {
                if (start_block == -1) {
                    start_block = j;
                }
                size--;
                if (size == 0) {
                    break;
                }
            } else {
                start_block = -1;
                size = file_sizes[i];
            }
        }

        if (size > 0) {
            printf("File %d could not be allocated\n", i + 1);
            continue;
        }

        for (j = start_block; j < start_block + file_sizes[i]; j++) {
            disk[j] = i + 1;
        }
        file_start[i] = start_block;
        printf("File %d allocated from block %d to block %d\n", i + 1, start_block, start_block + file_sizes[i] - 1);
    }

    printf("\nDisk allocation:\n");
    for (i = 0; i < disk_size; i++) {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

int main() {
    int file_sizes[] = {5, 10, 20}; // Example file sizes
    int num_files = 3;
    int disk_size = 50; // Example disk size

    ContiguousAllocation(file_sizes, num_files, disk_size);
    return 0;
}
