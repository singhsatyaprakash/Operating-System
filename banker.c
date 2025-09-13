#include <stdio.h>
#include <stdbool.h>

// Structure to hold process information
struct process_info {
    int max[10];
    int allocated[10];
    int need[10];
};

int no_of_process, no_of_resources;

// Function to take input for processes and available resources
void input(struct process_info process[], int available[]) {

    for (int i = 0; i < no_of_process; i++) {
        printf("For process %d:\n",i);
        // Max demand
        printf("Max demand:");
        for (int j = 0; j < no_of_resources; j++)
            scanf("%d", &process[i].max[j]);

        // Allocated and calculate need
        printf("Allocated:");
        for (int j = 0; j < no_of_resources; j++) {
            scanf("%d", &process[i].allocated[j]);
            process[i].need[j] = process[i].max[j] - process[i].allocated[j];
        }
    }

    printf("Enter Available Resources: ");
    for (int i = 0; i < no_of_resources; i++) {
        scanf("%d", &available[i]);
    }
}

// Function to display process information in tabular form
void showTheInfo(struct process_info process[no_of_process]) {
    printf("\nPID\tMaximum\t\tAllocated\tNeed\n");
    for (int i = 0; i < no_of_process; i++) {
        printf("P[%d]\t", i);

        // Max
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].max[j]);
        printf("\t\t");

        // Allocated
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].allocated[j]);
        printf("\t\t");

        // Need
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].need[j]);

        printf("\n");
    }
}

// Function to apply Safety Algorithm
bool applySafetyAlgo(struct process_info process[], int available[], int safeSequence[]) {
    bool finish[no_of_process];
    int work[no_of_resources];

    // Initialize Work as Available
    for (int i = 0; i < no_of_resources; i++)
        work[i] = available[i];

    // Initialize Finish as false
    for (int i = 0; i < no_of_process; i++)
        finish[i] = false;

    bool proceed = true;
    int k = 0;

    while (proceed) {
        proceed = false;

        for (int i = 0; i < no_of_process; i++) {
            bool flag = true;

            if (finish[i] == false) {
                // Check if Need <= Work
                for (int j = 0; j < no_of_resources; j++) {
                    if (process[i].need[j] > work[j]) {
                        flag = false;
                        break;
                    }
                }

                if (flag == false)
                    continue;

                // If Need <= Work, allocate resources
                for (int j = 0; j < no_of_resources; j++)
                    work[j] += process[i].allocated[j];

                finish[i] = true;
                safeSequence[k++] = i;
                proceed = true;
            }
        }
    }

    // Check if all processes finished
    for (int i = 0; i < no_of_process; i++) {
        if (finish[i] == false)
            return false;
    }

    return true;
}


int main() {
    printf("Enter no. of process:");
    scanf("%d", &no_of_process);
    printf("Enter no. of resources:");
    scanf("%d", &no_of_resources);

    int available[no_of_resources];
    int safeSequence[no_of_process];
    struct process_info process[no_of_process];

    input(process, available);
    showTheInfo(process);

    if (applySafetyAlgo(process, available, safeSequence)) {
        printf("\nSystem is in SAFE State\n");
        printf("Safe Sequence is: ");
        for (int i = 0; i < no_of_process; i++)
            printf("P[%d] ", safeSequence[i]);
        printf("\n");
    } else {
        printf("\nSystem is NOT in a SAFE State\n");
    }

    return 0;
}
