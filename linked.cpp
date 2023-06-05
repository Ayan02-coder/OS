 #include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct File {
    int start_block;
    int length;
};

void allocate_blocks(struct File files[], int num_files, int blocks[], int num_blocks)
{
    for (int i = 0; i < num_files; i++) {
        int start = -1;
        int count = 0;

        for (int j = 0; j < num_blocks; j++) {
            if (blocks[j] == 0) {
                if (count == 0)
                    start = j;
                count++;

                if (count == files[i].length)
                    break;
            }
        }

        if (count == files[i].length) {
            files[i].start_block = start;

            for (int j = start; j < start + count; j++) {
                blocks[j] = 1;
            }
        } else {
            printf("Insufficient free blocks to allocate file %d\n", i + 1);
        }
    }
}

void print_allocation(struct File files[], int num_files)
{
    printf("File\tStart Block\tLength\n");
    for (int i = 0; i < num_files; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, files[i].start_block, files[i].length);
    }
}

int main()
{
    int num_files, num_blocks;
    struct File files[MAX_BLOCKS];
    int blocks[MAX_BLOCKS];

    printf("Enter the number of files: ");
    scanf("%d", &num_files);

    printf("Enter the number of blocks: ");
    scanf("%d", &num_blocks);

    for (int i = 0; i < num_blocks; i++) {
        blocks[i] = 0;
    }

    for (int i = 0; i < num_files; i++) {
        printf("Enter the length of file %d: ", i + 1);
        scanf("%d", &files[i].length);
        files[i].start_block = -1;
    }

    allocate_blocks(files, num_files, blocks, num_blocks);

    printf("\nFile allocation:\n");
    print_allocation(files, num_files);

    return 0;
}
