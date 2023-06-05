#include <stdio.h>

#define MAX_PROCESS 100

struct Process {
    int pid;        // Process ID
    int burstTime;  // Burst time
    int priority;   // Priority
    int isCompleted; // Flag to track if the process has completed
};

void simulatePriority(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    printf("Process Execution Order:\n");

    while (completed < n) {
        int highestPriority = -1;
        int highestPriorityIndex = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].isCompleted == 0 && processes[i].priority > highestPriority) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex != -1) {
            printf("P%d ", processes[highestPriorityIndex].pid);

            currentTime += processes[highestPriorityIndex].burstTime;
            processes[highestPriorityIndex].isCompleted = 1;

            completed++;
        }
    }

    printf("\n");
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESS];

    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);

        printf("Enter the priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);

        processes[i].pid = i + 1;
        processes[i].isCompleted = 0;
    }

    simulatePriority(processes, n);

    return 0;
}
