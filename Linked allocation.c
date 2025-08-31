#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a block
struct Block {
    char data[256];       // Data of the block
    struct Block* next;   // Pointer to the next block
};

int main() {
    struct Block* firstBlock = NULL; // Pointer to the first block
    struct Block* lastBlock = NULL;  // Pointer to the last block
    int blockCount = 0;              // Number of blocks
    int blockNumber;
    char data[256];
    char choice;

    printf("Linked Allocation Simulation\n");

    while (1) {
        printf("\nEnter 'W' to write a block, 'R' to read a block, or 'Q' to quit: ");
        scanf(" %c", &choice);

        if (choice == 'Q' || choice == 'q') {
            break;
        } 
        else if (choice == 'W' || choice == 'w') {
            printf("Enter data for the block: ");
            scanf(" %[^\n]", data);

            // Create a new block
            struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
            strcpy(newBlock->data, data);
            newBlock->next = NULL;

            if (blockCount == 0) {
                firstBlock = newBlock;
                lastBlock = newBlock;
            } else {
                lastBlock->next = newBlock;
                lastBlock = newBlock;
            }

            blockCount++;
            printf("Block %d written successfully.\n", blockCount);
        } 
        else if (choice == 'R' || choice == 'r') {
            if (blockCount == 0) {
                printf("No blocks available to read.\n");
                continue;
            }

            printf("Enter the block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);

            if (blockNumber < 1 || blockNumber > blockCount) {
                printf("Invalid block number. The valid range is 1-%d.\n", blockCount);
            } else {
                struct Block* currentBlock = firstBlock;
                for (int i = 1; i < blockNumber; i++) {
                    currentBlock = currentBlock->next;
                }
                printf("Block %d Data: %s\n", blockNumber, currentBlock->data);
            }
        } 
        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    // Free the allocated memory
    struct Block* currentBlock = firstBlock;
    while (currentBlock != NULL) {
        struct Block* nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    printf("Exiting simulation.\n");
    return 0;
}

