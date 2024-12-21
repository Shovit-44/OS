#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

typedef struct {
    int block_start;
    int block_end;
    int size;
} Inode;

void InodeAllocation(int file_sizes[], int num_files, int disk_size) {
    int i, j;
    int disk[MAX_BLOCKS];
    Inode inodes[MAX_FILES];

    for (i = 0; i < disk_size; i++) {
        disk[i] = -1;
    }

    printf("Inode File Allocation:\n");

    for (i = 0; i < num_files; i++) {
        int size = file_sizes[i];
        int start_block = -1;
        int current_block = -1;

        for (j = 0; j < disk_size; j++) {
            if (disk[j] == -1) {
                if (start_block == -1) {
                    start_block = j;
                }
                current_block = j;
                size--;
                if (size == 0) {
                    break;
                }
            } else {
                start_block = -1;
                size = file_sizes[i];
                current_block = -1;
            }
        }

        if (size > 0) {
            printf("File %d could not be allocated\n", i + 1);
            continue;
        }

        for (j = start_block; j <= current_block; j++) {
            disk[j] = i + 1;
        }
        inodes[i].block_start = start_block;
        inodes[i].block_end = current_block;
        inodes[i].size = file_sizes[i];
        printf("File %d allocated from block %d to block %d\n", i + 1, start_block, current_block);
    }

    printf("\nDisk allocation:\n");
    for (i = 0; i < disk_size; i++) {
        printf("%d ", disk[i]);
    }
    printf("\n");

    printf("Inode table:\n");
    for (i = 0; i < num_files; i++) {
        printf("File %d: Start Block %d, End Block %d, Size %d\n", i + 1, inodes[i].block_start, inodes[i].block_end, inodes[i].size);
    }
}

int main() {
    int file_sizes[] = {5, 10, 20}; // Example file sizes
    int num_files = 3;
    int disk_size = 50; // Example disk size

    InodeAllocation(file_sizes, num_files, disk_size);
    return 0;
}
