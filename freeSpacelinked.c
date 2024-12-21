#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 30

typedef struct Node {
    int block_number;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} FileSystem;

void initializeFileSystem(FileSystem *fs) {
    fs->head = NULL;
    int i;
    for ( i = MAX_BLOCKS - 1; i >= 0; i--) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->block_number = i;
        new_node->next = fs->head;
        fs->head = new_node;
    }
}

int allocateBlock(FileSystem *fs) {
    if (fs->head == NULL) {
        printf("No free blocks available.\n");
        return -1;
    }
    Node *allocated_node = fs->head;
    int block_number = allocated_node->block_number;
    fs->head = allocated_node->next;
    free(allocated_node);
    return block_number;
}

void deallocateBlock(FileSystem *fs, int block_number) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->block_number = block_number;
    new_node->next = fs->head;
    fs->head = new_node;
}

void printFreeBlocks(FileSystem *fs) {
    Node *current = fs->head;
    printf("Free blocks: ");
    while (current != NULL) {
        printf("%d ", current->block_number);
        current = current->next;
    }
    printf("\n");
}

int main() {
    FileSystem fs;
    initializeFileSystem(&fs);

    printf("Initial free blocks:\n");
    printFreeBlocks(&fs);

    int allocated_blocks[7];
    printf("Allocating 7 blocks:\n");
    int i;
    for ( i = 0; i < 7; i++) {
        allocated_blocks[i] = allocateBlock(&fs);
        printf("Allocated block: %d\n", allocated_blocks[i]);
    }

    printf("Free blocks after allocation:\n");
    printFreeBlocks(&fs);

    printf("Deallocating 3 blocks:\n");
    deallocateBlock(&fs, allocated_blocks[0]);
    deallocateBlock(&fs, allocated_blocks[1]);
    deallocateBlock(&fs, allocated_blocks[2]);

    printf("Free blocks after deallocation:\n");
    printFreeBlocks(&fs);

    return 0;
}
