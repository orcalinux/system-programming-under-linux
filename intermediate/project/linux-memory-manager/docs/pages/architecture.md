# Architecture Overview

@brief Overview of the Linux Memory Manager architecture and design.

## Table of Contents

- [Architecture Overview](#architecture-overview)
  - [Table of Contents](#table-of-contents)
  - [System Architecture](#system-architecture)
  - [Architecture Layers](#architecture-layers)
  - [Core Components](#core-components)
    - [Page Family System](#page-family-system)
    - [Virtual Memory Pages](#virtual-memory-pages)
    - [Page Layout](#page-layout)
    - [Memory Model](#memory-model)
    - [Block Metadata](#block-metadata)
  - [GLThread Design](#glthread-design)
  - [Memory Allocation Flow](#memory-allocation-flow)
    - [Allocation Process](#allocation-process)
    - [Deallocation Process](#deallocation-process)
  - [Optimizations](#optimizations)
    - [Priority Free Lists](#priority-free-lists)
    - [Block Merging](#block-merging)
    - [Page Recycling](#page-recycling)
  - [Thread Safety Considerations](#thread-safety-considerations)
  - [Performance Characteristics](#performance-characteristics)
  - [Memory Layout](#memory-layout)
  - [Future Enhancements](#future-enhancements)
  - [Related Documentation](#related-documentation)

---

## System Architecture

The Linux Memory Manager is designed with a layered architecture that provides efficient memory management while maintaining simplicity and clarity.

---

## Architecture Layers

\image html ../assets/images/heap.png "Architecture Layers"

---

## Core Components

### Page Family System

Each registered data type gets its own **page family**:

- Manages a set of 4KB virtual memory pages.
- Each page is divided into fixed-size blocks for the registered structure.
- Tracks free and used blocks within its pages.
- Optimizes for minimal fragmentation by managing blocks of a single size.

**Structure:**

```c
typedef struct vm_page_family {
    char struct_name[MM_MAX_STRUCT_NAME];
    uint32_t struct_size;
    glthread_t free_block_priority_list_head;
    vm_page_for_families_t *first_page;
} vm_page_family_t;
```

### Virtual Memory Pages

Pages are the basic unit of memory allocated from the kernel via `mmap()`.

```c
typedef struct vm_page {
    struct vm_page *next;
    struct vm_page *prev;
    struct vm_page_family *pg_family;
    uint32_t block_size;
    char page_memory[0]; // Flexible array member for the start of the page's memory
} vm_page_t;
```

### Page Layout

A single 4KB page is structured as follows:

\image html ../assets/images/Page_Layout_Layered.svg "Page Layout (4KB)"

---

### Memory Model

The internal relationship between the kernel memory, virtual memory pages, and blocks is as follows:

\image html ../assets/images/Memory_Model.svg "Memory Model"

---

### Block Metadata

Each block of memory within a page is preceded by a metadata structure that tracks its state.

```c
typedef struct block_meta_data {
    bool is_free;
    uint32_t block_size;
    uint32_t offset;
    glthread_t priority_thread_glue;
    struct vm_page* vm_page;
} block_meta_data_t;
```

---

## GLThread Design

GLThread is an **intrusive linked list**. This means the list node is embedded directly within the data structure it belongs to, rather than being stored separately.

**Advantages:**

- **Zero allocation overhead:** No extra memory allocations are needed for list nodes.
- **Cache-friendly:** The list node and the data are in the same memory block, improving cache locality.
- **Type-safe conversion:** Macros provide a safe way to get the containing structure from a list node pointer.
- **No pointer indirection:** Accessing the data from the node is a simple offset calculation, not a pointer lookup.

**Example:**

```c
typedef struct {
    int data;
    glthread_t list_node; // Embedded node
} MyStruct;

// Add to list
MyStruct obj;
init_glthread(&obj.list_node);
glthread_add_next(&list_head, &obj.list_node);

// Traverse list
GLTHREAD_FOREACH(&list_head, node) {
    MyStruct *s = GLTHREAD_TO_STRUCT(node, MyStruct, list_node);
    // Use s->data
}
```

---

## Memory Allocation Flow

The process of allocating and deallocating memory is central to the manager's design.

### Allocation Process

The following diagram illustrates the flow when `XCALLOC` is called:

\image html ../assets/images/XCALLOC_Allocation_Flow.svg "XCALLOC Allocation Flow"

**Steps:**

1. **Application calls `XCALLOC`:**

   ```c
   Employee *emp = XCALLOC(1, Employee);
   ```

2. **Find Page Family:** The manager looks up the page family registered for the `Employee` struct.
3. **Check for Free Block:** It checks the `free_block_priority_list` for an available block.
4. **Two Paths:**

   - **✓ If a free block exists:**

     - The block is removed from the free list.
     - Its metadata is updated to mark it as `used`.
     - A pointer to the data portion of the block is returned to the application.

   - **✗ If no free block exists:**

     - A new 4KB page is requested from the kernel using `mmap()`.
     - The new page is initialized and divided into blocks of the appropriate size.
     - The first block is returned to the user, and the rest are added to the free list.

---

### Deallocation Process

1. **Application calls `XFREE`:**

   ```c
   XFREE(emp);
   ```

2. **Find Block Metadata:** The manager calculates the address of the block's metadata from the given pointer.
3. **Mark as Free:** The block's `is_free` flag is set to `true`.
4. **Add to Free List:** The block is added back to the page family's priority free list.
5. **Merge Blocks:** The manager attempts to merge the newly freed block with adjacent free blocks to form a larger contiguous block.
6. **Return Page to Kernel:** If a page becomes completely empty (all its blocks are free and merged into one), it can be returned to the kernel using `munmap()` to reduce the process's memory footprint.

---

## Optimizations

### Priority Free Lists

- Free blocks are kept in a priority-ordered list, with the largest blocks first.
- Reduces fragmentation and improves allocation speed.

### Block Merging

- Adjacent free blocks are merged into one larger block when possible.
- Reduces fragmentation and increases allocation success rate for larger structures.

### Page Recycling

- Completely free pages are unmapped using `munmap()`.
- Keeps memory footprint dynamic and efficient.

---

## Thread Safety Considerations

**Current Implementation:**

- GLThread operations are thread-safe.
- Memory allocation (`XCALLOC`, `XFREE`) is not thread-safe.

**Recommendations for multi-threaded use:**

- Use a mutex for global synchronization.
- Create per-thread page families or memory managers.
- Apply fine-grained locking at the page-family level for concurrency.

---

## Performance Characteristics

| Operation            | Time Complexity | Notes                               |
| -------------------- | --------------- | ----------------------------------- |
| `XCALLOC`            | O(1) amortized  | O(n) when a new page is required.   |
| `XFREE`              | O(1)            | Constant time to free a block.      |
| Priority List Insert | O(log n)        | Uses binary insertion for ordering. |
| Block Merge          | O(1)            | Only checks adjacent blocks.        |
| Page Allocation      | O(1)            | `mmap` system call.                 |

---

## Memory Layout

**Typical Memory Usage Example:**

- **Structure size:** 64 bytes
- **Page size:** 4KB (4096 bytes)

| Component             | Size            | Calculation                      |
| --------------------- | --------------- | -------------------------------- |
| **Page Overhead**     | ~ **128 bytes** | `vm_page_t` metadata             |
| **Block Overhead**    | ~ **32 bytes**  | Per block metadata               |
| **Usable Space**      | **3968 bytes**  | `4096 - 128 = 3968`              |
| **Block Size**        | **96 bytes**    | `64 + 32 = 96` (data + metadata) |
| **Blocks per Page**   | **41 blocks**   | `3968 / 96 ≈ 41`                 |
| **Memory Efficiency** | **64%**         | `(41 × 64) / 4096 ≈ 64%`         |

---

## Future Enhancements

Potential improvements for future versions include:

1. Thread-safe allocator (lock-free or per-thread pools).
2. Memory compaction for defragmentation.
3. Allocation profiling and statistics collection.
4. Configurable VM page sizes.
5. Memory quotas per page family.

---

## Related Documentation

- [API Reference](api_reference.md)
- [Developer Guide](developer_guide.md)
- [User Guide](user_guide.md)
