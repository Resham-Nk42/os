#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m; 
    int allocation[MAX][MAX], request[MAX][MAX], available[MAX];
    bool finish[MAX] = {false};
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter allocation matrix (%d x %d):\n", n, m);
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter request matrix (%d x %d):\n", n, m);
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter available resources (%d): ", m);
    for(j = 0; j < m; j++)
        scanf("%d", &available[j]);

    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > available[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (j = 0; j < m; j++)
                        available[j] += allocation[i][j];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            break; 
    }

    bool deadlock = false;
    printf("\nProcesses in deadlock: ");
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (!deadlock)
        printf("None. No deadlock detected.\n");
    else
        printf("\nDeadlock detected.\n");

    return 0;
}