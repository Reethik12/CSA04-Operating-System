#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char mainDirectory[] = "C:/Users/itssk/OneDrive/Desktop";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char filePath[200];
    char mainDirPath[200];

    // Construct full directory path
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s/", mainDirectory, subDirectory);

    // Construct full file path
    snprintf(filePath, sizeof(filePath), "%s%s", mainDirPath, fileName);

    // Create the file
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }

    // Write content to file
    fprintf(file, "This is an example file content.");
    fclose(file);

    printf("File created successfully: %s\n", filePath);

    return 0;
}

