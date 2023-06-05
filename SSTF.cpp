#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_REQUESTS 100

void calculateSSTF(int requests[], int head, int n)
{
    int distance = 0;
    int current_track = head;
    bool visited[MAX_REQUESTS] = {false};

    printf("SSTF Sequence: %d", current_track);

    for (int i = 0; i < n - 1; i++) {
        int min_distance = INT_MAX;
        int next_track;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(requests[j] - current_track) < min_distance) {
                min_distance = abs(requests[j] - current_track);
                next_track = requests[j];
            }
        }

        distance += min_distance;
        current_track = next_track;
        visited[next_track] = true;

        printf(" -> %d", current_track);
    }

    printf("\nTotal Head Movement: %d\n", distance);
}

int main()
{
    int n;
    int requests[MAX_REQUESTS];
    int head;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    calculateSSTF(requests, head, n);

    return 0;
}
