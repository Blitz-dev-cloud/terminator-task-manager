#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <stdio.h>

void list_running_processes() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    PROCESS_MEMORY_COUNTERS pmc;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("Failed to take process snapshot.\n");
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    // Retrieve information about the first process.
    if (Process32First(hProcessSnap, &pe32) == FALSE) {
        printf("Failed to get the first process.\n");
        CloseHandle(hProcessSnap);
        return;
    }

    printf("PID\tProcess Name\t\tMemory Usage (KB)\n");
    printf("----------------------------------------------\n");
    do {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
        if (hProcess != NULL) {
            if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                printf("%u\t%-20s\t%lu\n", pe32.th32ProcessID, pe32.szExeFile, pmc.WorkingSetSize / 1024); // Memory usage in KB
            } else {
                printf("%u\t%-20s\tError getting memory info\n", pe32.th32ProcessID, pe32.szExeFile);
            }
            CloseHandle(hProcess);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}