#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
typedef struct process{
    int pid,at,bt,ct,tat,wt,rt;
}Process;
int main(){
    int n;
    printf("Enter No. of process:");
    scanf("%d",&n);
    Process p[n];
    for(int i=0;i<n;i++){
        printf("Enter process %d deatails (Arrtivaltime,brustTime):",i);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].pid=i;
    }
    //calculation...
    int currTime=0,wasteTime=0;
    int completed[n];
    for(int i=0;i<n;i++){
        completed[i]=0;
    }
    int count=0;
    while(count!=n){
        int idx=-1;
        int minBrust=INT_MAX;
        for(int i=0;i<n;i++){
            if(!completed[i] && p[i].at<=currTime){
                if(p[i].bt<minBrust){
                    minBrust=p[i].bt;
                    idx=i;
                }
            }
        }
        if(idx==-1){
            currTime++;
            wasteTime++;
        }
        else{
            p[idx].ct=currTime+p[idx].bt;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            p[idx].rt=currTime-p[idx].at;//startTime- arrivalTime
            currTime=p[idx].ct;
            completed[idx]=1;
            count++;
        }
    }
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    int totalWt=0,totalTat=0,totalRt=0;
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
        totalWt+=p[i].wt;
        totalTat+=p[i].tat;
        totalRt+=p[i].rt;
    }
    printf("Avg TAT:%.2f\n",(float)totalTat/n);
    printf("Avg WT:%.2f\n",(float)totalWt/n);
    printf("Avg Rt:%.2f\n",(float)totalRt/n);
    printf("CPU Utilization:%.2f\n",(float)((currTime-wasteTime)/currTime)*100.0);
    printf("Throughput:%.2f\n",(float)n/currTime);
    return 0;
}