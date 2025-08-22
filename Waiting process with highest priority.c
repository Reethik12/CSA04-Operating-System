#include <stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], pr[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst time and priority for each process
    for (i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (smaller number = higher priority): ");
        scanf("%d", &pr[i]);
        p[i] = i + 1;  // process ID
    }

    // Sorting processes based on priority (smaller number = higher priority)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos]) { // smaller number = higher priority
                pos = j;
            }
        }

        // Swap priorities
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        // Swap burst times
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process IDs
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0; // waiting time for first process is 0

    // Calculate waiting times
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
        total += wt[i];
    }

    avg_wt = (float) total / n;
    total = 0;

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    // Calculate turnaround times and display
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
    }

    avg_tat = (float) total / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}

