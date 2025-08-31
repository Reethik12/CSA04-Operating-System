#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a block
struct Block {
    int blockNumber;
    char data[256]; // Adjust the size as needed for your blocks
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;
    long indexBlock[100] = {0}; // Index array storing file positions, use long for ftell

    // Open or create a file in write mode (for writing blocks)
    file = fopen("indexed_file.txt", "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write blocks and update the index block
    printf("Enter blocks (Enter '0' as block number to exit):\n");
    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);
        if (block.blockNumber == 0) {
            break;
        }

        printf("Data: ");
        scanf(" %[^\n]", block.data);

        // Store current position in indexBlock
        indexBlock[block.blockNumber] = ftell(file);

        // Write the block to the file
        fwrite(&block, sizeof(struct Block), 1, file);
    }
    fclose(file);

    // Reopen the file in read mode (for reading blocks)
    file = fopen("indexed_file.txt", "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read a specific block from the file
    while (1) {
        printf("Enter the block number to read (0 to exit): ");
        scanf("%d", &blockNumber);
        if (blockNumber == 0) {
            break;
        }

        if (indexBlock[blockNumber] == 0) {
            printf("Block not found.\n");
        } else {
            // Seek to the data block using the index block
            fseek(file, indexBlock[blockNumber], SEEK_SET);
            fread(&block, sizeof(struct Block), 1, file);
            printf("Block Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file);
    return 0;
}

