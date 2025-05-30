# Task 03 README

## Contents

### 1. **mypwdv1.c**
   - **Description:** This program (`mypwdv1.c`) prints the current working directory using the `getcwd` function and a fixed-size buffer.
   - **Usage:** Execute the program without any command-line arguments.
   - **Command:**
     ```bash
     ./mypwdv1
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     #include <unistd.h>
     
     /**< Buffer to store the current working directory */
     char buf[100];
     
     /**< Pointer to store the return value of getcwd */
     char *ret_add = NULL;
     
     int main(int argc, char **argv) {
         /**< Check if the program is called with no command-line arguments */
         if (argc != 1) {
             /**< Print a usage message */
             printf("Usage: %s only, no args needed\n", argv[0]);
             return -1;
         }
     
         /**< Get the current working directory and store it in the buffer */
         ret_add = getcwd(buf, sizeof(buf));
     
         /**< Check if getcwd failed */
         if (ret_add == NULL) {
             /**< Print an error message */
             perror("getcwd");
             return -1;
         }
     
         /**< Print the current working directory */
         printf("%s\n", ret_add);
     
         /**< Return success */
         return 0;
     }
     ```

### 2. **mypwdv2.c**
   - **Description:** This program (`mypwdv2.c`) prints the current working directory using the `getcwd` function and dynamic memory allocation.
   - **Usage:** Execute the program without any command-line arguments.
   - **Command:**
     ```bash
     ./mypwdv2
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     #include <stdlib.h>
     #include <unistd.h>
     
     int main(int argc, char **argv) {
         /**< Buffer to store the current working directory */
         char *buf = NULL;
     
         /**< Pointer to store the return value of getcwd */
         char *ret_add = NULL;
        
         /**< Check if the program is called with no command-line arguments */
         if (argc != 1) {
             /**< Print a usage message */
             printf("Usage: %s only, no args needed\n", argv[0]);
             return -1;
         }
     
         /**< Determine the required buffer size for the current working directory */
         long size = pathconf(".", _PC_PATH_MAX);
     
         /**< Allocate memory for the buffer based on the determined size */
         if ((buf = (char *)malloc((size_t)size)) != NULL) {
             /**< Get the current working directory and store it in the buffer */
             ret_add = getcwd(buf, (size_t)size);
     
             /**< Check if getcwd failed */
             if (ret_add == NULL) {
                 /**< Print an error message and free the allocated memory */
                 perror("getcwd");
                 free(buf);
                 return -1;
             }
     
             /**< Print the current working directory */
             printf("%s\n", ret_add);
     
             /**< Free the allocated memory */
             free(buf);
         } else {
             /**< Print an error message if memory allocation fails */
             perror("malloc");
             return -1;
         }
     
         return 0;
     }
     ```

### 3. **my_echo.c**
   - **Description:** This program (`my_echo.c`) echoes the command-line arguments, separating them with spaces.
   - **Usage:** Provide any number of arguments to echo.
   - **Command:**
     ```bash
     ./my_echo arg1 arg2 arg3
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     
     int main(int argc, char **argv) {
         /**< Iterate through the command-line arguments starting from index 1 */
         for (int i = 1; i < argc; i++) {
             /**< Print each command-line argument followed by a space */
             printf("%s ", argv[i]);
         }
     
         /**< Print a newline character to separate the output */
         printf("\n");
     
         /**< Return 0 to indicate successful execution */
         return 0;
     }
     ```

### 4. **my_mv.c**
   - **Description:** This program (`my_mv.c`) moves a file or directory from a source to a destination.
   - **Usage:** Provide source and destination paths as command-line arguments.
   - **Command:**
     ```bash
     ./my_mv source_path destination_path
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     #include <stdlib.h>
     
     int main(int argc, char *argv[]) {
         /**< Check the number of arguments */
         if (argc != 3) {
             /**< Print usage message and return -1 */
             printf("Usage: %s <src> <dest>\n", argv[0]);
             return -1;
         }
     
         /**< Extract source and destination paths from command-line arguments */
         const char *src = argv[1];
         const char *dest = argv[2];
     
         /**< Perform the move operation */
         if (rename(src, dest) != 0) {
            

         /**< Handle move operation failure */
             perror("Error moving file");
             return -1;
         }
     
         /**< Return success status */
         return 0;
     }
     ```

### 5. **commands.h / commands.c:**
   - **commands.h:** Header file containing function prototypes for command execution (`echo`, `pwd`, `cd`).
   - **commands.c:** Implementation file for command execution functions.

   - **Source Code:**

     ### commands.h

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

     ### commands.c
     ```c
     #include <stdio.h>
     #include <stdlib.h>
     #include <unistd.h>
     #include "commands.h"
     
     /**
      * @brief Execute the echo command.
      * @param args The arguments for the echo command.
      */
     void echo(char *args[]) {
         /**< Print each argument separated by a space */ 
         for (int i = 0; args[i] != NULL; i++) {
             printf("%s ", args[i]);
         }
         printf("\n");
     }
     
     /**
      * @brief Execute the pwd command.
      */
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
     
     /**
      * @brief Execute the cd command.
      * @param path The path to change the current working directory to.
      */
     void cd(char *path) {
         /**< Change the current working directory */ 
         if (chdir(path) != 0) {
             perror("chdir");
         }
     }
     ```
   
### 6. **fsh.h / fsh.c:**
   - **fsh.h:** Header file for Femto Shell containing the function prototype for command execution.
   - **fsh.c:** Implementation file for Femto Shell.
    
   - **Source Code:**

     ### fsh.h

     ```c
     #ifndef FSH_H
     #define FSH_H
     
     /**
      * @brief Function to execute the command based on the input.
      *
      * This function searches for the command in the sorted array of supported     commands
      * and executes the corresponding function if the command is found.
      *
      * @param command The command to be executed.
      * @param args An array of command arguments.
      */
     void executeCommand(char *command, char *args[]);
     
     #endif /**< FSH_H */ 
     ```

     ### fsh.c

     ```c
     #include <stdio.h>
     #include <stdlib.h>
     #include <string.h>
     #include "commands.h"  /**< Include the commands header */ 
     #include "fsh.h" /**< Include the Femto Shell (fsh) header */
     
     #define COMMAND_COUNT 4  /**< Number of supported commands */ 
     
     /**< Array of supported commands */ 
     char *supportedCommands[COMMAND_COUNT] = {"echo", "pwd", "cd", "exit"};
     
     int main(int argc, char **argv) {
         char inputBuffer[100];
     
         while (1) {
             /**< Prompt user to enter a command */ 
             printf("Enter a command: ");
             fgets(inputBuffer, sizeof(inputBuffer), stdin);
     
             /**< Remove the trailing newline character from the input */ 
             inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
     
             /**< Split the input into command and arguments */ 
             char *command = strtok(inputBuffer, " ");
             char *args[10];
             int i = 0;
             while (i < 10 && (args[i] = strtok(NULL, " ")) != NULL) {
                 i++;
             }
             
             /**< Execute the command */ 
             executeCommand(command, args);
         }
     
         return 0;
     }
     
     /**< Function to execute the command based on the input */ 
     void executeCommand(char *command, char *args[]) {
         if (strcmp(command, "pwd") == 0) {
             pwd();
         } else if (strcmp(command, "echo") == 0) {
             echo(args);
         } else if (strcmp(command, "cd") == 0) {
             if (args[0] != NULL) {
                 cd(args[0]);
             } else {
                 printf("cd: missing argument\n");
             }
         } else if (strcmp(command, "exit") == 0) {
             printf("Goodbye :)\n");
             exit(0);
         } else {
             printf("%s: command not found\n", command);
         }
     }
     ```

**Note:** Ensure executable permissions for each program before running.

**Building Instructions:**
- For each program, compile the source code using the `gcc` compiler:
  ```bash
  gcc -o mypwdv1 mypwdv1.c --save-temps
  gcc -o mypwdv2 mypwdv2.c --save-temps
  gcc -o my_echo my_echo.c --save-temps
  gcc -o my_mv my_mv.c --save-temps
  ```

- For the Femto Shell:

  ```bash
  gcc -o fsh main.c fsh.c commands.c -std=c99 --save-temps
  ```