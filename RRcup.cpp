#include <stdio.h>

#define MAX_PROCESS 100

struct Process {
    int pid;        // Process ID
    int burstTime;  // Burst time
    int remainingTime; // Remaining burst time
};

void simulateRR(struct Process processes[], int n, int quantum) {
    int currentTime = 0;
    int completed = 0;

    printf("Process Execution Order:\n");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                int executionTime = (processes[i].remainingTime < quantum) ? processes[i].remainingTime : quantum;

                printf("P%d ", processes[i].pid);

                currentTime += executionTime;
                processes[i].remainingTime -= executionTime;

                if (processes[i].remainingTime == 0)
                    completed++;
            }
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
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    simulateRR(processes, n, quantum);

    return 0;
}
