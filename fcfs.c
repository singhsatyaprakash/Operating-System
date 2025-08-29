#include <stdio.h>
#include <stdlib.h>

struct process_struct {
    int pid;            // Process ID
    int at;             // Arrival Time
    int bt;             // Burst Time
    int ct, wt, tat, rt; // Completion, Waiting, Turnaround, Response Time
    int start_time;     // Start Time
} ps[100];

// Find maximum of two values
int findmax(int a, int b) {
    return (a > b) ? a : b;
}

// Comparator: Sort by Arrival Time (ascending)
int comparatorAT(const void *a, const void *b) {
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    if (x < y) return -1;
    else if (x > y) return 1;
    else return 0;
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int length_cycle, total_idle_time = 0;
    float cpu_utilization;

    // Input arrival times and validate
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        if (ps[i].at < 0) {
            printf("Invalid arrival time. Must be >= 0.\n");
            return 1;
        }
        ps[i].pid = i;
    }

    // Input burst times and validate
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        if (ps[i].bt <= 0) {
            printf("Invalid burst time. Must be > 0.\n");
            return 1;
        }
    }

    // Sort by arrival time
    qsort(ps, n, sizeof(struct process_struct), comparatorAT);

    // Calculations
    for (int i = 0; i < n; i++) {
        ps[i].start_time = (i == 0) ? ps[i].at : findmax(ps[i].at, ps[i - 1].ct);
        ps[i].ct = ps[i].start_time + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].start_time - ps[i].at;

        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        sum_rt += ps[i].rt;

        if (i > 0) {
            total_idle_time += (ps[i].start_time - ps[i - 1].ct);
        }
    }

    length_cycle = ps[n - 1].ct - ps[0].start_time;

    // Output
    printf("\nProcess No.\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct,
               ps[i].tat, ps[i].wt, ps[i].rt);
    }

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    // Averages and Performance Metrics
    printf("\nAverage Turnaround Time = %.2f", sum_tat / n);
    printf("\nAverage Waiting Time = %.2f", sum_wt / n);
    printf("\nAverage Response Time = %.2f", sum_rt / n);
    printf("\nThroughput = %.2f processes/unit time", n / (float)length_cycle);
    printf("\nCPU Utilization = %.2f%%", cpu_utilization * 100);
    printf("\n");

    return 0;
}
