#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function
void* func(void* arg) 
{
    printf("Inside the thread\n");
    pthread_exit(NULL);
}

void fun() 
{
    pthread_t ptid;

    // Create thread
    pthread_create(&ptid, NULL, func, NULL);

    // Detach the thread (so we don't need to join it)
    pthread_detach(ptid);

    printf("This line may be printed before thread terminates\n");

    // Compare thread IDs
    if (pthread_equal(ptid, pthread_self())) 
    {
        printf("Threads are equal\n");
    } 
    else 
    {
        printf("Threads are not equal\n");
    }

    // Give time for detached thread to print
    sleep(1); // only for demonstration

    printf("This line will be printed after thread ends (main thread continues)\n");

    pthread_exit(NULL);
}

int main() 
{
    fun();
    return 0;
}

