#include <stdio.h>

struct Process {
    int id;             
    int arrivalTime;     
    int burstTime;       
    int waitingTime;     
    int turnaroundTime;
};


void fcfs(struct Process proc[], int n) {
    proc[0].waitingTime = 0; 

  
    for (int i = 1; i < n; i++) {
        proc[i].waitingTime = proc[i - 1].waitingTime + proc[i - 1].burstTime;
    }

   
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
    }
}


void calculateAvgTimes(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

   
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }

   
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}


void printProcesses(struct Process proc[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].waitingTime, proc[i].turnaroundTime);
    }
}

int main() {
    int n;

   
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

   
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;  
        printf("\nEnter arrival time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].arrivalTime);
        printf("Enter burst time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].burstTime);
    }

  
    fcfs(proc, n);

 
    printProcesses(proc, n);
    calculateAvgTimes(proc, n);

    return 0;
}
