# Mastering GDB and GDB Scripts

## Table of Contents

1. [Introduction to GDB](#introduction-to-gdb)
2. [Basic GDB Commands](#basic-gdb-commands)
3. [Advanced GDB Features](#advanced-gdb-features)
4. [GDB Scripting](#gdb-scripting)
5. [GDB Python Scripting](#gdb-python-scripting)
6. [Practical Examples](#practical-examples)
7. [Project Setup](#project-setup)
8. [Applying GDB Commands](#applying-gdb-commands)
9. [Best Practices](#best-practices)
10. [Resources](#resources)

## Introduction to GDB

GDB, the GNU Debugger, allows you to see what is happening inside a program while it runs or what it was doing at the moment it crashed. GDB supports debugging of C, C++, and other languages, and provides various functionalities to control the execution of programs, inspect variables, set breakpoints, and more.

### Installing GDB

On Linux:
```bash
sudo apt-get install gdb  # Debian/Ubuntu
sudo yum install gdb      # CentOS/RHEL
sudo dnf install gdb      # Fedora
```

On macOS:
```bash
brew install gdb
```

## Basic GDB Commands

### Common Commands

- `run (args)`: Starts the program with optional arguments.
- `break (location)`: Sets a breakpoint at the specified location.
- `continue`: Continues execution until the next breakpoint.
- `next`: Executes the next line of code (stepping over function calls).
- `step`: Steps into functions, executing the next line of code.
- `print (variable)`: Prints the value of a variable.
- `info locals`: Displays all local variables in the current stack frame.
- `backtrace`: Shows the call stack.
- `quit`: Exits GDB.

## Advanced GDB Features

### Breakpoints

- **Add a Breakpoint**: 
  ```gdb
  break <location>
  ```
  Example:
  ```gdb
  break main.c:20
  ```

- **Remove a Breakpoint**:
  ```gdb
  delete <breakpoint_number>
  ```
  Example:
  ```gdb
  delete 1
  ```

- **List All Breakpoints**:
  ```gdb
  info breakpoints
  ```

### Stepping Commands

- **Step into a Function**:
  ```gdb
  step
  ```

- **Step over a Function**:
  ```gdb
  next
  ```

### Navigating to a Certain Line or Function

- **Set a Breakpoint at a Specific Line**:
  ```gdb
  break filename:line_number
  ```
  Example:
  ```gdb
  break main.c:20
  ```

- **Set a Breakpoint at a Specific Function**:
  ```gdb
  break function_name
  ```
  Example:
  ```gdb
  break add_book
  ```

- **Jump to a Specific Line**:
  ```gdb
  jump filename:line_number
  ```
  Example:
  ```gdb
  jump main.c:20
  ```

- **Jump to a Specific Function**:
  ```gdb
  jump function_name
  ```
  Example:
  ```gdb
  jump add_book
  ```

## GDB Scripting

GDB scripting allows you to automate repetitive tasks and extend GDB’s functionality using its built-in command language.

### GDB Command Scripts

Create a file named `gdb_commands.gdb` with GDB commands:
```gdb
break main
run
print library
info locals
backtrace
continue
```

Run GDB with the script:
```bash
gdb -x gdb_commands.gdb ./library_mgmt
```

## GDB Python Scripting

GDB provides a Python API to automate complex tasks. Here’s how to use it:

### Setting Up a GDB Python Script

Create a Python script named `gdb_script.py`:
```python
import gdb

class HelloWorld(gdb.Command):
    """Greet the whole world."""

    def __init__(self):
        super(HelloWorld, self).__init__("hello", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        print("Hello, World!")

HelloWorld()
```

### Running the Python Script in GDB

Load the script in GDB:
```gdb
(gdb) source gdb_script.py
(gdb) hello
```

### Advanced Python Scripting Example

Here’s an advanced example that automatically sets breakpoints at functions that start with `add_`:

Create a Python script named `gdb_auto_break.py`:
```python
import gdb

class AutoBreakpoint(gdb.Command):
    """Automatically set breakpoints for functions starting with 'add_'."""

    def __init__(self):
        super(AutoBreakpoint, self).__init__("auto-break", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        output = gdb.execute("info functions", to_string=True)
        for line in output.splitlines():
            if line.startswith("add_"):
                func_name = line.split()[0]
                gdb.execute(f"break {func_name}")
                print(f"Breakpoint set at {func_name}")

AutoBreakpoint()
```

Load the script in GDB and run the command:
```gdb
(gdb) source gdb_auto_break.py
(gdb) auto-break
```

## Practical Examples

### Example 1: Debugging a Segmentation Fault

1. Compile your program with debugging information:
   ```bash
   gcc -g -o library_mgmt src/main.c src/library.c -Iincludes
   ```

2. Start GDB:
   ```bash
   gdb ./library_mgmt
   ```

3. Run the program:
   ```gdb
   run
   ```

4. When it crashes, use `backtrace` to see the call stack:
   ```gdb
   backtrace
   ```

5. Examine variables and memory to find the cause:
   ```gdb
   print variable_name
   ```

### Example 2: Automating Debugging with Scripts

Create a GDB command script `auto_debug.gdb`:
```gdb
break main
run
info locals
backtrace
```

Run GDB with the script:
```bash
gdb -x auto_debug.gdb ./library_mgmt
```

## Project Setup

Let's create a simple Library Management System project that uses dynamic memory allocation. This project will be used to demonstrate GDB commands and scripting.

### Project Structure

```
project/
│
├── src/
│   ├── main.c
│   ├── library.c
│   └── library.h
├── includes/
│   └── library.h
└── Makefile
```

### Source Code

#### `includes/library.h`

```c
#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct {
    int id;
    char title[100];
    char author[100];
} Book;

typedef struct {
    int id;
    char name[100];
} Member;

typedef struct {
    Book *books;
    int book_count;
    Member *members;
    int member_count;
} Library;

Library *create_library();
void add_book(Library *library, int id, const char *title, const char *author);
void add_member(Library *library, int id, const char *name);
void list_books(const Library *library);
void list_members(const Library *library);
void destroy_library(Library *library);

#endif // LIBRARY_H
```

#### `src/library.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

Library *create_library() {
    Library *library = (Library *)malloc(sizeof(Library));
    if (library) {
        library->books = NULL;
        library->book_count = 0;
        library->members = NULL;
        library->member_count = 0;
    }
    return library;
}

void add_book(Library *library, int id, const char *title, const char *author) {
    library->books = (Book *)realloc(library->books, sizeof(Book) * (library->book_count + 1));
    library->books[library->book_count].id = id;
    strcpy(library->books[library->book_count].title, title);
    strcpy(library->books[library->book_count].author, author);
    library->book_count++;
}

void add_member(Library *library, int id, const char *name) {
    library->members = (Member *)realloc(library->members, sizeof(Member) * (library->member_count + 1));
    library->members[library->member_count].id = id;
    strcpy(library->members[library->member_count].name, name);
    library->member_count++;
}

void list_books(const Library *library) {
    for (int i = 0; i < library->book_count; i++) {
        printf("Book ID: %d, Title: %s, Author: %s\n", library->books[i].id, library->books[i].title, library->books[i].author);
    }
}

void list_members(const Library

 *library) {
    for (int i = 0; i < library->member_count; i++) {
        printf("Member ID: %d, Name: %s\n", library->members[i].id, library->members[i].name);
    }
}

void destroy_library(Library *library) {
    if (library) {
        free(library->books);
        free(library->members);
        free(library);
    }
}
```

#### `src/main.c`

```c
#include <stdio.h>
#include "library.h"

int main() {
    Library *library = create_library();

    add_book(library, 1, "The C Programming Language", "Brian W. Kernighan, Dennis M. Ritchie");
    add_book(library, 2, "Expert C Programming", "Peter van der Linden");

    add_member(library, 1, "Alice");
    add_member(library, 2, "Bob");

    printf("Books in the library:\n");
    list_books(library);

    printf("\nMembers in the library:\n");
    list_members(library);

    destroy_library(library);

    return 0;
}
```

#### `Makefile`

```makefile
CC = gcc
CFLAGS = -g -Iincludes
SRC = src/main.c src/library.c
OBJ = $(SRC:.c=.o)
TARGET = library_mgmt

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
```

## Applying GDB Commands

### Compile the Program

First, compile the program using the Makefile:
```bash
make
```

### Starting GDB

Start GDB with the compiled program:
```bash
gdb ./library_mgmt
```

### Example Commands

#### `run (args)`

Starts the program with optional arguments. In this case, we don't have arguments, so just run:
```gdb
(gdb) run
```

#### `break (location)`

Sets a breakpoint at the specified location, for example, at the beginning of `main`:
```gdb
(gdb) break main
```

#### `continue`

Continues execution until the next breakpoint:
```gdb
(gdb) continue
```

#### `next`

Executes the next line of code (stepping over function calls):
```gdb
(gdb) next
```

#### `step`

Steps into functions, executing the next line of code:
```gdb
(gdb) step
```

#### `print (variable)`

Prints the value of a variable, for example, `library`:
```gdb
(gdb) print library
```

#### `info locals`

Displays all local variables in the current stack frame:
```gdb
(gdb) info locals
```

#### `backtrace`

Shows the call stack:
```gdb
(gdb) backtrace
```

#### `quit`

Exits GDB:
```gdb
(gdb) quit
```

### Listing All Breakpoints

Displays all breakpoints currently set:
```gdb
(gdb) info breakpoints
```

### Removing a Breakpoint

Removes a specific breakpoint by its number:
```gdb
(gdb) delete <breakpoint_number>
```
Example:
```gdb
(gdb) delete 1
```

### Navigating to a Certain Line or Function

- **Set a Breakpoint at a Specific Line**:
  ```gdb
  break filename:line_number
  ```
  Example:
  ```gdb
  break main.c:20
  ```

- **Set a Breakpoint at a Specific Function**:
  ```gdb
  break function_name
  ```
  Example:
  ```gdb
  break add_book
  ```

- **Jump to a Specific Line**:
  ```gdb
  jump filename:line_number
  ```
  Example:
  ```gdb
  jump main.c:20
  ```

- **Jump to a Specific Function**:
  ```gdb
  jump function_name
  ```
  Example:
  ```gdb
  jump add_book
  ```

## GDB Scripting

GDB scripting allows you to automate repetitive tasks and extend GDB’s functionality using its built-in command language.

### GDB Command Scripts

Create a file named `gdb_commands.gdb` with GDB commands:
```gdb
break main
run
print library
info locals
backtrace
continue
```

Run GDB with the script:
```bash
gdb -x gdb_commands.gdb ./library_mgmt
```

## GDB Python Scripting

GDB provides a Python API to automate complex tasks. Here’s how to use it:

### Setting Up a GDB Python Script

Create a Python script named `gdb_script.py`:
```python
import gdb

class HelloWorld(gdb.Command):
    """Greet the whole world."""

    def __init__(self):
        super(HelloWorld, self).__init__("hello", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        print("Hello, World!")

HelloWorld()
```

### Running the Python Script in GDB

Load the script in GDB:
```gdb
(gdb) source gdb_script.py
(gdb) hello
```

### Advanced Python Scripting Example

Here’s an advanced example that automatically sets breakpoints at functions that start with `add_`:

Create a Python script named `gdb_auto_break.py`:
```python
import gdb

class AutoBreakpoint(gdb.Command):
    """Automatically set breakpoints for functions starting with 'add_'."""

    def __init__(self):
        super(AutoBreakpoint, self).__init__("auto-break", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        output = gdb.execute("info functions", to_string=True)
        for line in output.splitlines():
            if line.startswith("add_"):
                func_name = line.split()[0]
                gdb.execute(f"break {func_name}")
                print(f"Breakpoint set at {func_name}")

AutoBreakpoint()
```

Load the script in GDB and run the command:
```gdb
(gdb) source gdb_auto_break.py
(gdb) auto-break
```

## Best Practices

- **Compile with Debug Information**: Always compile your programs with the `-g` flag to include debug information.
- **Use Conditional Breakpoints**: To avoid stopping execution too frequently, use conditions on breakpoints.
- **Script Repetitive Tasks**: Automate repetitive debugging tasks using GDB command scripts or Python scripts.
- **Keep a Cheat Sheet**: Maintain a cheat sheet of commonly used GDB commands for quick reference.
- **Learn by Doing**: Practice debugging real-world programs and gradually explore advanced features and scripting.

## Resources

Here are some valuable resources for further reading and understanding:

1. **Books:**
   - "Expert C Programming: Deep C Secrets" by Peter van der Linden
   - "The C Programming Language" by Brian W. Kernighan and Dennis M. Ritchie

2. **Online Tutorials:**
   - [GDB Documentation](https://www.gnu.org/software/gdb/documentation/)
   - [GDB Cheat Sheet](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)
   - [GDB Tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/)

3. **Courses:**
   - [Debugging C Programs](https://youtube.com/playlist?list=PL9IEJIKnBJjHGWPN_S9NS_Ky1-tC8ZrUI&si=5IcasU46WdLITYzS)
   - [Debug Running Python Processes with GDB](https://www.youtube.com/watch?v=ZqpaKkIjU80)

---

Mastering GDB and GDB scripting can significantly enhance your debugging skills and efficiency. Start with the basics, gradually explore advanced features, and leverage scripting to automate and extend GDB’s capabilities. Continuous practice and learning will help you become proficient in using GDB for complex debugging tasks.
