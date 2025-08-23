#include <stdio.h>

int main() {
    int n, i, j, temp, time = 0, count, over = 0;
    int at[10], bt[10], pr[10], start[10], end[10], waiting[10], turnaround[10];
    int sum_wait = 0, sum_turnaround = 0;
    float avgwait, avgturn;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d%d", &at[i], &bt[i]);
        pr[i] = i + 1; // process ID
    }

    // Sort processes by arrival time
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
            }
        }
    }

    while(over < n) {
        count = 0;

        // Count how many processes have arrived till current time
        for(i = over; i < n; i++) {
            if(at[i] <= time)
                count++;
            else
                break;
        }

        // If multiple processes available, sort them by burst time
        if(count > 1) {
            for(i = over; i < over + count - 1; i++) {
                for(j = i+1; j < over + count; j++) {
                    if(bt[i] > bt[j]) {
                        temp = at[i]; at[i] = at[j]; at[j] = temp;
                        temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                        temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                    }
                }
            }
        }

        // Schedule the next process
        if(time < at[over])  // if CPU is idle
            time = at[over];

        start[over] = time;
        time += bt[over];
        end[over] = time;

        waiting[over] = start[over] - at[over];
        turnaround[over] = end[over] - at[over];

        sum_wait += waiting[over];
        sum_turnaround += turnaround[over];

        over++;
    }

    avgwait = (float)sum_wait / n;
    avgturn = (float)sum_turnaround / n;

    // Print table header
    printf("----------------------------------------------------------------------------------\n");
    printf("| %-8s | %-12s | %-6s | %-6s | %-6s | %-12s | %-12s |\n",
           "Process", "Arrival", "Burst", "Start", "End", "Waiting", "Turnaround");
    printf("----------------------------------------------------------------------------------\n");

    // Print each process info
    for(i = 0; i < n; i++) {
        printf("| %-8s | %-12d | %-6d | %-6d | %-6d | %-12d | %-12d |\n",
               "P[i]", at[i], bt[i], start[i], end[i], waiting[i], turnaround[i]);
    }
    printf("----------------------------------------------------------------------------------\n");

    printf("\nAverage Waiting Time = %.2f\n", avgwait);
    printf("Average Turnaround Time = %.2f\n", avgturn);

    return 0;
}

