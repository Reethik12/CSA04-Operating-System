#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <sys/stat.h>

int main() {
    char filename[] = "file.txt";

    // Set read/write permissions for owner
    if (_chmod(filename, _S_IREAD | _S_IWRITE) == 0) {
        printf("File permissions changed successfully.\n");
    } else {
        perror("_chmod");
        return 1;
    }

    return 0;
}

