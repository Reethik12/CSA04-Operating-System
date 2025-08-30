#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, writeBlock;
int data = 0;
int readersCount = 0;

void* reader(void* arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock); // First reader locks writers
        }
        sem_post(&mutex);

        // Reading operation
        printf("Reader reads data: %d\n", data);
        usleep(100000); // Sleep 0.1s for demonstration

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock); // Last reader releases writers
        }
        sem_post(&mutex);

        i++;
    }
    return NULL;
}

void* writer(void* arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&writeBlock);

        // Writing operation
        data++;
        printf("Writer writes data: %d\n", data);
        usleep(150000); // Sleep 0.15s for demonstration

        sem_post(&writeBlock);
        i++;
    }
    return NULL;
}

int main() {
    pthread_t readerThread, writerThread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Create reader and writer threads
    pthread_create(&readerThread, NULL, reader, NULL);
    pthread_create(&writerThread, NULL, writer, NULL);

    // Wait for threads to finish
    pthread_join(readerThread, NULL);
    pthread_join(writerThread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}

