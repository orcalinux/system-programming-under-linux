# User Guide

@brief User guide for integrating and using the Linux Memory Manager library.

## Introduction for Users

This guide is for developers who want to **use** the Linux Memory Manager library in their applications. If you want to understand the internal implementation or contribute to the project, see the [Developer Guide](developer_guide.md) instead.

---

## Installation

### Installing from Source

1. **Clone the repository:**

   ```sh
   git clone https://github.com/orcalinux/linux-memory-manager.git
   cd linux-memory-manager
   ```

2. **Build the libraries:**

   ```sh
   make all
   ```

3. **Install (optional):**
   ```sh
   sudo cp lib/libhmm.so /usr/local/lib/
   sudo cp lib/libhmm.a /usr/local/lib/
   sudo cp include/*.h /usr/local/include/hmm/
   sudo ldconfig
   ```

### Verify Installation

Test that the library works:

```sh
./bin/hmm
```

---

## Integration Guide

### Static Linking

Include the header and link with the static library:

```c
#include <hmm/memory_manager_api.h>

int main() {
    mm_init();
    // Your code here
    return 0;
}
```

Compile with:

```sh
gcc -o myapp myapp.c -I/usr/local/include -L/usr/local/lib -lhmm
```

### Dynamic Linking

Same code, but link dynamically:

```sh
gcc -o myapp myapp.c -I/usr/local/include -L/usr/local/lib -lhmm
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
./myapp
```

---

## Basic Usage

### Initialize Memory Manager

Before using any memory allocation functions, initialize the memory manager:

```c
#include <hmm/memory_manager_api.h>

int main() {
    // Initialize the memory manager
    mm_init();

    // Your application code

    return 0;
}
```

### Register Data Types

Register your custom data types with the memory manager:

```c
typedef struct {
    int id;
    char name[64];
    float salary;
} Employee;

// Register the Employee structure
MM_REG_STRUCT(Employee);
```

### Allocate Memory

Allocate memory for your registered types:

```c
// Allocate a single Employee
Employee *emp = XCALLOC(1, Employee);

// Allocate array of 10 Employees
Employee *team = XCALLOC(10, Employee);

// Use the allocated memory
emp->id = 1001;
strcpy(emp->name, "John Doe");
emp->salary = 75000.0f;
```

### Free Memory

Free allocated memory when done:

```c
// Free single object
XFREE(emp);

// Free array
XFREE(team);
```

---

## Advanced Usage

### Memory Statistics

Monitor memory usage in your application:

```c
// Print memory usage for a specific structure family
mm_print_memory_usage(Employee);

// Print usage for all registered structures
mm_print_registered_page_families();
```

### Custom Allocation Strategies

For specific use cases, you can control allocation:

```c
// Register a structure family with custom page size
mm_instantiate_new_page_family(
    "Employee", // Structure name
    sizeof(Employee) // Structure size
);

// Allocate from specific family
Employee *emp = mm_allocate_free_data_block(
    lookup_page_family_by_name("Employee")
);
```

---

## Complete Examples

### Simple Application

```c
#include <stdio.h>
#include <string.h>
#include <hmm/memory_manager_api.h>

typedef struct {
    int id;
    char name[32];
} Student;

MM_REG_STRUCT(Student);

int main() {
    // Initialize memory manager
    mm_init();

    // Allocate students
    Student *student1 = XCALLOC(1, Student);
    student1->id = 101;
    strcpy(student1->name, "Alice");

    Student *student2 = XCALLOC(1, Student);
    student2->id = 102;
    strcpy(student2->name, "Bob");

    // Print memory statistics
    printf("Memory Statistics:\n");
    mm_print_memory_usage(Student);

    // Clean up
    XFREE(student1);
    XFREE(student2);

    return 0;
}
```

### Advanced Application

```c
#include <stdio.h>
#include <hmm/memory_manager_api.h>

typedef struct {
    int id;
    char data[100];
} Record;

MM_REG_STRUCT(Record);

int main() {
    mm_init();

    // Allocate large array
    const int NUM_RECORDS = 1000;
    Record *records = XCALLOC(NUM_RECORDS, Record);

    // Initialize records
    for (int i = 0; i < NUM_RECORDS; i++) {
        records[i].id = i;
        snprintf(records[i].data, 100, "Record #%d", i);
    }

    // Check memory fragmentation
    printf("Total Memory Usage:\n");
    mm_print_registered_page_families();

    // Free memory
    XFREE(records);

    return 0;
}
```

---

## Best Practices

### Always Initialize

Always call mm_init() before any memory operations:

```c
int main() {
    mm_init(); // First thing in main
    // Rest of your code
}
```

### Register Before Use

Register all custom types before allocating them:

```c
MM_REG_STRUCT(MyStruct); // Register first

MyStruct *ptr = XCALLOC(1, MyStruct); // Then allocate
```

### Match Allocations and Frees

Always free what you allocate:

```c
void* ptr = XCALLOC(1, MyType);
// Use ptr
XFREE(ptr); // Always free
```

### Check for NULL

Always check allocation results:

```c
MyType *ptr = XCALLOC(1, MyType);
if (ptr == NULL) {
    fprintf(stderr, "Allocation failed!\n");
    return -1;
}
```

---

## Troubleshooting

### Compilation Issues

**Problem:** Linker errors about undefined references

**Solution:** Make sure you're linking with the library:

```sh
gcc myapp.c -lhmm -L./lib
```

**Problem:** Cannot find header files

**Solution:** Specify include path:

```sh
gcc myapp.c -I./include -lhmm
```

### Runtime Issues

**Problem:** Segmentation fault

**Solution:**

- Did you call mm_init()?
- Did you register your structure with MM_REG_STRUCT()?
- Are you freeing memory twice?

**Problem:** Memory leaks

**Solution:** Use mm_print_memory_usage() to track allocations and ensure all XCALLOC() calls have matching XFREE() calls.

---

## Next Steps

- See the complete [API Reference](api_reference.md) for all available functions
- Check the [Integration Guide](integration_guide.md) for build system integration
- Read about [GLThreads Guide](glthreads_guide.md) for thread-safe data structures
- For internal details, see the [Architecture Overview](architecture.md)
