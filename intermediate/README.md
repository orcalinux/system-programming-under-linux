# Intermediate Training: Linux Systems Programming

## Overview

This document outlines the intermediate training in Linux systems programming, focusing on in-depth system programming concepts and practical applications. The training is based on "The Linux Programming Interface" book by Michael Kerrisk and includes a detailed project on creating a Linux memory manager.

## Table of Contents

1. [The Linux Programming Interface](#the-linux-programming-interface)
2. [Project: Linux Memory Manager](#project-linux-memory-manager)
3. [Chapters Covered](#chapters-covered)
4. [Practical Labs and Real-World Examples](#practical-labs-and-real-world-examples)
5. [Resources](#resources)

---

## The Linux Programming Interface

In the second part of the training, we studied "The Linux Programming Interface," which provided an in-depth understanding of system programming concepts and APIs used in Linux. The first 10 chapters of the book were covered, providing a strong foundation in Linux system programming.

### Chapters Covered

1. **Chapter 1: History and Standards**
   - Overview of UNIX and Linux history.
   - Understanding POSIX and UNIX standards.

2. **Chapter 2: Fundamental Concepts**
   - Core concepts of operating systems.
   - The shell, users, and groups.
   - Directory hierarchy, files, and links.

3. **Chapter 3: System Programming Concepts**
   - System calls and library functions.
   - Error handling and portability issues.

4. **Chapter 4: File I/O: The Universal I/O Model**
   - File I/O operations using system calls.
   - Opening, reading, writing, and closing files.

5. **Chapter 5: File I/O: Further Details**
   - Advanced file I/O operations.
   - File control operations and nonblocking I/O.

6. **Chapter 6: Processes**
   - Process creation and termination.
   - Process states and memory layout.

7. **Chapter 7: Memory Allocation**
   - Dynamic memory allocation.
   - Memory management techniques.

8. **Chapter 8: Users and Groups**
   - User and group management.
   - Password and shadow files.

9. **Chapter 9: Process Credentials**
   - Understanding process credentials.
   - Real, effective, and saved user and group IDs.

10. **Chapter 10: Time**
    - Handling time and date in programs.
    - System clocks and timers.

### Additional Topics Covered
- **Static and Shared Libraries**
  - Creating and using static and shared libraries.
  - Differences between static and shared linking.
  - Advantages and disadvantages of static and shared libraries.

## Project: Linux Memory Manager

As a practical application of the concepts learned, we developed a project focused on creating a Linux memory manager. This project involved:

### Memory Allocation and Deallocation
- Implementing custom memory allocation and deallocation routines.

### Memory Mapping
- Understanding and utilizing memory mapping techniques.

### Virtual Memory Management
- Exploring virtual memory concepts and implementing a basic virtual memory manager.

### Project Highlights
- Designing and implementing a custom memory allocator.
- Handling memory fragmentation and optimizing allocation strategies.
- Mapping files into memory and managing memory-mapped regions.
- Creating a basic virtual memory manager to handle paging and segmentation.

## Practical Labs and Real-World Examples

Each topic is paired with practical labs and real-world examples to enhance learning and retention, making it ideal for those aiming to deepen their understanding of Linux internals and system programming.

## Resources

This training provided an in-depth understanding of Linux system programming, focusing on practical skills and advanced concepts. For further reading and practice, consider exploring the following resources:

- [The Linux Programming Interface by Michael Kerrisk](https://man7.org/tlpi/)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- [Linux Kernel Development by Robert Love](https://rlove.org/)
- [Memory Management Documentation in the Linux Kernel](https://www.kernel.org/doc/html/latest/admin-guide/mm/index.html)
