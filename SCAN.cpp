 #include <stdio.h>
#include <stdlib.h>

#define DIRECTION_LEFT -1
#define DIRECTION_RIGHT 1

void scan_disk(int disk[], int disk_size, int head, int direction)
{
    int total_seek_time = 0;
    int current_track = head;
    int i, j;

    // Sort the disk array in ascending order
    for (i = 0; i < disk_size - 1; i++) {
        for (j = 0; j < disk_size - i - 1; j++) {
            if (disk[j] > disk[j + 1]) {
                int temp = disk[j];
                disk[j] = disk[j + 1];
                disk[j + 1] = temp;
            }
        }
    }

    // Find the position of the head in the sorted disk array
    int head_index = -1;
    for (i = 0; i < disk_size; i++) {
        if (disk[i] == head) {
            head_index = i;
            break;
        }
    }

    printf("Sequence of disk access:\n");

    if (direction == DIRECTION_LEFT) {
        // Process tracks to the left of the head
        for (i = head_index; i >= 0; i--) {
            printf("%d ", disk[i]);
            total_seek_time += abs(current_track - disk[i]);
            current_track = disk[i];
        }

        // Go to track 0
        printf("0 ");
        total_seek_time += current_track;
        current_track = 0;

        // Process tracks to the right of the head
        for (i = head_index + 1; i < disk_size; i++) {
            printf("%d ", disk[i]);
            total_seek_time += abs(current_track - disk[i]);
            current_track = disk[i];
        }
    } else if (direction == DIRECTION_RIGHT) {
        // Process tracks to the right of the head
        for (i = head_index; i < disk_size; i++) {
            printf("%d ", disk[i]);
            total_seek_time += abs(current_track - disk[i]);
            current_track = disk[i];
        }

        // Go to the last track
        printf("%d ", disk[disk_size - 1]);
        total_seek_time += abs(current_track - disk[disk_size - 1]);
        current_track = disk[disk_size - 1];

        // Process tracks to the left of the head
        for (i = head_index - 1; i >= 0; i--) {
            printf("%d ", disk[i]);
            total_seek_time += abs(current_track - disk[i]);
            current_track = disk[i];
        }
    }

    printf("\n");
    printf("Total seek time: %d\n", total_seek_time);
}

int main()
{
    int disk_size, head, direction;

    printf("Enter the size of the disk: ");
    scanf("%d", &disk_size);

    int *disk = (int *)malloc(disk_size * sizeof(int));

    printf("Enter the track positions (one per line):\n");
    for (int i = 0; i < disk_size; i++) {
        scanf("%d", &disk[i]);
    }

    printf("Enter the initial position of the head: ");
    scanf("%d", &head);

    printf("Enter the direction (left = -1, right = 1): ");
    scanf("%d", &direction);

    printf("\n");

    scan_disk(disk, disk_size, head, direction);

    free(disk);

    return 0;
}
