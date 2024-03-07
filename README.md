# **Minishell**

Minishell is a C-based shell program designed to offer a user-friendly command-line interface with a variety of features. Developed as part of the 42 School curriculum, this project strictly adheres to specific guidelines, including the use of the Norm and various coding standards.

## **Project Overview**

### **Features**

- **Prompt Display:** Displaying a prompt when waiting for a new command.
- **Working History:** Implementing a working history for previously entered commands.
- **Executable Launch:** Searching and launching the right executable based on the PATH variable or using a relative or absolute path.
- **Global Variable Usage:** Avoiding the use of more than one global variable to indicate a received signal.
- **Quote Handling:** Not interpreting unclosed quotes or special characters unnecessary for the project.
- **Quote Specifics:** Handling single and double quotes, preventing the shell from interpreting metacharacters in the quoted sequence.
- **Redirections:** Implementing redirections, including input (<), output (>), append (>>), and heredoc (<<).
- **Pipes:** Implementing pipes (|) for connecting the output of one command to the input of the next.
- **Environment Variables:** Handling environment variables ($) and expanding them to their values.
- **Exit Status Expansion:** Handling $? to expand to the exit status of the most recently executed foreground pipeline.
- **Signal Handling:** Handling ctrl-C, ctrl-D, and ctrl-\ in interactive mode.
- **Built-in Commands:** echo, cd, pwd, export, unset, env, and exit.

### **Usage**
To build the Minishell program, use the provided Makefile:

`make`

This will compile the source files with the necessary flags. You can then run the Minishell executable.

`./minishell`
