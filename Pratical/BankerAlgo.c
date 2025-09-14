#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int a, b, c, d;
} Obj;

int main() {
    int n;
    printf("Enter no.of processes: ");
    scanf("%d", &n);

    Obj allocated[n], max[n], need[n];
    bool isCompleted[n]; 


    for (int i = 0; i < n; i++) {
        printf("Enter all allocated values of process P%d: ", i);
        scanf("%d %d %d %d", &allocated[i].a, &allocated[i].b, &allocated[i].c, &allocated[i].d);
        isCompleted[i] = false;
    }


    for (int i = 0; i < n; i++) {
        printf("Enter all max values of process P%d: ", i);
        scanf("%d %d %d %d", &max[i].a, &max[i].b, &max[i].c, &max[i].d);
    }

    for (int i = 0; i < n; i++) {
        need[i].a = max[i].a - allocated[i].a;
        need[i].b = max[i].b - allocated[i].b;
        need[i].c = max[i].c - allocated[i].c;
        need[i].d = max[i].d - allocated[i].d;
    }

    int a, b, c, d;
    printf("Enter available resources (a b c d): ");
    scanf("%d %d %d %d", &a, &b, &c, &d);

    // Banker’s algorithm
    int completed = 0;
    while (completed != n) {
        bool flag = false;

        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && need[i].a <= a && need[i].b <= b &&
                need[i].c <= c && need[i].d <= d) {
                
                a += allocated[i].a;
                b += allocated[i].b;
                c += allocated[i].c;
                d += allocated[i].d;

                isCompleted[i] = true;  
                flag = true;
                completed++;

                printf("Process P%d executed...\n", i);
                printf("Available resources: %d %d %d %d\n", a, b, c, d);
            }
        }

        if (!flag) {
            printf("Deadlock detected. System is NOT in a safe state.\n");
            break;
        }
    }

    if (completed == n) {
        printf("All processes executed successfully. System is in a SAFE state.\n");
    }

    return 0;
}
