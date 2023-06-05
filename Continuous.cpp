 #include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100

void allocate_file(int start_block, int num_blocks, int blocks[])
{
    printf("Allocating file starting from block %d\n", start_block);
    for (int i = 0; i < num_blocks; i++) {
        blocks[start_block + i] = 1;
    }
}

void deallocate_file(int start_block, int num_blocks, int blocks[])
{
    printf("Deallocating file starting from block %d\n", start_block);
    for (int i = 0; i < num_blocks; i++) {
        blocks[start_block + i] = 0;
    }
}

void print_blocks(int blocks[], int num_blocks)
{
    for (int i = 0; i < num_blocks; i++) {
        printf("%d ", blocks[i]);
    }
    printf("\n");
}

int main()
{
    int blocks[MAX_BLOCKS] = {0};
    int num_blocks;

    printf("Enter the number of blocks: ");
    scanf("%d", &num_blocks);

    while (true) {
        int choice;
        printf("\n1. Allocate file\n");
        printf("2. Deallocate file\n");
        printf("3. Print blocks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int start_block, num_file_blocks;
            printf("Enter the starting block and number of blocks for the file: ");
            scanf("%d %d", &start_block, &num_file_blocks);

            if (start_block < 0 || start_block >= num_blocks) {
                printf("Invalid starting block.\n");
                continue;
            }

            if (start_block + num_file_blocks > num_blocks) {
                printf("File size exceeds available blocks.\n");
                continue;
            }

            bool is_allocated = true;
            for (int i = 0; i < num_file_blocks; i++) {
                if (blocks[start_block + i] == 1) {
                    printf("Block %d is already allocated.\n", start_block + i);
                    is_allocated = false;
                    break;
                }
            }

            if (is_allocated) {
                allocate_file(start_block, num_file_blocks, blocks);
                printf("File allocated successfully.\n");
            }
        } else if (choice == 2) {
            int start_block, num_file_blocks;
            printf("Enter the starting block and number of blocks for the file to deallocate: ");
            scanf("%d %d", &start_block, &num_file_blocks);

            if (start_block < 0 || start_block >= num_blocks) {
                printf("Invalid starting block.\n");
                continue;
            }

            if (start_block + num_file_blocks > num_blocks) {
                printf("Invalid number of blocks.\n");
                continue;
            }

            deallocate_file(start_block, num_file_blocks, blocks);
            printf("File deallocated successfully.\n");
        } else if (choice == 3) {
            print_blocks(blocks, num_blocks);
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
