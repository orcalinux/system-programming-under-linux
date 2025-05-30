# Task 02 README

## Description

This C program prompts the user to enter text until the user types "exit." It removes newline characters from the input, prints the input, and continues the loop until the user enters "exit," displaying "Good Bye :)" before termination.

## C Code (task_02.c)

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    /**< Variable to store the string from the user */
    char str[1000] = {0};

    do {
        /**< Prompt the user to enter something */
        printf("Enter anything > ");

        /**< Read from the stdin using fgets() function */
        fgets(str, sizeof(str), stdin);

        /**< Remove the newline character from the input */
        str[strcspn(str, "\n")] = '\0';

        /**< Check if the input is equal to "exit" */
        if (strcmp(str, "exit") == 0) {
            /**< If so, print a farewell message */
            printf("Good Bye :)\n");
        } else {
            /**< If not, print the input */
            printf("%s\n", str);
        }

    /**< Continue the loop while the input is not equal to "exit" */
    } while (strcmp(str, "exit") != 0);

    return 0;
}
```

## Compilation Commands

1. **Preprocess (Generate Preprocessed Code):**
   ```bash
   gcc task_02.c -E -o task_02.i
   ```
   - The `-E` flag instructs the compiler to stop after the preprocessing stage, producing the preprocessed code. The output is redirected to `task_02.i`.

2. **Compile Assembly Code (Generate Assembly Code):**
   ```bash
   gcc task_02.c -S -o task_02.s
   ```
   - The `-S` flag tells the compiler to stop after generating assembly code. The output is redirected to `task_02.s`.

3. **Compile Object File (Generate Object File):**
   ```bash
   gcc task_02.c -c -o task_02.o
   ```
   - The `-c` flag compiles the source code into an object file (`task_02.o`) without linking.

4. **Final Compilation (Generate Executable):**
   ```bash
   gcc task_02.c -o task_02
   ```
   - This command links the object file and generates the final executable named `task_02`.

## Execution

To run the compiled program:
```bash
./task_02
```

Enter text when prompted and type "exit" to terminate the program.
