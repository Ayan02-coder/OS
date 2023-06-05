 #include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int request_resources(int process_id, int request[])
{
    // Check if the request exceeds the process's declared maximum needs
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process_id][i])
            return -1;
    }

    // Check if the request can be granted based on the available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > available[i])
            return -1;
    }

    // Simulate resource allocation
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    return 0;
}

int release_resources(int process_id)
{
    // Release the allocated resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] += allocation[process_id][i];
        allocation[process_id][i] = 0;
        need[process_id][i] = max[process_id][i];
    }

    return 0;
}

int is_safe_state()
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safe_sequence[MAX_PROCESSES];
    int completed_processes = 0;

    // Initialize work array and find unfinished processes
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    while (completed_processes < MAX_PROCESSES) {
        int process_found = 0;

        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int resource_found = 1;

                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        resource_found = 0;
                        break;
                    }
                }

                if (resource_found) {
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }

                    safe_sequence[completed_processes] = i;
                    finish[i] = 1;
                    completed_processes++;
                    process_found = 1;
                }
            }
        }

        // No process found in the current iteration
        if (!process_found) {
            return 0;
        }
    }

    // Print the safe sequence
    printf("Safe sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");

    return 1;
}

int main()
{
    printf("Enter the number of resources: ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resource requirements for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the resource allocation for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    if (is_safe_state()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is in an unsafe state.\n");
    }

    return 0;
}
