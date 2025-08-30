#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>   // for close()

extern int errno;

int main() {
    // Try opening the file
    int fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);

    // Print file descriptor
    printf("fd = %d\n", fd);

    // Check for errors
    if (fd == -1) {
        printf("Error Number %d\n", errno);
        perror("Program");
    } else {
        printf("File opened successfully!\n");
        close(fd); // Close the file descriptor
    }

    return 0;
}

