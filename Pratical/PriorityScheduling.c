#include<stdio.h>
#include<limits.h>
typedef struct process{
    int pid,at,bt,ct,tat,wt,rt,pr;
}Process;
int main(){
    int n;
    printf("Enter no. of process:");
    scanf("%d",&n);
    Process p[n];
    for(int i=0;i<n;i++){
        printf("Enter process %d deatils:(AT,BT,Priority):",i);
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pr);
        p[i].pid=i;
        p[i].rt=-1;
    }
    int currTime=0,wasteTime=0;
    int count=0;
    int completed[n];
    for(int i=0;i<n;i++){
        completed[i]=0;
    }
    while(count!=n){
        //finding priotrity process
        int idx=-1;
        int maxpr=INT_MIN;//high number high priority
        for(int i=0;i<n;i++){
            if(p[i].at<=currTime && !completed[i]){
                if(p[i].pr>maxpr){
                    idx=i;
                    maxpr=p[i].pr;
                }
            }
        }
        if(idx==-1){
            currTime++;
            wasteTime++;
        }
        else{
            p[idx].rt=currTime-p[idx].at;
            p[idx].ct=currTime+p[idx].bt;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            completed[idx]=1;
            count++;
            currTime+=p[idx].bt;
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

    float cpuUtil = ((float)(currTime - wasteTime) / currTime) * 100.0;
    float throughput = (float)n / currTime;

    printf("CPU Utilization: %.2f%%\n", cpuUtil);
    printf("Throughput: %.4f processes/unit time\n", throughput);

    return 0;
}