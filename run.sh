#!/bin/bash

# Compile the C-Shell code
gcc -o cshell cshell.c

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running C-Shell..."
    # Run the compiled executable
    ./cshell
else
    echo "Compilation failed. Exiting..."
fi
