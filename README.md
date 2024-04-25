# C-Shell

C-Shell is a simple Unix-like shell implementation written in C. 

## Features

- Command execution: Execute external commands and built-in commands.
- Built-in commands: Supports built-in commands such as `cd`, `mkdir`, `cat`, `help`, and `exit`.
- Input/output redirection: Supports input/output redirection using `<` and `>` operators.
- Signal handling: Gracefully handles signals such as SIGINT (Ctrl+C) and SIGTERM.
- Colorful prompt: Displays a colorful prompt to enhance user experience.

## How to Use

1. Run the shell using the provided `run.sh` script:
```bash
./run.sh
```

2. You will see the C-Shell prompt (`>`). You can type commands and press Enter to execute them.

## Built-in Commands

- `cd`: Change directory.
- `mkdir`: Create a directory.
- `cat`: Display the contents of a file.
- `help`: Display information about the shell and built-in commands.
- `exit`: Exit the shell.

## Input/Output Redirection

C-Shell supports input/output redirection using the `<` and `>` operators. For example:
```bash	
cat  input.txt > output.txt
```

## Signal Handling

C-Shell gracefully handles signals such as SIGINT (Ctrl+C) and SIGTERM. Pressing Ctrl+C will exit the shell.

## Acknowledgements

A big thank you to [Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) for his comprehensive guide on writing a shell in C, which served as a valuable resource and reference for this project.

