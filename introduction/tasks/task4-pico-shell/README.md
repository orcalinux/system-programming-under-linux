# Pico Shell (Psh)

Pico Shell (Psh) is a simple shell program that provides basic shell functionalities such as executing commands, built-in commands (echo, pwd, cd, and exit), and support for external commands. Psh allows users to enter commands, parse them, and execute them accordingly.

## Features

- Built-in commands: echo, pwd, cd, and exit.
- Command-line parsing to parse user input and divide it into arguments.
- Support for executing external commands using fork/exec system calls.
- Dynamic memory allocation to handle varying numbers of arguments.
- Execution of programs using their names directly without the need to enter the full path.

## Files

- `commands.c`: Contains implementations of built-in commands.
- `commands.h`: Header file declaring functions for built-in commands.
- `psh.c`: Main program file containing the shell implementation.
- `psh.h`: Header file declaring functions for the shell program.

## Usage

1. Compile the program:
   ```bash
   gcc psh.c commands.c -o psh
   ```

2. Run the compiled executable:
   ```bash
   ./psh
   ```

3. Enter commands at the prompt and press Enter to execute.

## Implementation Details

### `commands.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "commands.h"

void echo(char *args[]) {
    /**< Print each argument separated by a space */ 
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void pwd() {
    /**< Buffer to store the current working directory */ 
    char buf[100];

    /**< Get the current working directory and print it */ 
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("%s\n", buf);
    } else {
        perror("getcwd");
    }
}

void cd(char *path) {
    /**< Change the current working directory */ 
    if (chdir(path) != 0) {
        perror("chdir");
    }
}
```

### `commands.h`

```c
#ifndef COMMANDS_H
#define COMMANDS_H

/**
 * @brief Execute the echo command.
 * @param args The arguments for the echo command.
 */
void echo(char *args[]);

/**
 * @brief Execute the pwd command.
 */
void pwd();

/**
 * @brief Execute the cd command.
 * @param path The path to change the current directory to.
 */
void cd(char *path);

#endif  /**< COMMANDS_H */ 
```

### `psh.c`

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "psh.h"

int main() {
    char *inputBuffer = NULL; /**< Pointer to store user input */ 
    size_t bufferSize = 0;  /**< Size of the input buffer */

    char **args = NULL; /**< Pointer to store parsed arguments */
    int argCount = 0; /**< Number of parsed arguments */

    while (1) {
        /**< Prompt user to enter a command */ 
        getUserInput(&inputBuffer, &bufferSize);

        /**< Skip processing if input is empty. */
        if (strlen(inputBuffer) == 0) {
            continue;
        }

        /**< Extract the command and arguments */ 
        parseInput(inputBuffer, &args, &argCount);

        /**< Execute the command with the arguments */ 
        int ret_val = executeCommand(args[0], args);
        /**< This Command Not Internal -> External Command */
        if(ret_val != 0) {
            /**< Fork a new process to execute the command. */
            pid_t returned_pid = fork();

            if (returned_pid > 0) { /**< Parent process. */
            int wstatus;

            /**< Wait for the child process to finish. */
            wait(&wstatus);
            } else if (returned_pid == 0) { /**< Child process. */
                /**< Execute the specified command. */
                if (execvp(args[0], args) == -1) {
                    /**< Exec failed. Print an error message and return. */
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            } else {
                /**< Fork failed. Print an error message. */
                printf("ERROR: I could not get a child\n");
            }

        } 
        
        /**< Free the allocated memory for arguments */ 
        for (int i = 0; i < argCount; i++) {
            free(args[i]);
        }
        free(args);

        /**< Free the allocated memory for inputBuffer */ 
        free(inputBuffer);
        inputBuffer = NULL;
        bufferSize = 0;
    }
    
    return 0;
}
```

### `psh.h`

```c
#ifndef PSH_H
#define PSH_H

/**
 * @brief Function to execute the command based on the input.
 *


 * This function searches for the command in the sorted array of supported internal commands
 * and executes the corresponding function if the command is found internally.
 * If the command is not found internally, it is treated as an external command and executed accordingly.
 *
 * @param command The command to be executed.
 * @param args An array of command arguments.
 * 
 * @return 0 if the command is executed successfully as an internal command, -1 if it's an external command.
 */
int executeCommand(char *command, char *args[]);

/**
 * @brief Parse the input string and tokenize it into arguments.
 *
 * This function parses the input string and tokenizes it into arguments based on spaces.
 * It dynamically allocates memory for the array of arguments and individual argument strings.
 *
 * @param input The input string to be parsed.
 * @param args Pointer to a pointer to store the array of arguments.
 * @param argCount Pointer to an integer to store the number of arguments.
 *
 * Example usage:
 * @code{.c}
 * char *inputString = "command arg1 arg2 arg3";
 * char **args = NULL;
 * int argCount = 0;
 * parseInput(inputString, &args, &argCount);
 * /// Use args and argCount to process the parsed arguments...
 * /// Don't forget to free the allocated memory for args...
 * freeArgs(args, argCount);
 * /// Free the allocated memory for arguments 
 * for (int i = 0; i < argCount; i++) {
 *     free(args[i]);
 * }
 * free(args);
 * @endcode
 */
void parseInput(char *input, char ***args, int *argCount);

/**
 * @brief Prompts the user to enter a command and reads the input into a buffer.
 * 
 * @param[in,out] inputBuffer A pointer to a pointer to the buffer where the input will be stored.
 * @param[in,out] bufferSize A pointer to the size of the buffer.
 * 
 * @note The function allocates memory for the input buffer if it's NULL or insufficient.
 * @warning The function exits with failure if `getline` fails to read input.
 * 
 * Example usage:
 * @code{.c}
 * char *inputBuffer = NULL;
 * size_t bufferSize = 0;
 * getUserInput(&inputBuffer, &bufferSize);
 * /// Use inputBuffer to process user input...
 * /// Don't forget to free the allocated memory for inputBuffer...
 * free(inputBuffer);
 * @endcode
 */
void getUserInput(char **inputBuffer, size_t *bufferSize);

#endif /**< PSH_H */
```
