# Minishell

The **Minishell** project is a journey into the core of shell development. The goal is to create a minimalistic, functional shell, mimicking the behavior of Bash, while adhering to strict requirements for stability and memory management. This project is an excellent opportunity to deepen your understanding of processes, file descriptors, and inter-process communication. <br>
This project is also an excellent introduction to teamwork. With the size and functionality the program is supposed to have, communication and proper splitting of tasks is important.

---

## Functionality

The **Minishell** program provides the basic functionality of a shell:

1. **Interactive Command Prompt**: 
   - Displays a prompt and waits for user input.
   - Executes commands entered by the user.

2. **Command Execution**:
   - Searches and runs executables using the `$PATH` environment variable or relative/absolute paths.
   - Implements pipes (`|`) to connect commands.
   - Implements lists of commands (with the '&&' and '||' operators) to execute miltiple pipelines sequentially.

3. **Redirections**:
    - `<`: Redirects input from a file.
    - `>`: Redirects output to a file.
    - `>>`: Appends output to a file.
    - `<<`: Reads input until a given delimiter is encountered.

4. **Signal Handling**:
   - Reacts to `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` like Bash:
     - `Ctrl-C`: Cancels the current command and displays a new prompt.
     - `Ctrl-D`: Exits the shell.
     - `Ctrl-\`: Does nothing in interactive mode.

5. **Environment Variable Management**:
   - Expands `$VARIABLE` to its value.
   - Supports `$?` to retrieve the exit status of the last executed command.
   - Supports wildcard '*' expansion in current directory and subdirectories.

6. **Quote Handling**:
   - Single quotes (`'`) prevent interpretation of meta-characters.
   - Double quotes (`"`) allow expansion of variables but prevent interpretation of other meta-characters.

7. **Built-in Commands**:
   - `echo`: Prints text, with support for the `-n` flag.
   - `cd`: Changes the current directory.
   - `pwd`: Prints the current working directory.
   - `export`: Sets environment variables.
   - `unset`: Removes environment variables.
   - `env`: Displays the current environment variables.
   - `exit`: Exits the shell.
