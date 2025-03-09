#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

void save_processes_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("Failed to take process snapshot.\n");
        fclose(file);
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    // Write process details to the file.
    if (Process32First(hProcessSnap, &pe32)) {
        fprintf(file, "PID\tProcess Name\n");
        fprintf(file, "---------------------\n");
        do {
            fprintf(file, "%u\t%s\n", pe32.th32ProcessID, pe32.szExeFile);
        } while (Process32Next(hProcessSnap, &pe32));
    }

    fclose(file);
    CloseHandle(hProcessSnap);
    printf("Processes saved to %s\n", filename);
}