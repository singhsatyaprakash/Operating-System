#include<stdio.h>
#include<stdbool.h>
typedef struct{
    int a,b,c,d;
}Obj;
int main(){
    int n;
    printf("Enter no.of process:");
    scanf("%d",&n);
    // int r;
    // printf("Enter number of resources:");
    // scanf("%d",&r);
    Obj allocated[n],max[n],need[n];
    for(int i=0;i<n;i++){
      printf("Enter all allocated values of process P%d: ",i);
      scanf("%d",&allocated[i].a);
      scanf("%d",&allocated[i].b);
      scanf("%d",&allocated[i].c);
      scanf("%d",&allocated[i].d);
    }
    for(int i=0;i<n;i++){
      printf("Enter all max values of process P%d: ",i);
      scanf("%d",&max[i].a);
      scanf("%d",&max[i].b);
      scanf("%d",&max[i].c);
      scanf("%d",&max[i].d);
    }
    //calculating needed...
    for(int i=0;i<n;i++){
        need[i].a=max[i].a-allocated[i].a;
        need[i].b=max[i].b-allocated[i].b;
        need[i].c=max[i].c-allocated[i].c;
        need[i].d=max[i].d-allocated[i].d;
    }
    // for(int i=0;i<n;i++){
    //   printf("Enter all need values of process P%d: ",i);
    //   printf("%d",need[i].a);
    //   printf("%d",need[i].b);
    //   printf("%d",need[i].c);
    //   printf("%d",need[i].d);
    // }

    int a,b,c,d;
    printf("Enter avaliable resources:(a,b,c,d):");
    scanf("%d%d%d%d",&a,&b,&c,&d);
    
    //banker algorithm
    int completed=0;
    while(completed!=n){
        bool flag=false;
        for(int i=0;i<n;i++){
            if(need[i].a<=a && need[i].b<=b && need[i].c<=c && need[i].d<=d){
                a+=allocated[i].a;
                b+=allocated[i].b;
                c+=allocated[i].c;
                d+=allocated[i].d;
                flag=true;
                printf("Process P%d executed...\n",i);
                printf("%d %d %d %d\n",a,b,c,d);
                completed++;
            }
        }
        if(!flag){
            printf("Deadlock...");
        }
    }
    return 0;
}