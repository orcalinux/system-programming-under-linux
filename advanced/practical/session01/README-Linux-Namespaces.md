# Linux Namespaces

## Overview

Linux namespaces provide a way to create isolation for various system resources. This README covers the eight types of namespaces in Linux, how to create them using different syscalls, and how to add namespaces to a container.

## Table of Contents

1. [Overview](#overview)
2. [Types of Namespaces](#types-of-namespaces)
   - [PID Namespace](#pid-namespace)
   - [Network Namespace](#network-namespace)
   - [Mount Namespace](#mount-namespace)
   - [IPC Namespace](#ipc-namespace)
   - [UTS Namespace](#uts-namespace)
   - [User Namespace](#user-namespace)
   - [Cgroup Namespace](#cgroup-namespace)
   - [Time Namespace](#time-namespace)
3. [Creating Namespaces](#creating-namespaces)
   - [Using `unshare`](#using-unshare)
   - [Using `clone`](#using-clone)
   - [Using `setns`](#using-setns)
4. [Code Examples](#code-examples)
   - [Creating a PID Namespace](#creating-a-pid-namespace)
   - [Creating a Network Namespace](#creating-a-network-namespace)
   - [Creating a Mount Namespace](#creating-a-mount-namespace)
5. [Adding Namespaces to Containers](#adding-namespaces-to-containers)
6. [References](#references)

---

## Types of Namespaces

### PID Namespace

**Purpose:** Isolates the process ID number space, allowing processes to have different views of the process tree.

**Syscall:** `CLONE_NEWPID`

### Network Namespace

**Purpose:** Isolates network resources such as network devices, IP addresses, and routing tables.

**Syscall:** `CLONE_NEWNET`

### Mount Namespace

**Purpose:** Isolates the set of mounted file systems, allowing different processes to have different views of the file system hierarchy.

**Syscall:** `CLONE_NEWNS`

### IPC Namespace

**Purpose:** Isolates interprocess communication resources, such as System V IPC objects and POSIX message queues.

**Syscall:** `CLONE_NEWIPC`

### UTS Namespace

**Purpose:** Isolates the hostname and NIS domain name.

**Syscall:** `CLONE_NEWUTS`

### User Namespace

**Purpose:** Isolates user and group ID number spaces, allowing a process to have different user and group IDs.

**Syscall:** `CLONE_NEWUSER`

### Cgroup Namespace

**Purpose:** Isolates the view of cgroups, allowing processes to have different views of the cgroup hierarchy.

**Syscall:** `CLONE_NEWCGROUP`

### Time Namespace

**Purpose:** Isolates the system and monotonic clocks, allowing processes to have different views of time.

**Syscall:** `CLONE_NEWTIME`

---

## Creating Namespaces

### Using `unshare`

The `unshare` command allows a program to run with some namespaces unshared from its parent.

**Example:**

```sh
unshare --pid --fork --mount-proc bash
```

This command will create a new PID namespace and mount namespace, then start a bash shell within these namespaces. The `--fork` option ensures that the shell runs as a child process.

### Using `clone`

The `clone` system call creates a new process, and can also create new namespaces.

**Example:**

```c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int childFunc(void *arg) {
    printf("In child process!\n");
    return 0;
}

int main() {
    const int STACK_SIZE = 1024 * 1024;
    char *stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (clone(childFunc, stack + STACK_SIZE, SIGCHLD | CLONE_NEWPID, NULL) == -1) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    printf("In parent process!\n");
    free(stack);
    return 0;
}
```

### Using `setns`

The `setns` system call allows a process to join an existing namespace.

**Example:**

```c
#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("/proc/<pid>/ns/net", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (setns(fd, CLONE_NEWNET) == -1) {
        perror("setns");
        return 1;
    }

    close(fd);
    // Now in the target network namespace
    return 0;
}
```

---

## Code Examples

### Creating a PID Namespace

```c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int childFunc(void *arg) {
    printf("Child PID: %ld\n", (long)getpid());
    return 0;
}

int main() {
    const int STACK_SIZE = 1024 * 1024;
    char *stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (clone(childFunc, stack + STACK_SIZE, CLONE_NEWPID | SIGCHLD, NULL) == -1) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    sleep(1);  // Give the child time to execute
    printf("Parent PID: %ld\n", (long)getpid());
    free(stack);
    return 0;
}
```

### Creating a Network Namespace

```c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int childFunc(void *arg) {
    system("ip link");
    return 0;
}

int main() {
    const int STACK_SIZE = 1024 * 1024;
    char *stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (clone(childFunc, stack + STACK_SIZE, CLONE_NEWNET | SIGCHLD, NULL) == -1) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    sleep(1);  // Give the child time to execute
    free(stack);
    return 0;
}
```

### Creating a Mount Namespace

```c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>

static int childFunc(void *arg) {
    if (mount("proc", "/proc", "proc", 0, NULL) == -1) {
        perror("mount");
        return 1;
    }

    system("mount | grep proc");
    return 0;
}

int main() {
    const int STACK_SIZE = 1024 * 1024;
    char *stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (clone(childFunc, stack + STACK_SIZE, CLONE_NEWNS | SIGCHLD, NULL) == -1) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    sleep(1);  // Give the child time to execute
    free(stack);
    return 0;
}
```

---

## Adding Namespaces to Containers

To add namespaces to a container, you can use tools like `systemd-nspawn`, `Docker`, or `Podman`. Here’s an example with `systemd-nspawn`:

### Using `systemd-nspawn`

**Creating a container with specific namespaces:**

```sh
systemd-nspawn --directory=/path/to/container/root --private-network --hostname=my-container
```

### Using `Docker`

Docker automatically creates several namespaces for containers. Here’s how you can create a Docker container:

```sh
docker run -it --name my-container --hostname my-container --network none ubuntu bash
```

This command creates a container with its own network namespace (`--network none`).

### Using `Podman`

Similar to Docker, Podman also uses namespaces for containers:

```sh
podman run -it --name my-container --hostname my-container --network none ubuntu bash
```

---

## Differences Between `clone` and `unshare`

### `clone`

- **Purpose:** Creates a new process and can simultaneously create new namespaces.
- **Usage:** Typically used when you need to create a new process that should be part of new namespaces from the start.
- **Example:** Creating a new PID namespace along with a new process.
  
  ```c
  if (clone(childFunc, stack + STACK_SIZE, CLONE_NEWPID | SIGCHLD, NULL) == -1) {
      perror("clone");
      exit(EXIT_FAILURE);
  }
  ```

### `unshare`

- **Purpose:** Modifies the current process to unshare namespaces from its parent.
- **Usage:** Used when you want the current process (or a newly forked process) to operate in new namespaces without creating a completely new process.
- **Example:** Creating a new mount namespace for the current shell.

  ```sh
  unshare --mount --fork bash
  ```

### Key Differences

- **Process Creation:** `clone` creates a new process, while `unshare` affects

 the current process.
- **Flexibility:** `unshare` is useful for modifying the namespace environment of the current process or shell, whereas `clone` is better suited for creating a new process in new namespaces.
- **Complexity:** `clone` involves more setup since it requires providing a new stack for the child process, whereas `unshare` is simpler for modifying the current process.

---

## References

- [man 2 clone](https://man7.org/linux/man-pages/man2/clone.2.html)
- [man 2 unshare](https://man7.org/linux/man-pages/man2/unshare.2.html)
- [man 2 setns](https://man7.org/linux/man-pages/man2/setns.2.html)
- [Linux Containers](https://linuxcontainers.org/)
- [man 7 namespaces](https://man7.org/linux/man-pages/man7/namespaces.7.html)
