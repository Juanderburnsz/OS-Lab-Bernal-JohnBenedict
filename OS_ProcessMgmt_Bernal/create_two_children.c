#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si[2];
    PROCESS_INFORMATION pi[2];
    DWORD parentPID = GetCurrentProcessId();

    printf("Parent Process: PID = %lu\n", (unsigned long)parentPID);

    // Create 2 children
    for (int i = 0; i < 2; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));

        char cmd[256];
        sprintf(cmd, "child_echo.exe %lu", (unsigned long)parentPID);

        if (!CreateProcess(
                NULL,        // Application name
                cmd,         // Command line
                NULL,        // Process security attributes
                NULL,        // Thread security attributes
                FALSE,       // Inherit handles
                0,           // Creation flags
                NULL,        // Use parent environment
                NULL,        // Use parent current directory
                &si[i],      // Startup info
                &pi[i])) {   // Process info
            printf("CreateProcess failed (%lu).\n", GetLastError());
            return 1;
        }
    }

    // Wait for both children to finish
    HANDLE handles[2] = {pi[0].hProcess, pi[1].hProcess};
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    // Get exit codes
    for (int i = 0; i < 2; i++) {
        DWORD exitCode;
        GetExitCodeProcess(pi[i].hProcess, &exitCode);
        printf("Child %d exit code: %lu\n", i + 1, (unsigned long)exitCode);

        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}
