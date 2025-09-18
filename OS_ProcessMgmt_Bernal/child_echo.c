// child_echo.c
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    DWORD pid = GetCurrentProcessId();
    DWORD ppid = (argc > 1) ? (DWORD)atoi(argv[1]) : 0;

    printf("Child process started. PID = %lu, Parent PID = %lu\n",
           (unsigned long)pid, (unsigned long)ppid);
    fflush(stdout);            // ensures the line is printed immediately

    // stay alive long enough for you to inspect/kill it
    Sleep(30000);              // 30 seconds (increase if you need more time)

    printf("Child process exiting. PID = %lu\n", (unsigned long)pid);
    return 0;
}
