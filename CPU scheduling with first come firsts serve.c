#include <stdio.h>

int main() {
    int A[10][5];  // A[i][0] = Process ID, A[i][1] = Burst Time, A[i][2] = Waiting Time, A[i][3] = Turnaround Time
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1;  // Assign process ID
    }

    // Sort processes based on burst time (Selection Sort)
    for (i = 0; i < n - 1; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            if (A[j][1] < A[index][1]) {
                index = j;
            }
        }
        // Swap burst time
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;
        // Swap process ID
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    // Calculate waiting time
    A[0][2] = 0; // First process waiting time is 0
    total = 0;
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++) {
            A[i][2] += A[j][1];
        }
        total += A[i][2];
    }
    avg_wt = (float)total / n;

    // Calculate turnaround time and print results
    total = 0;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];  // Turnaround time = burst time + waiting time
        total += A[i][3];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }
    avg_tat = (float)total / n;

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}

