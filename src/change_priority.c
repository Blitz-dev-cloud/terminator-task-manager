#include <windows.h>
#include <stdio.h>

void change_process_priority(DWORD pid, DWORD priority) {
    HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to open process with PID %u.\n", pid);
        return;
    }

    if (SetPriorityClass(hProcess, priority)) {
        printf("Successfully changed the priority of PID %u.\n", pid);
    } else {
        printf("Failed to change the priority of PID %u.\n", pid);
    }

    CloseHandle(hProcess);
}