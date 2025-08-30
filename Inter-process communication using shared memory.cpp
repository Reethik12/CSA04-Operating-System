#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    const char* msg = "Hello, shared memory!";
    
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, "MySharedMemory");
    
    if (hMapFile == NULL) {
        cout << "Could not create file mapping." << endl;
        return 1;
    }
    
    LPVOID pBuf = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
    if (pBuf == NULL) {
        cout << "Could not map view of file." << endl;
        CloseHandle(hMapFile);
        return 1;
    }
    
    CopyMemory((PCHAR)pBuf, msg, strlen(msg) + 1);
    cout << "Data written to shared memory: " << msg << endl;
    
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}

