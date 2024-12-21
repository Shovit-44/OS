#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 30

typedef struct {
    char bitmap[(MAX_BLOCKS + 7) / 8]; 
} FileSystem;

void initializeFileSystem(FileSystem *fs) {
    memset(fs->bitmap, 0, sizeof(fs->bitmap)); 
}

void allocateBlocks(FileSystem *fs, int num_blocks, int allocated_blocks[]) {
    int i, count = 0;
    for (i = 0; i < MAX_BLOCKS && count < num_blocks; i++) {
        if ((fs->bitmap[i / 8] & (1 << (i % 8))) == 0) {
            // Block is free
            fs->bitmap[i / 8] |= (1 << (i % 8)); 
            allocated_blocks[count++] = i;
        }
    }
    if (count < num_blocks) {
        printf("Not enough free blocks available.\n");
    }
}

void deallocateBlocks(FileSystem *fs, int num_blocks, int blocks[]) {
	int i;
    for ( i = 0; i < num_blocks; i++) {
        int block = blocks[i];
        fs->bitmap[block / 8] &= ~(1 << (block % 8)); 
    }
}

void printBitmap(FileSystem *fs) {
	int i;
    printf("Bitmap: ");
    for ( i = 0; i < MAX_BLOCKS; i++) {
        if ((fs->bitmap[i / 8] & (1 << (i % 8))) == 0) {
            printf("0 ");
        } else {
            printf("1 ");
        }
    }
    printf("\n");
}

int main() {
    FileSystem fs;
    initializeFileSystem(&fs);

    int allocated_blocks[MAX_BLOCKS];
    int num_blocks_to_allocate = 7;
    int i;

    allocateBlocks(&fs, num_blocks_to_allocate, allocated_blocks);
    printf("Allocated blocks: ");
    for ( i = 0; i < num_blocks_to_allocate; i++) {
        printf("%d ", allocated_blocks[i]);
    }
    printf("\n");

    printBitmap(&fs);

    int num_blocks_to_deallocate = 2;
    int blocks_to_deallocate[num_blocks_to_deallocate];

    
    for ( i = 0; i < num_blocks_to_deallocate; i++) {
        blocks_to_deallocate[i] = allocated_blocks[i];
    }

    deallocateBlocks(&fs, num_blocks_to_deallocate, blocks_to_deallocate);
    printf("Deallocated blocks: ");
    for ( i = 0; i < num_blocks_to_deallocate; i++) {
        printf("%d ", blocks_to_deallocate[i]);
    }
    printf("\n");

    printBitmap(&fs);

    return 0;
}
