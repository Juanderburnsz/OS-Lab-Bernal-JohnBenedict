#include <windows.h>
#include <stdio.h>

int main(void) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command to run: "cmd /c dir"
    char cmd[] = "cmd /c dir";

    printf("Parent process PID = %lu\n", GetCurrentProcessId());

    // Create the new process
    if (!CreateProcess(
            NULL,        // Application name (NULL because we’re using command line)
            cmd,         // Command line
            NULL,        // Process handle not inheritable
            NULL,        // Thread handle not inheritable
            FALSE,       // Set handle inheritance to FALSE
            0,           // No creation flags
            NULL,        // Use parent's environment block
            NULL,        // Use parent's starting directory 
            &si,         // Pointer to STARTUPINFO structure
            &pi)         // Pointer to PROCESS_INFORMATION structure
    ) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for the child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    printf("Child exited with code: %lu\n", exitCode);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Simulate "exec": parent exits with the same exit code
    return exitCode;
}
