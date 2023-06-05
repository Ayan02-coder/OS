#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACKS 100

void cscan(int disk[], int n, int head, int direction)
{
    int total_distance = 0;
    int current_track = head;
    int next_track;
    int i;

    printf("C-SCAN Disk Scheduling Algorithm\n");

    // Sort the disk tracks in ascending order
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (disk[j] > disk[j + 1]) {
                int temp = disk[j];
                disk[j] = disk[j + 1];
                disk[j + 1] = temp;
            }
        }
    }

    // Find the index of the head in the sorted disk tracks
    for (i = 0; i < n; i++) {
        if (disk[i] == head)
            break;
    }

    printf("Head movement: ");

    // If the direction is towards increasing track numbers (right)
    if (direction == 1) {
        // Move the head to the last track
        for (int j = i; j < n; j++) {
            next_track = disk[j];
            total_distance += abs(next_track - current_track);
            printf("%d -> ", next_track);
            current_track = next_track;
        }

        // Move the head to the first track
        total_distance += abs(0 - current_track);
        printf("0 -> ");

        // Move the head back to the next track after the head's initial position
        for (int j = 0; j < i; j++) {
            next_track = disk[j];
            total_distance += abs(next_track - current_track);
            printf("%d -> ", next_track);
            current_track = next_track;
        }
    }
    // If the direction is towards decreasing track numbers (left)
    else if (direction == -1) {
        // Move the head to the first track
        for (int j = i; j >= 0; j--) {
            next_track = disk[j];
            total_distance += abs(next_track - current_track);
            printf("%d -> ", next_track);
            current_track = next_track;
        }

        // Move the head to the last track
        total_distance += abs(MAX_TRACKS - 1 - current_track);
        printf("%d -> ", MAX_TRACKS - 1);
        current_track = MAX_TRACKS - 1;

        // Move the head back to the next track after the head's initial position
        for (int j = n - 1; j > i; j--) {
            next_track = disk[j];
            total_distance += abs(next_track - current_track);
            printf("%d -> ", next_track);
            current_track = next_track;
        }
    }

    printf("\nTotal head movement: %d\n", total_distance);
}

int main()
{
    int disk[MAX_TRACKS];
    int n;
    int head;
    int direction;

    printf("Enter the number of disk tracks: ");
    scanf("%d", &n);

    printf("Enter the disk tracks (0 to %d): ", MAX_TRACKS - 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &disk[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the direction of disk head movement (1 for right, -1 for left): ");
    scanf("%d", &direction);

    cscan(disk, n, head, direction);

    return 0;
}
