#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void calculateTotalHeadMovement(int requests[], int n, int initialPosition)
{
    int headMovement = 0;
    int currentTrack = initialPosition;

    for (int i = 0; i < n; i++) {
        headMovement += abs(requests[i] - currentTrack);
        currentTrack = requests[i];
    }

    printf("Total head movement: %d\n", headMovement);
}

int main()
{
    int requests[MAX_REQUESTS];
    int n;
    int initialPosition;

    printf("FCFS Disk Scheduling Algorithm\n\n");

    printf("Enter the number of requests (up to %d): ", MAX_REQUESTS);
    scanf("%d", &n);

    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialPosition);

    calculateTotalHeadMovement(requests, n, initialPosition);

    return 0;
}
