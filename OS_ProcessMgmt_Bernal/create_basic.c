#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    DWORD parentPID = GetCurrentProcessId();
    printf("Parent Process: PID = %lu\n", (unsigned long)parentPID);

    // Command line: child_echo.exe <parent_pid>
    char cmd[256];
    sprintf(cmd, "child_echo.exe %lu", (unsigned long)parentPID);

    if (!CreateProcess(
            NULL,        // Application name
            cmd,         // Command line
            NULL,        // Process security attributes
            NULL,        // Thread security attributes
            FALSE,       // Inherit handles
            0,           // Creation flags
            NULL,        // Use parent’s environment
            NULL,        // Use parent’s current directory
            &si,         // Startup info
            &pi)) {      // Process info
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get child exit code
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    printf("Child exit code: %lu\n", (unsigned long)exitCode);

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
