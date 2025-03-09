#include <windows.h>
#include <stdio.h>

void terminate_process(DWORD pid) {
    HANDLE hProcess;

    // Open the process with TERMINATE access.
    hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to open process with PID %u.\n", pid);
        return;
    }

    // Terminate the process.
    if (TerminateProcess(hProcess, 0) == FALSE) {
        printf("Failed to terminate process with PID %u.\n", pid);
    } else {
        printf("Successfully terminated process with PID %u.\n", pid);
    }

    CloseHandle(hProcess);
}