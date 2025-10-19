# Developer Guide

@brief Developer guide for understanding and contributing to the Linux Memory Manager.

## Introduction for Developers

This guide is for developers who want to **understand**, **modify**, or **contribute** to the Linux Memory Manager project. If you just want to use the library, see the [User Guide](user_guide.md) instead.

---

## Development Setup

### Requirements

- **GCC 7.0+** - C compiler with C11 support
- **GNU Make** - Build automation
- **Git** - Version control
- **Doxygen 1.9+** - Documentation generation (optional)
- **Graphviz** - Diagram generation (optional)
- **Valgrind** - Memory leak detection (optional)

### Clone Repository

```sh
git clone https://github.com/orcalinux/linux-memory-manager.git
cd linux-memory-manager
```

### Build Everything

```sh
# Build all targets
make all

# Or build individually
make static # Build static library only
make shared # Build shared library only
```

---

## Architecture Overview

### Core Components

The memory manager consists of several key components:

1. **VM Page Manager** (memory_manager.c)

   - Manages virtual memory pages from the kernel
   - Implements page families for different data types
   - Handles page allocation and deallocation

2. **Block Allocator** (memory_manager.c)

   - Divides pages into fixed-size blocks
   - Maintains free block lists
   - Implements block splitting and merging

3. **GLThread** (glthread.c)

   - Generic intrusive linked list
   - Thread-safe operations
   - Zero-overhead abstraction

4. **Type Registry** (datatype_size_lookup.c)
   - Maps type names to sizes
   - Enables dynamic type registration
   - Used by XCALLOC/XFREE macros

### Memory Model

\image html ../assets/images/Memory_Model.svg "Memory Model"

---

## Code Organization

### File Organization

```
src/
├── memory_manager.c           # Core memory management
├── glthread.c                 # Linked list implementation
├── datatype_size_lookup.c     # Type size registry
├── parse_datatype.c           # Type name parsing
└── memory_manager_test.c      # Test suite

include/
├── memory_manager_api.h       # Public API (users include this)
├── memory_manager.h           # Internal structures
├── glthread.h                 # GLThread API
├── datatype_size_lookup.h     # Type registry API
├── parse_datatype.h           # Parser API
└── colors.h                   # Terminal output utilities
```

### Header Dependencies

\image html ../assets/images/Header_Dependencies.svg "Header Dependencies"

## Building & Testing

### Makefile Targets

| Target           | Description                      |
| ---------------- | -------------------------------- |
| `make all`       | Build executable and libraries   |
| `make static`    | Build static library (libhmm.a)  |
| `make shared`    | Build shared library (libhmm.so) |
| `make clean_all` | Remove all build artifacts       |
| `make clean_obj` | Remove object files only         |
| `make doc`       | Generate Doxygen documentation   |
| `make clean_doc` | Remove generated documentation   |

### Testing

**Run the test suite:**

```sh
./bin/hmm
```

**Run with Valgrind (detect memory leaks):**

```sh
valgrind --leak-check=full --show-leak-kinds=all ./bin/hmm
```

**Run with AddressSanitizer:**

```sh
gcc -fsanitize=address -g src/*.c -o bin/hmm_asan
./bin/hmm_asan
```

---

## Contributing

### Contribution Workflow

1. **Fork the repository** on GitHub

2. **Create a feature branch:**

   ```sh
   git checkout -b feature/my-new-feature
   ```

3. **Make your changes** and commit:

   ```sh
   git add .
   git commit -m "Add new feature: description"
   ```

4. **Push to your fork:**

   ```sh
   git push origin feature/my-new-feature
   ```

5. **Open a Pull Request** on GitHub

### Coding Guidelines

**Style Rules:**

- Use 4 spaces for indentation (no tabs)
- Maximum line length: 80 characters
- Use snake_case for functions and variables
- Use UPPER_CASE for macros and constants
- Add Doxygen comments for all public functions

**Example:**

```c
/**
 * @brief Allocate a block of memory
 *
 * @param size Size in bytes to allocate
 * @return Pointer to allocated memory, or NULL on failure
 */
void* mm_allocate(size_t size) {
    // Implementation
}
```

### Commit Messages

Follow this format:

```
<type>: <subject>

<body>

<footer>
```

**Types:**

- `feat:` New feature
- `fix:` Bug fix
- `docs:` Documentation changes
- `refactor:` Code refactoring
- `test:` Adding tests
- `chore:` Maintenance tasks

**Example:**

```text
feat: Add memory fragmentation analysis

Implement mm_get_fragmentation_ratio() to analyze internal
fragmentation across all page families.

Closes #42
```

---

## Debugging

### Build with Debug Symbols

```sh
gcc -g -O0 src/*.c -o bin/hmm_debug
gdb bin/hmm_debug
```

### Memory Debugging

**Enable verbose output:**

```c
#define MM_DEBUG 1
```

**Print memory state:**

```c
mm_print_registered_page_families();
mm_print_memory_usage(MyStruct);
mm_print_vm_page_details();
```

---

## Advanced Topics

### Understanding GLThread

GLThread is an intrusive linked list implementation. Each structure contains the list node:

```c
typedef struct {
    int data;
    glthread_t list_node;  // Intrusive list node
} MyStruct;

// Convert from list node to structure
MyStruct *s = GLTHREAD_TO_STRUCT(node, MyStruct, list_node);
```

### Page Families

Each data type gets its own "page family":

- Pages are allocated from the kernel
- Each page is divided into fixed-size blocks
- Free blocks are tracked in a priority list

### Block Metadata

Each allocated block has metadata:

```c
typedef struct {
    bool is_free;
    uint32_t block_size;
    uint32_t offset;
    glthread_t priority_thread_glue;
    struct vm_page* *vm_page;
} block_meta_data_t;
```

---

## Extending the Library

### Custom Allocators

You can implement custom allocation strategies:

```c
void* my_custom_alloc(size_t size) {
    // Custom allocation logic
    return mm_allocate_free_data_block(family);
}
```

### Memory Hooks

Add callbacks for allocation/deallocation events:

```c
void on_alloc(void *ptr, size_t size) {
    printf("Allocated %zu bytes at %p\n", size, ptr);
}
```

---

## Resources

- [API Reference](api_reference.md) - Complete function documentation
- [Architecture](architecture.md) - System design details
- [Testing Guide](user_guide.md) - How to write and run tests
- [GitHub Repository](https://github.com/orcalinux/linux-memory-manager)
- [Issue Tracker](https://github.com/orcalinux/linux-memory-manager/issues)
