#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

struct process_struct {
    int pid;          // Process ID
    int at;           // Arrival Time
    int bt;           // Burst Time
    int ct;           // Completion Time
    int wt;           // Waiting Time
    int tat;          // Turnaround Time
    int rt;           // Response Time
    int start_time;   // First time process gets CPU
    int bt_remaining; // Remaining Burst Time
} ps[100];

// Utility function
int findmax(int a, int b) {
    return (a > b) ? a : b;
}

// Comparator: sort by Arrival Time
int comparatorAT(const void *a, const void *b) {
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    if (x < y) return -1;
    else if (x > y) return 1;
    else return 0;
}

// Comparator: sort by Process ID
int comparatorPID(const void *a, const void *b) {
    int x = ((struct process_struct *)a)->pid;
    int y = ((struct process_struct *)b)->pid;
    if (x < y) return -1;
    else if (x > y) return 1;
    else return 0;
}

int main() {
    int n, index;
    float cpu_utilization;
    bool visited[100] = {false}, is_first_process = true;
    int current_time = 0, max_completion_time;
    int completed = 0, tq, total_idle_time = 0, length_cycle;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    int queue[100], front = -1, rear = -1;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    // Input arrival times
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
    }

    // Input burst times
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        ps[i].bt_remaining = ps[i].bt;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    // Sort processes by arrival time
    qsort((void *)ps, n, sizeof(struct process_struct), comparatorAT);

    // First process goes to the queue
    front = rear = 0;
    queue[rear] = 0;
    visited[0] = true;

    // Round Robin scheduling loop
    while (completed != n) {
        index = queue[front];
        front++;

        // If process is executing for the first time
        if (ps[index].bt_remaining == ps[index].bt) {
            ps[index].start_time = findmax(current_time, ps[index].at);
            total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;
            current_time = ps[index].start_time;
            is_first_process = false;
        }

        // Run process for tq or remaining time
        if (ps[index].bt_remaining - tq > 0) {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        } else {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            // Calculate metrics
            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }

        // Add newly arrived processes to the queue
        for (int i = 1; i < n; i++) {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false) {
                queue[++rear] = i;
                visited[i] = true;
            }
        }

        // If process still has burst time left, push it back
        if (ps[index].bt_remaining > 0) {
            queue[++rear] = index;
        }

        // If queue is empty, add the next available process
        if (front > rear) {
            for (int i = 1; i < n; i++) {
                if (ps[i].bt_remaining > 0) {
                    queue[++rear] = i;
                    visited[i] = true;
                    break;
                }
            }
        }
    } // end while

    // Find length of cycle
    max_completion_time = INT_MIN;
    for (int i = 0; i < n; i++) {
        max_completion_time = findmax(max_completion_time, ps[i].ct);
    }
    length_cycle = max_completion_time - ps[0].at;

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    // Sort back by PID for output
    qsort((void *)ps, n, sizeof(struct process_struct), comparatorPID);

    // Output table
    printf("\nProcess No.\tAT\tBT\tStart Time\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               ps[i].pid, ps[i].at, ps[i].bt, ps[i].start_time,
               ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }

    // Final stats
    printf("\nAverage Turnaround Time = %.2f", (float)sum_tat / n);
    printf("\nAverage Waiting Time   = %.2f", (float)sum_wt / n);
    printf("\nAverage Response Time  = %.2f", (float)sum_rt / n);
    printf("\nThroughput             = %.2f", n / (float)length_cycle);
    printf("\nCPU Utilization        = %.2f%%\n", cpu_utilization * 100);

    return 0;
}
