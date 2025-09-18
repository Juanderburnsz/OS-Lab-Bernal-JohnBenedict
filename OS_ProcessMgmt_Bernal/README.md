# 

# ---

# 

# \## Notes on results

# \### Task A

# \- Parent PID: `<fill parent PID printed here>`

# \- Child PID: `<fill child PID printed here>`

# \- Explanation: child was spawned and exited normally with code `0`.

# 

# \### Task B

# \- Parent PID: `<...>`

# \- Child PIDs: `<...>, <...>`

# \- Explanation: parent spawns two children in parallel. When a child was force-terminated using `Stop-Process`, the parent reported a non-zero exit code for that child.

# 

# \### Task C

# \- Behavior: parent spawns `cmd /c dir`, waits for it. Parent prints child exit code and then terminates with the same code (simulate exec()). 

# 

# \### Task D

* # Behavior: The parent created a child process, but instead of running its original code, the child was replaced by another program (child\_echo.exe) using exec(). The parent continued running, but the child’s behavior was replaced. This confirmed how exec() substitutes the child process image.



# 

# 

