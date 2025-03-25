#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int priority;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Function to calculate waiting time for non-preemptive priority scheduling
void calculateWaitingTimeNonPreemptive(struct Process proc[], int n) {
    proc[0].waiting_time = 0;  // The first process does not have to wait
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

// Function to calculate turnaround time for non-preemptive priority scheduling
void calculateTurnaroundTimeNonPreemptive(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

// Function to implement non-preemptive priority scheduling
void prioritySchedulingNonPreemptive(struct Process proc[], int n) {
    struct Process temp;
    
    // Sort processes based on priority (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    // After sorting, calculate waiting and turnaround times
    calculateWaitingTimeNonPreemptive(proc, n);
    calculateTurnaroundTimeNonPreemptive(proc, n);
}

// Function to print the results
void printResults(struct Process proc[], int n) {
    printf("\nProcess ID\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burst_time, proc[i].priority, proc[i].arrival_time, proc[i].waiting_time, proc[i].turnaround_time);
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

   
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &proc[i].priority);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
    }

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Non-Preemptive Priority Scheduling\n");
    printf("2. Preemptive Priority Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            prioritySchedulingNonPreemptive(proc, n);
            printResults(proc, n);
            break;
        
        case 2:
            printf("Preemptive scheduling is not yet implemented in this example.\n");
            break;
        
        default:
            printf("Invalid choice! Exiting program.\n");
            break;
    }

    return 0;
}
