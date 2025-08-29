#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
 
struct process_struct
{
  int pid;
  int at;
  int bt;
  int pt;
  int ct,wt,tat,rt,start_time;
}ps[100];
 
int findmax(int a, int b)
{
    return a>b?a:b;
}
 
int findmin(int a, int b)
{
    return a<b?a:b;
}
 
int main()
{
     
    int n;
    bool is_completed[100]={false},is_first_process=true;
    int currTime = 0;
    int completed = 0;
    printf("Enter total number of processes: ");
    scanf("%d",&n);
    int sum_tat=0,sum_wt=0,sum_rt=0,total_idle_time=0,prev=0,length_cycle;
    float cpu_utilization;
    int max_completion_time,min_arrival_time;
 
    for(int i=0;i<n;i++)
    {
        printf("Enter Process %d Arrival Time: ",i);
        scanf("%d",&ps[i].at);
        ps[i].pid = i ;
    }
     
    for(int i=0;i<n;i++)
    {
        printf("Enter Process %d Burst Time: ",i);
        scanf("%d",&ps[i].bt);
    }
    for(int i=0;i<n;i++)
    {
        printf("Enter Process %d Priority: ",i);
        scanf("%d",&ps[i].pt);
    }
     
    while(completed!=n)
    {
        //find process with max. priority in ready queue at currTime
        int index=-1;
        int priority=INT_MIN;
        for(int i=0;i<n;i++){
            if(ps[i].at <= currTime && is_completed[i] == false) {
                if(ps[i].pt > priority) {
                    priority = ps[i].pt;
                    index = i;
                }
                if(ps[i].pt== priority) {
                    if(ps[i].at < ps[index].at) {
                        priority= ps[i].pt;
                        index = i;
                    }
                    if(ps[i].at==ps[index].at){
                        if(ps[i].pid<ps[index].pid){
                            index=i;
                            priority=ps[i].pt;
                        }
                    }
                }
            }
        }
        if(index==-1){
            currTime++;
        }
        else
        {
        ps[index].start_time = currTime;
        ps[index].ct = ps[index].start_time + ps[index].bt;
        ps[index].tat = ps[index].ct - ps[index].at;
        ps[index].wt = ps[index].tat - ps[index].bt;
        ps[index].rt = ps[index].wt;
        // ps[index].rt = ps[index].start_time - ps[index].at; 
                 
        sum_tat +=ps[index].tat;
        sum_wt += ps[index].wt;
        sum_rt += ps[index].rt;
        total_idle_time += (is_first_process==true) ? 0 : (ps[index].start_time -  prev); 
         
        completed++;
        is_completed[index]=true;
        currTime = ps[index].ct;
        prev= currTime;
        is_first_process = false;
        }
    }
     
    //Calculate Length of Process completion cycle
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for(int i=0;i<n;i++)
    {
        max_completion_time = findmax(max_completion_time,ps[i].ct); 
        min_arrival_time = findmin(min_arrival_time,ps[i].at); 
    }
    length_cycle = max_completion_time - min_arrival_time; 
 
    //Output
    printf("\nProcess No.\tAT\tCPU Burst Time\tPriority\tCT\tTAT\tWT\tRT\n"); 
    for(int i=0;i<n;i++)
     
        printf("%d\t\t%d\t%d\t\t%d\t\t%d\t%d\t%d\t%d\n",ps[i].pid,ps[i].at,ps[i].bt,ps[i].pt,ps[i].ct,ps[i].tat,ps[i].wt,ps[i].rt); 
 
    printf("\n");
     
    cpu_utilization = (float)(length_cycle - total_idle_time)/ length_cycle; 
 
    printf("\nAverage Turn Around time= %f ",(float)sum_tat/n); 
    printf("\nAverage Waiting Time= %f ",(float)sum_wt/n); 
    printf("\nAverage Response Time= %f ",(float)sum_rt/n); 
    printf("\nThroughput= %f",n/(float)length_cycle);     
    printf("\nCPU Utilization(Percentage)= %f",(cpu_utilization*100)); 
 
    return 0; 
}