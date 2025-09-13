#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid, at, bt, ct, wt, tat;
} Process;

// Sort by arrival time
int comparator(const void *a, const void *b) {
    return ((Process *)a)->at - ((Process *)b)->at;
}

int main() {
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter process %d details (ArrivalTime BurstTime): ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
    }

    qsort(p, n, sizeof(Process), comparator);

    int currTime = 0, wasteTime = 0;
    for (int i = 0; i < n; i++) {
        if (currTime < p[i].at) {
            wasteTime += (p[i].at - currTime);
            currTime = p[i].at;
        }
        p[i].ct = currTime + p[i].bt;
        currTime = p[i].ct;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += p[i].tat;
        avgWT  += p[i].wt;
    }
    avgTAT /= n;
    avgWT  /= n;

    float cpuUtil = ((float)(currTime-wasteTime) / (currTime)) * 100.0f;
    float throughput = (float)n / (currTime);

    printf("\nAverage Turnaround Time = %.2f\n", avgTAT);
    printf("Average Waiting Time = %.2f\n", avgWT);
    printf("CPU Utilization = %.2f%%\n", cpuUtil);
    printf("Throughput = %.4f processes/unit time\n", throughput);

    return 0;
}
