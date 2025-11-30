# hw1shell - Simple Shell Implementation

## Overview
hw1shell is a simple command-line shell implementation for Linux that supports both internal commands (like `exit`, `cd`, and `jobs`) and external commands through the use of system calls. This project serves as an educational tool for understanding shell behavior and process management in Unix-like operating systems.

## Features
- **Internal Commands**: 
  - `exit`: Exits the shell.
  - `cd`: Changes the current working directory.
  - `jobs`: Lists background jobs.
- **External Command Execution**: Supports executing external commands using `fork` and `exec`.
- **Background and Foreground Process Management**: Handles processes running in the background and foreground.

## Project Structure
```
hw1shell
├── src
│   ├── main.c        # Entry point of the shell application
│   ├── shell.c       # Main shell functionalities
│   ├── parser.c      # Command parsing
│   ├── builtin.c     # Internal commands implementation
│   ├── jobs.c        # Background job management
│   ├── exec.c        # External command execution
│   └── utils.c       # Utility functions
├── include
│   └── shell.h       # Header file with function declarations
├── tests
│   └── test_hw1shell.sh # Test script for shell functionality
├── examples
│   └── sample_commands.txt # Example commands for testing
├── Makefile          # Build instructions
├── .gitignore        # Files to ignore in version control
└── README.md         # Project documentation
```

## Building the Project
To build the hw1shell project, navigate to the project directory and run the following command:

```bash
make
```

This will compile the source files and create an executable named `hw1shell`.

## Running the Shell
After building the project, you can run the shell by executing:

```bash
./hw1shell
```

## Testing
To test the functionality of hw1shell, you can run the provided test script:

```bash
bash tests/test_hw1shell.sh
```

## Example Commands
Refer to `examples/sample_commands.txt` for a list of example commands that can be executed in hw1shell.

## Contribution
Feel free to contribute to this project by submitting issues or pull requests. Your feedback and contributions are welcome!