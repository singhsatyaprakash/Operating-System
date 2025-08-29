#include <stdio.h>

struct Process {
    int pid, at, bt;
    int ct, wt, tat, rt, start;
};

int findmax(int a, int b) { return (a > b) ? a : b; }
int findmin(int a, int b) { return (a < b) ? a : b; }

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int bt_rem[n], completed = 0, time = 0;
    int queue[100], front = 0, rear = 0, visited[100] = {0};
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    for (int i = 0; i < n; i++) {
        printf("AT BT for P%d: ", i);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i;
        bt_rem[i] = p[i].bt;
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Start with earliest arrival
    int min_at = p[0].at;
    for (int i = 1; i < n; i++)
        if (p[i].at < min_at) min_at = p[i].at;
    time = min_at;

    // Add first arrivals to queue
    for (int i = 0; i < n; i++)
        if (p[i].at == time) queue[rear++] = i, visited[i] = 1;

    while (completed < n) {
        if (front == rear) { // CPU idle
            time++;
            for (int i = 0; i < n; i++)
                if (!visited[i] && p[i].at <= time && bt_rem[i] > 0)
                    queue[rear++] = i, visited[i] = 1;
            continue;
        }

        int idx = queue[front++]; // Get process
        if (bt_rem[idx] == p[idx].bt) // First time execution
            p[idx].start = findmax(time, p[idx].at);

        int exec_time = findmin(tq, bt_rem[idx]);
        time = findmax(time, p[idx].at) + exec_time;
        bt_rem[idx] -= exec_time;

        // Add new arrivals
        for (int i = 0; i < n; i++)
            if (!visited[i] && p[i].at <= time && bt_rem[i] > 0)
                queue[rear++] = i, visited[i] = 1;

        if (bt_rem[idx] > 0)
            queue[rear++] = idx; // Still has burst left
        else {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].start - p[idx].at;
            sum_tat += p[idx].tat;
            sum_wt += p[idx].wt;
            sum_rt += p[idx].rt;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);

    printf("\nAvg TAT = %.2f", sum_tat / n);
    printf("\nAvg WT  = %.2f", sum_wt / n);
    printf("\nAvg RT  = %.2f", sum_rt / n);
    printf("\nThroughput = %.2f", n / (float)(time - min_at));
    printf("\nCPU Utilization = %.2f%%\n", ((time - min_at) / (float)(time - min_at)) * 100);

    return 0;
}
