#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};


void calculateRoundRobin(struct Process proc[], int n, int quantum) {
    int time = 0;  
    int remaining_processes = n; 

    while (remaining_processes > 0) {
       
        for (int i = 0; i < n; i++) {
           
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > quantum) {
                   
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].turnaround_time = time; 
                    proc[i].remaining_time = 0;  
                    remaining_processes--;  
                }
            }
        }
    }
}


void printResults(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

   
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
}

int main() {
    int n, quantum;

  
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time; 
    }

    
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

   
    calculateRoundRobin(proc, n, quantum);

   
    printResults(proc, n);

    return 0;
}
