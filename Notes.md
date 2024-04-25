# C-Shell

- Shell is a program which interprets user commands through CLI like Terminal. 
- Shell does three main things in its lifetime: 
    - Initialize: In this step, a shell reads its configuration files. These change aspects of the shell’s behavior.
    - Interpret: Next, the shell reads commands from the terminal line and executes them.
    - Terminate: After the user types “exit” or “logout”, the shell destroys all the child processes and terminates.

- The basic loop of a shell is:
    - Accept > Parse > Execute > Display > Loop

## How shell starts a process?

- There are 2 ways to start a process on Unix:
    - Init process: The init process is the first process that is started when a Unix-like operating system is booted. It is the ancestor of all other processes. It is started by the kernel using a hard-coded filename.
    - fork() system call: The fork() system call will spawn a new child process which is an identical process to the parent except that it has a new system process ID. After forking, both the parent and the child will execute the next instruction following the fork() system call. If you want the child process to execute a different piece of code than the parent, you can use the return value from fork() to distinguish the two cases.

## Shell Builtins

- Shell builtins are commands that are internal to the shell. When you type a command that you think is a shell builtin, the shell looks at the command and if it is a shell builtin, it is executed by the shell itself. If it is not a shell builtin, the shell looks for the command in the directories listed in the PATH environment variable.

## Acknowledgements

A big thank you to [Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) for his comprehensive guide on writing a shell in C, which served as a valuable resource and reference for this project.
