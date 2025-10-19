# GLThreads Data Structures Guide

@brief Guide to GLThreads data structures and their usage in low-level programming.

## Introduction

**GLThreads** (Generic Linked Threads) is a powerful programming technique used to manage data structures with enhanced flexibility and memory efficiency. GLThreads allow data structures to embed nodes directly within them, making it possible for a single data structure to participate in multiple linked structures simultaneously.

> 💡 Key Insight: GLThreads is particularly useful in low-level systems programming, where performance and memory efficiency are critical.

---

## Why It's Called GLThreads

The term **GLThreads** or **Generic Linked Threads** originates from the concept of "threads" in the context of linked lists and data structures.

### 🔗 "Thread" Metaphor

Just as a thread in sewing connects fabric pieces, GLThreads create a "thread" of connections linking elements together in a data structure.

### 🔀 "Linked" Component

Embedded nodes connect elements within data structures, allowing participation in multiple linked lists or other structures simultaneously.

### ⚙️ "Generic" Nature

Not limited to any specific type of data structure—applicable to linked lists, queues, trees, and more.

---

## Key Concepts

### Embedded Nodes

Instead of using standalone nodes with pointers to the next and previous elements, GLThreads embed these nodes directly within the data structure. This allows the structure to be part of multiple lists without modification.

**Traditional Node vs. GLThread Node**

**❌ Traditional Approach:**

```
struct Node {
  Data* data;
  Node* next;
  Node* prev;
};
```

_Requires separate allocation_

**✅ GLThread Approach:**

```
struct Data {
  int value;
  glthread_t node;
};
```

_Node embedded in data_

### Offset-Based Navigation

Pointers to next and previous nodes are calculated using offsets within the containing structure. This allows for flexible management of data structures.

```c
#define OFFSET_OF(type, member) ((size_t)&(((type *)0)->member))
#define GLTHREAD_TO_STRUCT(ptr, type, member) \
 (type *)((char *)(ptr) - OFFSET_OF(type, member))
```

### Multiple List Participation

A single data structure can participate in multiple lists, queues, or other linked structures simultaneously, enabling more complex relationships between data elements.

\image html ../assets/images/Multiple_List_Participation.svg "Multiple List Participation"

---

## Advantages

### 💾 Memory Efficiency

By embedding nodes within the data structure, GLThreads reduce memory overhead by avoiding separate allocations for each node.

### 🔄 Flexibility

The same data structure can be linked into multiple lists or queues without needing to modify its definition.

### ⚡ Cache Performance

Since nodes are embedded within a structure that is often accessed together, cache locality is improved.

---

---

## Use Cases

| Domain                      | Application                                                             | Benefit                                                 |
| --------------------------- | ----------------------------------------------------------------------- | ------------------------------------------------------- |
| **Operating Systems**       | Managing processes or tasks in different queues (run queue, wait queue) | Single process can be in multiple queues simultaneously |
| **Embedded Systems**        | Efficiently managing resources with minimal overhead                    | Reduced memory footprint and allocation overhead        |
| **Complex Data Management** | Data structures participating in multiple lists                         | Flexible relationships without data duplication         |

---

## Implementation Examples

### Linked List with GLThreads

```c
#include <stddef.h>
#include <stdio.h>

typedef struct glthread_node {
struct glthread_node *prev;
struct glthread_node *next;
} glthread_node_t;

typedef struct {
char name[32];
int id;
glthread_node_t glnode;
} employee_t;

#define OFFSET_OF(type, member) ((size_t)&(((type *)0)->member))
#define GLTHREAD_TO_STRUCT(ptr, type, member) \
 (type *)((char *)(ptr) - OFFSET_OF(type, member))

void glthread_add_next(glthread_node_t *base_node, glthread_node_t *new_node) {
new_node->prev = base_node;
new_node->next = base_node->next;
if (base_node->next) {
base_node->next->prev = new_node;
}
base_node->next = new_node;
}

void init_glthread(glthread_node_t *glnode) {
glnode->prev = NULL;
glnode->next = NULL;
}

int main() {
employee_t e1 = {.name = "Alice", .id = 1};
employee_t e2 = {.name = "Bob", .id = 2};

    init_glthread(&e1.glnode);
    init_glthread(&e2.glnode);

    glthread_add_next(&e1.glnode, &e2.glnode);

    // Traverse list
    glthread_node_t *current = &e1.glnode;
    while (current) {
        employee_t *emp = GLTHREAD_TO_STRUCT(current, employee_t, glnode);
        printf("Employee: %s (ID: %d)\n", emp->name, emp->id);
        current = current->next;
    }

    return 0;

}
```

> ✅ Output:

```
Employee: Alice (ID: 1)
Employee: Bob (ID: 2)
```

### Queue with GLThreads

```c
typedef struct glthread_queue {
glthread_node_t *head;
glthread_node_t *tail;
} glthread_queue_t;

void queue_init(glthread_queue_t *queue) {
queue->head = NULL;
queue->tail = NULL;
}

void queue_enqueue(glthread_queue_t *queue, glthread_node_t *node) {
node->next = NULL;
node->prev = queue->tail;

    if (queue->tail) {
        queue->tail->next = node;
    } else {
        queue->head = node;
    }
    queue->tail = node;

}

glthread_node_t* queue_dequeue(glthread_queue_t *queue) {
if (!queue->head) return NULL;

    glthread_node_t *node = queue->head;
    queue->head = node->next;

    if (queue->head) {
        queue->head->prev = NULL;
    } else {
        queue->tail = NULL;
    }

    node->next = node->prev = NULL;
    return node;

}
```

### Binary Tree with GLThreads

> 🌲 Tree Structure: For binary trees, use two GLThread nodes—one for left child, one for right child.

```c
typedef struct tree_node {
int value;
glthread_node_t left_child;
glthread_node_t right_child;
} tree_node_t;

void tree_init(tree_node_t *node, int value) {
node->value = value;
init_glthread(&node->left_child);
init_glthread(&node->right_child);
}

void tree_add_left(tree_node_t *parent, tree_node_t *child) {
parent->left_child.next = &child->left_child;
child->left_child.prev = &parent->left_child;
}

void tree_add_right(tree_node_t *parent, tree_node_t *child) {
parent->right_child.next = &child->right_child;
child->right_child.prev = &parent->right_child;
}
```

---

## Advanced Examples

### Double-Ended Queue (Deque)

**Deque Operations:**

- `push_front()` - Add to head
- `push_back()` - Add to tail
- `pop_front()` - Remove from head
- `pop_back()` - Remove from tail

````c
typedef struct deque {
glthread_node_t *head;
glthread_node_t *tail;
} deque_t;

void deque_push_front(deque_t *dq, glthread_node_t *node) {
node->prev = NULL;
node->next = dq->head;

    if (dq->head) {
        dq->head->prev = node;
    } else {
        dq->tail = node;
    }
    dq->head = node;

}

void deque_push_back(deque_t *dq, glthread_node_t *node) {
node->next = NULL;
node->prev = dq->tail;

    if (dq->tail) {
        dq->tail->next = node;
    } else {
        dq->head = node;
    }
    dq->tail = node;

}

glthread_node_t* deque_pop_front(deque_t *dq) {
if (!dq->head) return NULL;

    glthread_node_t *node = dq->head;
    dq->head = node->next;

    if (dq->head) {
        dq->head->prev = NULL;
    } else {
        dq->tail = NULL;
    }

    node->next = node->prev = NULL;
    return node;

}

glthread_node_t* deque_pop_back(deque_t *dq) {
if (!dq->tail) return NULL;

    glthread_node_t *node = dq->tail;
    dq->tail = node->prev;

    if (dq->tail) {
        dq->tail->next = NULL;
    } else {
        dq->head = NULL;
    }

    node->next = node->prev = NULL;
    return node;

}
### Circular Linked List

\image html ../assets/images/Circular_Linked_List.svg "Circular Linked List"

```c
void circular_list_add(glthread_node_t *head, glthread_node_t *new_node) {
if (!head->next) {
// First node
head->next = new_node;
head->prev = new_node;
new_node->next = head;
new_node->prev = head;
} else {
// Insert before head
new_node->next = head;
new_node->prev = head->prev;
head->prev->next = new_node;
head->prev = new_node;
}
}

void circular_list_traverse(glthread_node_t *head) {
if (!head->next) return;

    glthread_node_t *current = head->next;
    do {
        // Process current node
        current = current->next;
    } while (current != head->next);

}
````

---

## Comparison: Traditional vs GLThreads

| Aspect                | Traditional Nodes                          | GLThreads                                    |
| --------------------- | ------------------------------------------ | -------------------------------------------- |
| **Memory Allocation** | Separate allocations for each node         | Single allocation for data + embedded node   |
| **Cache Locality**    | Poor - scattered memory                    | Good - data and node together                |
| **Multiple Lists**    | Requires wrapper structures or duplication | Embed multiple nodes in one structure        |
| **Type Safety**       | Requires explicit casting                  | Type-safe macros (GLTHREAD_TO_STRUCT)        |
| **Complexity**        | Simple, straightforward                    | Requires understanding of offset calculation |

---

## Best Practices

> ✅ DO:

- Use GLThreads for structures that need to be in multiple lists
- Initialize glthread nodes before use
- Use type-safe macros (GLTHREAD_TO_STRUCT)
- Document which list each embedded node is for

> ⚠️ DON'T:

- Don't forget to remove nodes before freeing memory
- Don't use the same glthread node in multiple lists simultaneously
- Don't manually manipulate pointers without proper checks
- Don't assume thread safety without external locking

---

## Related Documentation

- [Architecture Overview](architecture.md) - System design using GLThreads
- [Developer Guide](developer_guide.md) - Implementation details
- [API Reference](api_reference.md) - GLThread API functions
