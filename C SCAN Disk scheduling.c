#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek_time = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    // Sort the request queue
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    // Find the first request greater than or equal to head
    int i;
    for (i = 0; i < n; i++) {
        if (request_queue[i] >= head) break;
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    // Move right from current head to the end
    for (int j = i; j < n; j++) {
        seek_time += abs(head - request_queue[j]);
        head = request_queue[j];
        printf(" -> %d", head);
    }

    // Jump to the beginning (circular)
    if (i != 0) {
        seek_time += abs(head - 0);
        head = 0;
        printf(" -> %d", head);

        // Continue servicing the remaining requests
        for (int j = 0; j < i; j++) {
            seek_time += abs(head - request_queue[j]);
            head = request_queue[j];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}

