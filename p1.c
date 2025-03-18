#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int process_id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;  
    int remaining_time;  
} Process;


void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}


void calculate_wait_turnaround(Process processes[], int n) {
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        processes[i].completion_time = processes[i].turnaround_time + processes[i].arrival_time;
    }
}


void sjf_non_preemptive(Process processes[], int n) {
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                swap(&processes[i], &processes[j]);
            }
        }
    }

    calculate_wait_turnaround(processes, n);

    printf("\nNon-Preemptive SJF Scheduling:\n");
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    int total_wait_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].completion_time);
        total_wait_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}


void sjf_preemptive(Process processes[], int n) {
    int time = 0, completed = 0;
    int total_wait_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nPreemptive SJF Scheduling (SRTF):\n");

    while (completed < n) {
        int min_burst_time = -1;
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (min_burst_time == -1 || processes[i].remaining_time < min_burst_time) {
                    min_burst_time = processes[i].remaining_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        processes[idx].remaining_time--;
        time++;

        if (processes[idx].remaining_time == 0) {
            completed++;
            processes[idx].completion_time = time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }
    }

    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].completion_time);
        total_wait_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
    }

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Non-Preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sjf_non_preemptive(processes, n);
            break;
        case 2:
            sjf_preemptive(processes, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
