# Generating Perfect Hash Functions with gperf

@brief Guide to generating perfect hash functions using gperf for efficient lookups.

## Overview

This guide explains how to use `gperf` to generate perfect hash functions and lookup tables for efficient keyword lookup in C programs.

## Prerequisites

Before getting started, make sure you have `gperf` installed on your system. You can install it using the package manager of your operating system or by downloading and compiling it from source.

## Usage

### 1. Prepare Keyword List

Create a text file containing the list of keywords (or data type names) for which you want to generate the perfect hash function. Each keyword should be on a separate line.

Example (`data_type_keywords.txt`):

```
int
char
float
double
short
long
long long
unsigned int
unsigned char
unsigned short
unsigned long
unsigned long long
```

### 2. Generate Perfect Hash Function

Run `gperf` on the keyword list file to generate the perfect hash function and associated lookup table. Here's the command:

```bash
gperf -L C -t -N getSizeOfDataType -K name -H hash_function data_type_keywords.txt > data_type_mappings.c
```

Explanation of options:

- `-L C`: Specifies the language to use (C).
- `-t`: Tells `gperf` to produce a C function table.
- `-N getSizeOfDataType`: Specifies the name of the lookup function.
- `-K name`: Specifies the key field in the input file (data type names).
- `-H hash_function`: Specifies the hash function to use.
- `data_type_keywords.txt`: Input file containing the list of data type names.
- `data_type_mappings.c`: Output C file containing the generated code.

### 3. Include Generated Code

Include the generated C code (`data_type_mappings.c`) in your project. This code contains the perfect hash function and the lookup table for efficient keyword lookup.

## Example

Here's how you can use the generated perfect hash function and lookup table in your C program:

```c
#include <stdio.h>
#include "data_type_mappings.c"

size_t getSizeOfDataType(const char *data_type) {
    // Use the generated perfect hash function to get the size of the data type
    const struct DataTypeMapping *result = in_word_set(data_type, strlen(data_type));
    if (result) {
        return result->size;
    }
    return 0; // Return 0 if data type is not found
}

int main() {
    printf("Size of int: %zu\n", getSizeOfDataType("int"));
    printf("Size of float: %zu\n", getSizeOfDataType("float"));
    printf("Size of long long: %zu\n", getSizeOfDataType("long long"));
    return 0;
}
```

## Conclusion

By using `gperf` to generate perfect hash functions and lookup tables, you can efficiently perform keyword lookup in your C programs, improving performance compared to linear search algorithms.
