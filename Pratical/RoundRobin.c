#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt, rt, bt_remain;
} Process;

int comparator(const void *a, const void *b) {
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;

    if (p1->at != p2->at) return p1->at - p2->at; // Sort by arrival time
    return p1->pid - p2->pid;                    // Then by PID
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter process %d arrival time & burst time: ", i);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].pid = i;
        p[i].bt_remain = p[i].bt;
        p[i].rt = -1; // response time not yet calculated
    }

    int tq;
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    qsort(p, n, sizeof(Process), comparator);

    int queue[100], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    queue[0] = 0;
    visited[0] = 1;

    int count = 0, currTime = p[0].at, wasteTime = 0;

    while (count != n) {
        if (front > rear) { // Queue empty → jump to next arrival
            for (int i = 0; i < n; i++) {
                if (p[i].bt_remain > 0 && !visited[i]) {
                    wasteTime += p[i].at - currTime;
                    currTime = p[i].at;
                    queue[++rear] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }

        int idx = queue[front++];
        if (p[idx].rt == -1) { // First time the process gets CPU
            p[idx].rt = currTime - p[idx].at;
        }

        if (p[idx].bt_remain > tq) {
            p[idx].bt_remain -= tq;
            currTime += tq;
        } else {
            currTime += p[idx].bt_remain;
            p[idx].bt_remain = 0;
            p[idx].ct = currTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            count++;
        }

        // Enqueue newly arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].bt_remain > 0 && p[i].at <= currTime && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }

        // Requeue current process if incomplete
        if (p[idx].bt_remain > 0) {
            queue[++rear] = idx;
        }
    }

    // Output results
    int totaltat = 0, totalwt = 0, totalrt = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        totaltat += p[i].tat;
        totalwt += p[i].wt;
        totalrt += p[i].rt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("Average TAT: %.2f\n", (float)totaltat / n);
    printf("Average WT: %.2f\n", (float)totalwt / n);
    printf("Average RT: %.2f\n", (float)totalrt / n);
    printf("CPU Utilization: %.2f%%\n",
           (float)(currTime - wasteTime) / currTime * 100);
    printf("Throughput: %.2f\n", (float)n / currTime);

    return 0;
}
