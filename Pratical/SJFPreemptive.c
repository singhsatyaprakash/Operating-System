
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt, rt;
} Process;

int main() {
    int n;
    printf("Enter No. of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter process %d details (ArrivalTime BurstTime): ", i);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i;
        p[i].rt = -1;  // mark response time uninitialized
    }

    int remBT[n];
    for (int i = 0; i < n; i++) remBT[i] = p[i].bt;

    int completed = 0, currTime = 0, wasteTime = 0;
    int lastCompletion = 0;

    while (completed != n) {
        int idx = -1;
        int minRem = INT_MAX;

        // Find process with minimum remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currTime && remBT[i] > 0) {
                if (remBT[i] < minRem) {
                    minRem = remBT[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currTime++;      // CPU is idle
            wasteTime++;
        } else {
            // First response time (when it starts first time)
            if (p[idx].rt == -1) {
                p[idx].rt = currTime - p[idx].at;
            }

            remBT[idx]--;
            currTime++;

            if (remBT[idx] == 0) {
                completed++;
                p[idx].ct = currTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                lastCompletion = currTime;
            }
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    int totalWT = 0, totalTAT = 0, totalRT = 0, totalBT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        totalRT += p[i].rt;
        totalBT += p[i].bt;
    }

    printf("\nAvg TAT: %.2f\n", (float)totalTAT / n);
    printf("Avg WT: %.2f\n", (float)totalWT / n);
    printf("Avg RT: %.2f\n", (float)totalRT / n);

    float cpuUtil = ((float)(lastCompletion - wasteTime) / lastCompletion) * 100.0;
    float throughput = (float)n / lastCompletion;

    printf("CPU Utilization: %.2f%%\n", cpuUtil);
    printf("Throughput: %.4f processes/unit time\n", throughput);

    return 0;
}
