#include<stdio.h>
#include<math.h>
void take(int a[], int n){
    for(int i=0;i<n;i++){
        printf("Enter for process %d: ", i+1);
        scanf("%d", &a[i]);
    }
}

int gcd(int a, int b) {
    if(b==0){
        return a;
    }
    else{
        return gcd(b, a%b);
    }
}

int lcm(int a[], int n) {
    int ans=a[0];
    for(int i=1; i<n; i++){
        ans=((a[i]*ans))/(gcd(a[i], ans));
    }
    return ans;
}

void main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int c[n], t[n], pid[n], prio[n], rem_cap[n];
    printf("Enter Capacity:\n");
    take(c, n);
    printf("Enter Time Period:\n");
    take(t, n);
    double u=0;
    double bound=n*(pow(2, (double) (1/n))-1);
    for(int i=0; i<n; i++){
        u+=(double) (c[i]/t[i]);
    }
    if(u<=bound){
        printf("Schedulable using RMS.\n");
    }
    else{
        printf("Utilization not within bound");
        if(u<=1){
            printf("but less than 1. RMS can be used.");
        }
        else{
            printf("and not less than 1. RMS can't be used");
        }
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(t[j]<t[i]){
                int temp=t[i];
                t[i]=t[j];
                t[j]=temp;

                temp=c[i];
                c[i]=c[j];
                c[j]=c[i];

                temp=pid[i];
                pid[i]=pid[j];
                pid[j]=pid[i];
            }
        }
    }
    for(int i=0; i<n; i++){
        prio[i]=pid[i];
        rem_cap[i]=c[i];
    }
    int j=0;
    int timeline[lcm(t, n)];
    for(int i=0; i<lcm(t, n); i++){
        if(rem_cap[j]==0){
            j++;
        }
        if(j>n){
            j=0;
        }
        timeline[i]=j;
        rem_cap[j]--;
    }
    for(int i=0; i<lcm(t, n); i++){
        printf("%d", timeline[i]);
    }
    printf("%d", lcm(t, n));
}
