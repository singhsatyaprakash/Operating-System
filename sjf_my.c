#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
struct process_struct{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,startTime;
}ps[100];
int main(){
    int n;
    printf("Enter total number of process:");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Enter Arrival and Brust Time of process:%d",i);
        scanf("%d%d\n",&ps[i].at,&ps[i].bt);
        ps[i].pid=i;
    }
    bool isCompleted[100]={false};
    int completed=0,currTime=0;
    int sum_tat=0,sum_wt=0,sum_rt=0;
    while(completed!=n){
        int min_idx=-1; // no process is choosen
        int minimum=INT_MAX; //initial brust time

        //choosing process with less worst time and first arrived...
        for(int i=0;i<n;i++){
            if(ps[i].at<=currTime && isCompleted[i]==false){ //process reached already and not coompleted yet...
                if(ps[i].bt<minimum){
                    minimum=ps[i].bt;
                    min_idx=i;
                }
                if(ps[i].bt==minimum){
                    if(ps[i].at<ps[min_idx].at){
                        minimum=ps[i].bt;
                        min_idx=i;
                    }
                }

            }
        }
        if(min_idx=-1){
            currTime++;// CPU is at ideal state now, no task is assigned to it...
        }
        else{
            //calculating table...
            ps[min_idx].startTime=currTime;
            ps[min_idx].ct=ps[min_idx].startTime+ps[min_idx].bt;
            ps[min_idx].tat = ps[min_idx].ct - ps[min_idx].at;
            ps[min_idx].wt = ps[min_idx].tat - ps[min_idx].bt;
            ps[min_idx].rt = ps[min_idx].wt;

            sum_tat +=ps[min_idx].tat;
            sum_wt += ps[min_idx].wt;
            sum_rt += ps[min_idx].rt;

        }
    }
}