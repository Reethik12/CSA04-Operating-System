#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void create() {
    FILE *fp = fopen("sasi.txt", "w");
    if (fp == NULL) {
        printf("Error creating file.\n");
        return;
    }
    fclose(fp);
    printf("File created successfully.\n");
}

void copy() {
    const char *sourcefile = "sasi.txt";
    const char *destination_file = "sk.txt";

    int source_fd = open(sourcefile, O_RDONLY);
    if (source_fd == -1) {
        printf("Error opening source file.\n");
        return;
    }

    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        printf("Error creating destination file.\n");
        close(source_fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            printf("Error writing to destination file.\n");
            close(source_fd);
            close(dest_fd);
            return;
        }
    }

    close(source_fd);
    close(dest_fd);
    printf("File copied successfully.\n");
}

void delete_file() {
    if (remove("sasi.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error deleting file.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- File Operations Menu ---\n");
        printf("1. Create File\n");
        printf("2. Copy File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                copy();
                break;
            case 3:
                delete_file();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

