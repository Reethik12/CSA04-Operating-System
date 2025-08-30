#include <stdio.h>

void bestfit(int mp[], int p[], int m, int n) {
    int j = 0;
    for (int i = 0; i < n && j < m; i++) {
        if (mp[i] >= p[j]) {
            printf("\nProcess %d of size %d fits in partition %d of size %d", 
                   j+1, p[j], i+1, mp[i]);
            mp[i] -= p[j++];
            i = -1; // restart loop for next process
        }
    }
    for (int i = j; i < m; i++) {
        printf("\nProcess %d of size %d must wait", i+1, p[i]);
    }
}

void sort(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void rsort(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (a[i] < a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void firstfit(int mp[], int p[], int m, int n) {
    sort(mp, n);
    sort(p, m);
    bestfit(mp, p, m, n);
}

void worstfit(int mp[], int p[], int m, int n) {
    rsort(mp, n);
    sort(p, m);
    bestfit(mp, p, m, n);
}

int main() {
    int m, n, mp[20], p[20], ch;
    
    printf("Number of memory partitions: ");
    scanf("%d", &n);

    printf("Number of processes: ");
    scanf("%d", &m);

    printf("Enter the memory partitions:\n");
    for (int i = 0; i < n; i++) scanf("%d", &mp[i]);

    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++) scanf("%d", &p[i]);

    while (1) {
        printf("\n\n--- Memory Allocation Menu ---\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        // Make a copy of original memory partitions because allocation modifies them
        int mp_copy[20];
        for (int i = 0; i < n; i++) mp_copy[i] = mp[i];

        switch (ch) {
            case 1: 
                firstfit(mp_copy, p, m, n); 
                break;
            case 2: 
                bestfit(mp_copy, p, m, n); 
                break;
            case 3: 
                worstfit(mp_copy, p, m, n); 
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default: 
                printf("Invalid choice. Try again.\n"); 
                break;
        }
    }

    return 0;
}

