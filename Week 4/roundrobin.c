#include<stdio.h>
void take(int a[], int n){
    for(int i=0;i<n;i++){
        printf("Enter for process %d: ", i+1);
        scanf("%d", &a[i]);
    }
}

void main(){
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int pid[n], at[n], bt[n];
    int ct[n], tat[n], wt[n], rt[n];
    int rem[n], visited[n];
    printf("Enter PIDs:\n");
    take(pid, n);
    printf("Enter Arrival Time:\n");
    take(at, n);
    printf("Enter Burst Time:\n");
    take(bt, n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    for(int i=0;i<n;i++){
        rem[i]=bt[i];
        visited[i]=0;
        rt[i]=-1;
    }
    int time=0, completed=0;
    int queue[100], front=0, rear=0;

    for(int i=0; i<n; i++){
        if(at[i]==0){
            queue[rear++]=i;
            visited[i]=1;
        }
    }
    float avg_tat=0, avg_wt=0, avg_rt=0;
    printf("\nReady Queue Order:\n");
    while(completed<n){
        if(front==rear){
            time++;
            for(int i=0;i<n;i++){
                if(at[i]<=time && visited[i]==0){
                    queue[rear++]=i;
                    visited[i]=1;
                }
            }
            continue;
        }
        int i=queue[front++];
        printf("P%d ", pid[i]);

        if(rt[i]==-1){
            rt[i]=time-at[i];
        }
        if(rem[i]>tq){
            time+=tq;
            rem[i]-=tq;
        }
        else{
            time+=rem[i];
            rem[i]=0;
            ct[i]=time;
            completed++;
        }
        for(int j=0; j<n; j++){
            if(at[j]<=time && visited[j]==0){
                queue[rear++]=j;
                visited[j]=1;
            }
        }
        if(rem[i]>0){
            queue[rear++]=i;
        }
    }
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        avg_tat+=tat[i];
        avg_wt+=wt[i];
        avg_rt+=rt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
    printf("\nAverage TAT=%.2f", avg_tat/n);
    printf("\nAverage WT=%.2f", avg_wt/n);
    printf("\nAverage RT=%.2f", avg_rt/n);
}
