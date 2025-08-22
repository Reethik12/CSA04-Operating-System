#include <stdio.h>

int main() {
    int NOP, i, j, sum = 0, count = 0, y;
    int bt[20], temp[20], at[20];
    int wt = 0, tat = 0;
    float avg_wt, avg_tat;
    int quant;

    printf("Enter the number of processes: ");
    scanf("%d", &NOP);

    printf("Enter Burst Time for each process:\n");
    for(i = 0; i < NOP; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // temporary copy of burst time
    }

    printf("Enter Arrival Time for each process:\n");
    for(i = 0; i < NOP; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &at[i]);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quant);

    y = NOP; // number of processes left
    i = 0;
    sum = 0;

    printf("\nProcess No\tBurst Time\tTurnaround Time\tWaiting Time\n");

    while(y != 0) {
        if(temp[i] <= quant && temp[i] > 0) {
            sum += temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if(temp[i] > 0) {
            temp[i] -= quant;
            sum += quant;
        }

        if(temp[i] == 0 && count == 1) {
            y--;
            int tat_i = sum - at[i];
            int wt_i = tat_i - bt[i];
            wt += wt_i;
            tat += tat_i;
            printf("P%d\t\t%d\t\t%d\t\t%d\n", i+1, bt[i], tat_i, wt_i);
            count = 0;
        }

        if(i == NOP - 1) {
            i = 0;
        }
        else if(at[i+1] <= sum) {
            i++;
        }
        else {
            i = 0;
        }
    }

    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}

