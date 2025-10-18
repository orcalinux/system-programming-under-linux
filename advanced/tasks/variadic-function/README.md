# Variadic Functions in C

Variadic functions are a powerful feature in C that allow you to create functions capable of handling a variable number of arguments. This capability makes your code more flexible and adaptable to different situations.

## Table of Contents

- [Variadic Functions in C](#variadic-functions-in-c)
  - [Table of Contents](#table-of-contents)
  - [Introduction to Variadic Functions](#introduction-to-variadic-functions)
    - [How Variadic Functions Work](#how-variadic-functions-work)
    - [Common Use Cases](#common-use-cases)
  - [Basic Examples](#basic-examples)
    - [Example 1: Simple Sum Function](#example-1-simple-sum-function)
    - [Example 2: Printing Arguments](#example-2-printing-arguments)
    - [Example 3: Finding Maximum Value](#example-3-finding-maximum-value)
    - [Example 4: Finding Minimum Value](#example-4-finding-minimum-value)
    - [Example 5: Concatenating Strings](#example-5-concatenating-strings)
  - [Intermediate Examples](#intermediate-examples)
    - [Example 6: Logging Messages](#example-6-logging-messages)
    - [Example 7: Formatting Strings](#example-7-formatting-strings)
    - [Example 8: Flexible Array Sum](#example-8-flexible-array-sum)
    - [Example 9: Calculating Average](#example-9-calculating-average)
    - [Example 10: Checking Data Types](#example-10-checking-data-types)
  - [Advanced Examples](#advanced-examples)
    - [Example 11: Dynamic SQL Query Builder](#example-11-dynamic-sql-query-builder)
    - [Example 12: Configurable Command Processor](#example-12-configurable-command-processor)
    - [Example 13: Parsing Complex Input](#example-13-parsing-complex-input)
    - [Example 14: Dynamic Memory Allocation](#example-14-dynamic-memory-allocation)
    - [Example 15: Multi-Type Data Processing](#example-15-multi-type-data-processing)
    - [Example 16: Custom Data Structure Handling](#example-16-custom-data-structure-handling)
    - [Example 17: Flexible Error Handling](#example-17-flexible-error-handling)
    - [Example 18: Implementing a Dispatcher](#example-18-implementing-a-dispatcher)
    - [Example 19: Multi-Threaded Logging System](#example-19-multi-threaded-logging-system)
    - [Example 20: Building a Complex Mathematical Expression](#example-20-building-a-complex-mathematical-expression)
  - [Best Practices](#best-practices)
  - [Conclusion](#conclusion)
  - [Further Reading](#further-reading)

## Introduction to Variadic Functions

### How Variadic Functions Work

A variadic function is a function that accepts a variable number of arguments. This is achieved by including an ellipsis (`...`) in the function's declaration. The most common example of a variadic function is `printf`, which can accept a varying number of arguments based on the format string.

To handle these arguments, variadic functions use a set of macros provided by the `<stdarg.h>` header file:

- **`va_list`**: A type that holds the information needed to retrieve additional arguments.
- **`va_start`**: Initializes a `va_list` variable to start retrieving arguments.
- **`va_arg`**: Retrieves the next argument in the list.
- **`va_end`**: Cleans up the `va_list` variable after all arguments have been processed.

### Common Use Cases

- **Logging and Debugging**: Variadic functions allow the creation of flexible logging systems where you can pass a variable number of messages or data points.
- **Data Processing**: Functions that process arrays, lists, or sets of data can use variadic functions to handle different amounts of input data.
- **Custom Implementations of Standard Functions**: For example, implementing your own version of `printf`, `scanf`, etc.

## Basic Examples

### Example 1: Simple Sum Function

This example demonstrates how to sum a variable number of integers:

```c
#include <stdarg.h>
#include <stdio.h>

void sum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;

    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }

    va_end(args);
    printf("Sum: %d\n", total);
}

int main() {
    sum(3, 1, 2, 3); // Output: Sum: 6
    sum(5, 10, 20, 30, 40, 50); // Output: Sum: 150
    return 0;
}
```

### Example 2: Printing Arguments

A variadic function that prints each argument:

```c
#include <stdarg.h>
#include <stdio.h>

void print_args(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int arg = va_arg(args, int);
        printf("Argument %d: %d\n", i + 1, arg);
    }

    va_end(args);
}

int main() {
    print_args(3, 10, 20, 30);
    return 0;
}
```

### Example 3: Finding Maximum Value

This function finds the maximum value among the arguments:

```c
#include <stdarg.h>
#include <stdio.h>

int find_max(int count, ...) {
    va_list args;
    va_start(args, count);
    int max = va_arg(args, int);

    for (int i = 1; i < count; i++) {
        int value = va_arg(args, int);
        if (value > max) {
            max = value;
        }
    }

    va_end(args);
    return max;
}

int main() {
    printf("Max: %d\n", find_max(4, 10, 20, 5, 15)); // Output: Max: 20
    return 0;
}
```

### Example 4: Finding Minimum Value

Similar to finding the maximum, this function finds the minimum value:

```c
#include <stdarg.h>
#include <stdio.h>

int find_min(int count, ...) {
    va_list args;
    va_start(args, count);
    int min = va_arg(args, int);

    for (int i = 1; i < count; i++) {
        int value = va_arg(args, int);
        if (value < min) {
            min = value;
        }
    }

    va_end(args);
    return min;
}

int main() {
    printf("Min: %d\n", find_min(4, 10, 20, 5, 15)); // Output: Min: 5
    return 0;
}
```

### Example 5: Concatenating Strings

This function concatenates multiple strings into a single string:

```c
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void concat_strings(char *result, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        strcat(result, va_arg(args, char *));
    }

    va_end(args);
}

int main() {
    char result[100] = "";
    concat_strings(result, 3, "Hello, ", "World", "!");
    printf("Result: %s\n", result); // Output: Result: Hello, World!
    return 0;
}
```

## Intermediate Examples

### Example 6: Logging Messages

This custom logging function can log messages with varying arguments:

```c
#include <stdarg.h>
#include <stdio.h>

void log_message(const char *format, ...) {
    va_list args;
    va_start(args, format);

    printf("LOG: ");
    vprintf(format, args);

    va_end(args);
}

int main() {
    log_message("This is a log message: %d, %s\n", 42, "hello");
    return 0;
}
```

### Example 7: Formatting Strings

A function that formats a string using a format specifier:

```c
#include <stdarg.h>
#include <stdio.h>

void format_string(char *result, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(result, format, args);
    va_end(args);
}

int main() {
    char result[100];
    format_string(result, "Name: %s, Age: %d", "John Doe", 30);
    printf("Formatted String: %s\n", result); // Output: Formatted String: Name: John Doe, Age: 30
    return 0;
}
```

### Example 8: Flexible Array Sum

This function sums an array of integers of any size:

```c
#include <stdarg.h>
#include <stdio.h>

int sum_array(int count, ...) {
    va_list args;
    va_start(args, count);
    int sum = 0;

    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }

    va_end

(args);
    return sum;
}

int main() {
    int result = sum_array(5, 1, 2, 3, 4, 5);
    printf("Sum of array: %d\n", result); // Output: Sum of array: 15
    return 0;
}
```

### Example 9: Calculating Average

This function calculates the average of a set of numbers:

```c
#include <stdarg.h>
#include <stdio.h>

double calculate_average(int count, ...) {
    va_list args;
    va_start(args, count);
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }

    va_end(args);
    return sum / count;
}

int main() {
    double avg = calculate_average(4, 10, 20, 30, 40);
    printf("Average: %.2f\n", avg); // Output: Average: 25.00
    return 0;
}
```

### Example 10: Checking Data Types

This function demonstrates how to handle multiple data types using variadic functions:

```c
#include <stdarg.h>
#include <stdio.h>

void print_values(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char type = va_arg(args, int); // Retrieve the type specifier
        if (type == 'i') {
            int val = va_arg(args, int);
            printf("Integer: %d\n", val);
        } else if (type == 'f') {
            double val = va_arg(args, double);
            printf("Float: %f\n", val);
        } else if (type == 'c') {
            char val = (char)va_arg(args, int); // char is promoted to int
            printf("Char: %c\n", val);
        } else {
            printf("Unknown type\n");
        }
    }

    va_end(args);
}

int main() {
    print_values(3, 'i', 42, 'f', 3.14, 'c', 'A');
    return 0;
}
```

## Advanced Examples

### Example 11: Dynamic SQL Query Builder

This function builds a dynamic SQL query using variadic arguments:

```c
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void build_query(char *query, const char *table, int count, ...) {
    va_list args;
    va_start(args, count);

    strcpy(query, "SELECT * FROM ");
    strcat(query, table);
    strcat(query, " WHERE ");

    for (int i = 0; i < count; i++) {
        const char *column = va_arg(args, const char *);
        const char *value = va_arg(args, const char *);

        strcat(query, column);
        strcat(query, " = '");
        strcat(query, value);
        strcat(query, "'");

        if (i < count - 1) {
            strcat(query, " AND ");
        }
    }

    va_end(args);
}

int main() {
    char query[256];
    build_query(query, "users", 2, "name", "John Doe", "age", "30");
    printf("SQL Query: %s\n", query); // Output: SQL Query: SELECT * FROM users WHERE name = 'John Doe' AND age = '30'
    return 0;
}
```

### Example 12: Configurable Command Processor

A function that processes commands with a variable number of arguments:

```c
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void process_command(const char *command, int count, ...) {
    va_list args;
    va_start(args, count);

    printf("Processing command: %s\n", command);
    for (int i = 0; i < count; i++) {
        char *arg = va_arg(args, char *);
        printf("Argument %d: %s\n", i + 1, arg);
    }

    va_end(args);
}

int main() {
    process_command("COPY", 2, "file1.txt", "file2.txt");
    process_command("MOVE", 3, "file1.txt", "file2.txt", "file3.txt");
    return 0;
}
```

### Example 13: Parsing Complex Input

This example demonstrates how to parse complex input using variadic functions:

```c
#include <stdarg.h>
#include <stdio.h>

void parse_input(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == 'd') {
            int i = va_arg(args, int);
            printf("Integer: %d\n", i);
        } else if (*format == 'c') {
            int c = va_arg(args, int); // char is promoted to int
            printf("Char: %c\n", c);
        } else if (*format == 'f') {
            double d = va_arg(args, double);
            printf("Float: %f\n", d);
        }
        ++format;
    }

    va_end(args);
}

int main() {
    parse_input("dcf", 42, 'A', 3.14);
    return 0;
}
```

### Example 14: Dynamic Memory Allocation

A variadic function that allocates memory dynamically based on input types:

```c
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void *allocate_memory(const char *format, ...) {
    va_list args;
    va_start(args, format);
    void *memory = NULL;

    while (*format != '\0') {
        if (*format == 'i') {
            memory = malloc(sizeof(int));
            int value = va_arg(args, int);
            *(int *)memory = value;
            printf("Allocated memory for int: %d\n", *(int *)memory);
        } else if (*format == 'f') {
            memory = malloc(sizeof(double));
            double value = va_arg(args, double);
            *(double *)memory = value;
            printf("Allocated memory for double: %f\n", *(double *)memory);
        }
        ++format;
    }

    va_end(args);
    return memory;
}

int main() {
    int *pInt = (int *)allocate_memory("i", 100);
    double *pDouble = (double *)allocate_memory("f", 3.14);

    free(pInt);
    free(pDouble);

    return 0;
}
```

### Example 15: Multi-Type Data Processing

This function processes different types of data passed as arguments:

```c
#include <stdarg.h>
#include <stdio.h>

void process_data(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char type = va_arg(args, int); // Retrieve the type specifier
        if (type == 'i') {
            int val = va_arg(args, int);
            printf("Processing integer: %d\n", val);
        } else if (type == 'f') {
            double val = va_arg(args, double);
            printf("Processing float: %f\n", val);
        } else if (type == 's') {
            char *val = va_arg(args, char *);
            printf("Processing string: %s\n", val);
        }
    }

    va_end(args);
}

int main() {
    process_data(3, 'i', 42, 'f', 3.14, 's', "Hello, World!");
    return 0;
}
```

### Example 16: Custom Data Structure Handling

This example shows how to handle custom data structures:

```c
#include <stdarg.h>
#include <stdio.h>

typedef struct {
    int id;
    char name[50];
} Person;

void print_person_info(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        Person *person = va_arg(args, Person *);
        printf("Person ID: %d, Name: %s\n", person->id, person->name);
    }

    va_end(args);
}

int main() {
    Person p1 = {1, "John Doe"};
    Person p2 = {2, "Jane Smith"};

    print_person_info(2, &p1, &p2);
    return 0;
}
```

### Example 17: Flexible Error Handling

A function that handles errors based on a variable number of error messages:

```c
#include <stdarg.h>
#include <stdio.h>

void handle_errors(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char *error_message = va_arg(args, char *);
        printf("Error: %s\n", error_message);
    }

    va_end(args);
}

int main() {
    handle_errors(3, "File not found", "Memory allocation failed", "Invalid input");
    return 0;
}
```

### Example 18: Implementing a Dispatcher

A function dispatcher that calls different functions based on the command:

```c
#include <stdarg.h>
#include <stdio.h>

void command_dispatcher(const char *command, ...) {
    va_list args;
    va_start(args, command);

    if (strcmp(command, "PRINT") == 0) {
        char *message = va_arg(args, char *);
        printf("PRINT: %s

\n", message);
    } else if (strcmp(command, "SUM") == 0) {
        int a = va_arg(args, int);
        int b = va_arg(args, int);
        printf("SUM: %d\n", a + b);
    } else {
        printf("Unknown command: %s\n", command);
    }

    va_end(args);
}

int main() {
    command_dispatcher("PRINT", "Hello, World!");
    command_dispatcher("SUM", 10, 20);
    return 0;
}
```

### Example 19: Multi-Threaded Logging System

A more complex example of logging in a multi-threaded environment:

```c
#include <stdarg.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

void thread_safe_log(const char *format, ...) {
    va_list args;
    va_start(args, format);

    pthread_mutex_lock(&log_mutex);
    vprintf(format, args);
    pthread_mutex_unlock(&log_mutex);

    va_end(args);
}

void *thread_function(void *arg) {
    thread_safe_log("Thread %d: %s\n", (int)arg, "Logging from thread");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function, (void *)1);
    pthread_create(&thread2, NULL, thread_function, (void *)2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
```

### Example 20: Building a Complex Mathematical Expression

This advanced example demonstrates how to build and evaluate a complex mathematical expression:

```c
#include <stdarg.h>
#include <stdio.h>

double evaluate_expression(int count, ...) {
    va_list args;
    va_start(args, count);
    double result = 0;

    for (int i = 0; i < count; i++) {
        char op = va_arg(args, int); // Operation
        double value = va_arg(args, double); // Value

        if (op == '+') {
            result += value;
        } else if (op == '-') {
            result -= value;
        } else if (op == '*') {
            result *= value;
        } else if (op == '/') {
            result /= value;
        }
    }

    va_end(args);
    return result;
}

int main() {
    double result = evaluate_expression(5, '+', 10.0, '*', 3.0, '-', 5.0, '/', 2.0);
    printf("Result: %.2f\n", result); // Output: Result: 25.00
    return 0;
}
```

## Best Practices

- **Type Safety**: Always be mindful of the types of arguments when using `va_arg`. Incorrect types can lead to undefined behavior.
- **Documentation**: Clearly document the expected argument types and order.
- **Error Handling**: Implement error checks to handle invalid or unexpected arguments gracefully.
- **Avoid Overuse**: Use variadic functions when necessary, but avoid them if a fixed argument function would be clearer or more maintainable.

## Conclusion

Variadic functions in C provide powerful flexibility for handling functions that require a variable number of arguments. From basic summation functions to complex command processors and mathematical expression evaluators, variadic functions enable you to write more dynamic and reusable code.

## Further Reading

- [C Standard Library: `stdarg.h`](https://en.cppreference.com/w/c/variadic)
- [Variadic Functions in C - GeeksforGeeks](https://www.geeksforgeeks.org/variadic-functions-in-c/)
- [Understanding `printf` Internals](https://www.cprogramming.com/tutorial/printf-format-strings.html)
