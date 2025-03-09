#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Include Windows API for DWORD and priority classes

// Function declarations
void list_running_processes();
void terminate_process(DWORD pid);
void change_process_priority(DWORD pid, DWORD priority);
void save_processes_to_file(const char* filename);

void display_menu() {
    printf("\n=== Enhanced Task Manager ===\n");
    printf("1. List Running Processes\n");
    printf("2. Terminate a Process\n");
    printf("3. Change Process Priority\n");
    printf("4. Save Process List to File\n");
    printf("5. Exit\n");
}

int main() {
    int choice;
    DWORD pid;  // Now recognized since <windows.h> is included
    int priorityChoice;

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_running_processes();
                break;
            case 2:
                printf("Enter the PID of the process you want to terminate: ");
                scanf("%lu", &pid);
                terminate_process(pid);
                break;
            case 3:
                printf("Enter the PID of the process to change priority: ");
                scanf("%lu", &pid);
                printf("Choose priority (1: IDLE_PRIORITY_CLASS, 2: BELOW_NORMAL_PRIORITY_CLASS, 3: NORMAL_PRIORITY_CLASS, 4: ABOVE_NORMAL_PRIORITY_CLASS, 5: HIGH_PRIORITY_CLASS): ");
                scanf("%d", &priorityChoice);
                switch (priorityChoice) {
                    case 1: change_process_priority(pid, IDLE_PRIORITY_CLASS); break;
                    case 2: change_process_priority(pid, BELOW_NORMAL_PRIORITY_CLASS); break;
                    case 3: change_process_priority(pid, NORMAL_PRIORITY_CLASS); break;
                    case 4: change_process_priority(pid, ABOVE_NORMAL_PRIORITY_CLASS); break;
                    case 5: change_process_priority(pid, HIGH_PRIORITY_CLASS); break;
                    default: printf("Invalid priority choice!\n"); break;
                }
                break;
            case 4:
                save_processes_to_file("process_list.txt");
                break;
            case 5:
                printf("Exiting Enhanced Task Manager.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}