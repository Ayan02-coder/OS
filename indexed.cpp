#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100

struct File {
    int indexBlock;
    int blockCount;
};

void initializeDisk(bool disk[], int size)
{
    for (int i = 0; i < size; i++)
        disk[i] = false;
}

void printDiskStatus(bool disk[], int size)
{
    printf("Disk Status:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: %s\n", i, disk[i] ? "Allocated" : "Free");
    }
    printf("\n");
}

void allocateFile(bool disk[], int indexBlock, int blockCount)
{
    if (disk[indexBlock]) {
        printf("Error: Index block %d is already allocated.\n\n", indexBlock);
        return;
    }

    int allocatedBlocks = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!disk[i]) {
            disk[i] = true;
            allocatedBlocks++;
            if (allocatedBlocks == blockCount)
                break;
        }
    }

    if (allocatedBlocks < blockCount) {
        printf("Error: Not enough consecutive free blocks available for allocation.\n\n");
        return;
    }

    disk[indexBlock] = true;

    printf("File allocated successfully!\n");
    printf("Index block: %d\n", indexBlock);
    printf("Blocks allocated: %d\n\n", blockCount);
}

void deallocateFile(bool disk[], int indexBlock)
{
    if (!disk[indexBlock]) {
        printf("Error: Index block %d is not allocated.\n\n", indexBlock);
        return;
    }

    int blockCount = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i]) {
            disk[i] = false;
            blockCount++;
        }
        if (blockCount == indexBlock)
            break;
    }

    disk[indexBlock] = false;

    printf("File deallocated successfully!\n");
    printf("Index block: %d\n", indexBlock);
    printf("Blocks deallocated: %d\n\n", blockCount);
}

int main()
{
    bool disk[MAX_BLOCKS];
    initializeDisk(disk, MAX_BLOCKS);

    int choice;
    do {
        printf("Indexed File Allocation\n");
        printf("1. Print Disk Status\n");
        printf("2. Allocate File\n");
        printf("3. Deallocate File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printDiskStatus(disk, MAX_BLOCKS);
                break;
            case 2: {
                int indexBlock, blockCount;
                printf("Enter the index block: ");
                scanf("%d", &indexBlock);
                printf("Enter the number of blocks to allocate: ");
                scanf("%d", &blockCount);
                allocateFile(disk, indexBlock, blockCount);
                break;
            }
            case 3: {
                int indexBlock;
                printf("Enter the index block to deallocate: ");
                scanf("%d", &indexBlock);
                deallocateFile(disk, indexBlock);
                break;
            }
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
