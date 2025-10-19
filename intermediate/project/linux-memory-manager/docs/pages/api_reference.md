# API Reference

@brief Complete API reference for the Linux Memory Manager library.

## Table of Contents

- [API Reference](#api-reference)
  - [Table of Contents](#table-of-contents)
  - [API Overview](#api-overview)
  - [Initialization](#initialization)
    - [mm_init()](#mm_init)
  - [Memory Allocation](#memory-allocation)
    - [XCALLOC()](#xcalloc)
    - [XFREE()](#xfree)
  - [Type Registration](#type-registration)
    - [MM_REG_STRUCT()](#mm_reg_struct)
    - [mm_instantiate_new_page_family()](#mm_instantiate_new_page_family)
  - [Memory Statistics](#memory-statistics)
    - [mm_print_memory_usage()](#mm_print_memory_usage)
    - [mm_print_registered_page_families()](#mm_print_registered_page_families)
    - [mm_print_vm_page_details()](#mm_print_vm_page_details)
  - [GLThread API](#glthread-api)
    - [init_glthread()](#init_glthread)
    - [glthread_add_next()](#glthread_add_next)
    - [remove_glthread()](#remove_glthread)
    - [GLTHREAD_TO_STRUCT()](#glthread_to_struct)
  - [Advanced Functions](#advanced-functions)
    - [lookup_page_family_by_name()](#lookup_page_family_by_name)
    - [mm_allocate_free_data_block()](#mm_allocate_free_data_block)
    - [mm_free_blocks()](#mm_free_blocks)
  - [Constants and Macros](#constants-and-macros)
  - [Error Handling](#error-handling)
  - [Thread Safety](#thread-safety)
  - [Usage Examples](#usage-examples)

## API Overview

The Linux Memory Manager provides a simple, efficient API for custom memory management. All public functions are defined in `memory_manager_api.h`.

---

## Initialization

### mm_init()

Initialize the memory manager. Must be called before any other operations.

**Declaration:**

```c
void mm_init(void);
```

**Usage:**

```c
int main() {
    mm_init(); // First call
    // Rest of code
}
```

---

## Memory Allocation

### XCALLOC()

Allocate memory for a specific type.

**Declaration:**

```c
#define XCALLOC(units, struct_name)
```

**Parameters:**

- `units` - Number of elements to allocate
- `struct_name` - Type name (must be registered)

**Returns:** Pointer to allocated memory, or NULL on failure

**Example:**

```c
typedef struct {
    int id;
    char name[32];
} Employee;

MM_REG_STRUCT(Employee);

Employee *emp = XCALLOC(1, Employee); // Single object
Employee *team = XCALLOC(10, Employee); // Array of 10
```

### XFREE()

Free previously allocated memory.

**Declaration:**

```c
#define XFREE(ptr)
```

**Parameters:**

- `ptr` - Pointer to memory to free

**Example:**

```c
Employee *emp = XCALLOC(1, Employee);
// Use emp
XFREE(emp);
```

---

## Type Registration

### MM_REG_STRUCT()

Register a structure type with the memory manager.

**Declaration:**

```c
#define MM_REG_STRUCT(struct_name)
```

**Parameters:**

- `struct_name` - Name of the structure to register

**Example:**

```c
typedef struct {
    int x, y;
} Point;

MM_REG_STRUCT(Point); // Must be called before XCALLOC
```

### mm_instantiate_new_page_family()

Manually create a page family for a structure.

**Declaration:**

```c
void mm_instantiate_new_page_family(
    const char *struct_name,
    uint32_t struct_size
);
```

**Parameters:**

- `struct_name` - Name of the structure
- `struct_size` - Size in bytes

**Example:**

```c
mm_instantiate_new_page_family("Point", sizeof(Point));
```

---

## Memory Statistics

### mm_print_memory_usage()

Print memory usage statistics for a specific type.

**Declaration:**

```c
#define mm_print_memory_usage(struct_name)
```

**Parameters:**

- `struct_name` - Structure type to report

**Example:**

```c
mm_print_memory_usage(Employee);
```

**Output:**

```
Page Family: Employee | Size: 72 bytes
=======================================
Total VM Pages: 1
Total Blocks: 56
Used Blocks: 3
Free Blocks: 53
```

### mm_print_registered_page_families()

Print statistics for all registered types.

**Declaration:**

```c
void mm_print_registered_page_families(void);
```

**Example:**

```c
mm_print_registered_page_families();
```

### mm_print_vm_page_details()

Print detailed information about a specific memory page.

**Declaration:**

```c
void mm_print_vm_page_details(vm_page_t *vm_page);
```

---

## GLThread API

GLThread provides a generic, thread-safe intrusive linked list.

### init_glthread()

Initialize a GLThread node.

**Declaration:**

```c
void init_glthread(glthread_t *glthread);
```

### glthread_add_next()

Add a node after another node.

**Declaration:**

```c
void glthread_add_next(
    glthread_t *base_glthread,
    glthread_t *new_glthread
);
```

### remove_glthread()

Remove a node from the list.

**Declaration:**

```c
void remove_glthread(glthread_t *glthread);
```

### GLTHREAD_TO_STRUCT()

Convert GLThread node pointer to structure pointer.

**Declaration:**

```c
#define GLTHREAD_TO_STRUCT(fn_name, structure_name, field_name, glthreadptr)
```

**Example:**

```c
typedef struct {
    int data;
    glthread_t list_node;
} MyStruct;

GLTHREAD_TO_STRUCT(get_my_struct, MyStruct, list_node, glthread_ptr)

MyStruct *s = get_my_struct(node_ptr);
```

---

## Advanced Functions

### lookup_page_family_by_name()

Find a registered page family by name.

**Declaration:**

```c
vm_page_family_t* lookup_page_family_by_name(const char *struct_name);
```

### mm_allocate_free_data_block()

Allocate a single block from a page family.

**Declaration:**

```c
void* mm_allocate_free_data_block(vm_page_family_t *vm_page_family);
```

### mm_free_blocks()

Free a previously allocated block.

**Declaration:**

```c
void mm_free_blocks(void *app_data);
```

---

## Constants and Macros

| Constant                                  | Value | Description                  |
| ----------------------------------------- | ----- | ---------------------------- |
| `SYSTEM_PAGE_SIZE`                        | 4096  | Size of VM page in bytes     |
| `MM_MAX_STRUCT_NAME`                      | 32    | Max length of structure name |
| `OFFSET_OF(type, field)`                  | -     | Get byte offset of field     |
| `MM_GET_PAGE_FROM_META_BLOCK(block_meta)` | -     | Get page from block metadata |

---

## Error Handling

Most functions return NULL on failure. Always check return values:

```c
Employee *emp = XCALLOC(1, Employee);
if (emp == NULL) {
    fprintf(stderr, "Allocation failed\n");
    return -1;
}
```

---

## Thread Safety

- GLThread operations are thread-safe
- Memory allocation functions are NOT thread-safe by default
- For multi-threaded applications, use external synchronization

```c
pthread_mutex_t mem_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&mem_lock);
Employee *emp = XCALLOC(1, Employee);
pthread_mutex_unlock(&mem_lock);
```

---

## Usage Examples

See complete examples in:

- [User Guide](user_guide.md)
- [Simple Example](#example_simple)
- [Advanced Example](#example_advanced)
