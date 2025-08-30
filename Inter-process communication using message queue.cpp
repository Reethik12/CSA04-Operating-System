#include <stdio.h>
#include <windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"

int main() {
    HANDLE hPipe;
    char buffer[100];
    DWORD bytesWritten, bytesRead;

    // Create a named pipe
    hPipe = CreateNamedPipe(
        PIPE_NAME,             // pipe name
        PIPE_ACCESS_DUPLEX,    // read/write access
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,                     // max instances
        1024,                  // output buffer size
        1024,                  // input buffer size
        0,                     // default timeout
        NULL                   // default security attributes
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error creating pipe. Error code: %d\n", GetLastError());
        return 1;
    }

    printf("Waiting for client to connect...\n");
    BOOL connected = ConnectNamedPipe(hPipe, NULL) || GetLastError() == ERROR_PIPE_CONNECTED;
    if (!connected) {
        printf("Failed to connect to pipe. Error code: %d\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    // Producer: send a message
    const char* msg = "Hello, Windows Named Pipe!";
    WriteFile(hPipe, msg, (DWORD)strlen(msg) + 1, &bytesWritten, NULL);
    printf("Producer: Data sent: %s\n", msg);

    // Consumer: read the message
    ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL);
    printf("Consumer: Data received: %s\n", buffer);

    // Close the pipe
    CloseHandle(hPipe);
    return 0;
}

