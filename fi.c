#include <stdio.h>

struct Process{
    int pid;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int turnarroundtime;
    int waitingtime;
};

void sortByArrivalTime(struct Process p[], int n){
    struct Process temp;
    for(int i=0;i<n-1;i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].arrivaltime>p[j+1].arrivaltime){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void calculateTime(struct Process p[], int n) {
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrivaltime) {
            time = p[i].arrivaltime;  // If CPU is idle, move time forward
        }

        p[i].completiontime = time + p[i].bursttime;  // Completion Time
        time = p[i].completiontime;  // Update current time

        p[i].turnarroundtime = p[i].completiontime- p[i].arrivaltime;  // Turnaround Time
        p[i].waitingtime = p[i].turnarroundtime - p[i].bursttime;  // Waiting Time
    }
}

void printGaantChart(struct Process p[], int n) {
    printf("\nGaant Chart:\n");
    printf(" ");

    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }
    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n0");

    for (int i = 0; i < n; i++) {
        printf("      %d", p[i].completiontime);
    }
    printf("\n");
}

void printProcessTable(struct Process p[], int n) {
    printf("\nProcesses  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++) {
        printf("   P%d      %d   %d   %d   %d   %d\n",
               p[i].pid, p[i].arrivaltime, p[i].bursttime, p[i].completiontime, p[i].turnarroundtime, p[i].waitingtime);
    }

    float avgTAT;
    float sumTAT;

    float avgWT;
    float sumWT;

    for(int i=0; i<n; i++){
        sumTAT+=p[i].turnarroundtime;
    }
    avgTAT=sumTAT/n;

    for(int i=0; i<n; i++){
        sumWT+=p[i].waitingtime;
    }
    avgWT=sumWT/n;

    printf("Average Turn Around Time: %f\n", avgTAT);
    printf("Average Waiting Time: %f\n", avgWT);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];


    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d %d", &p[i].arrivaltime, &p[i].bursttime);
    }

    
    sortByArrivalTime(p, n);

    
    calculateTime(p, n);


    printProcessTable(p, n);

   
    printGaantChart(p, n);

    return 0;
}
