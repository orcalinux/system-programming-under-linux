# Training with STMicroelectronics - System Programming under Linux

## Overview

During my training with STMicroelectronics, I underwent an extensive learning journey covering various aspects of embedded systems development, Linux fundamentals, and software engineering practices. This README provides an overview of the topics covered and the skills acquired during the training period.

## Table of Contents

- [Training with STMicroelectronics - System Programming under Linux](#training-with-stmicroelectronics---system-programming-under-linux)
  - [Overview](#overview)
  - [Table of Contents](#table-of-contents)
  - [Training Content](#training-content)
    - [Part 1: Introductory Training](#part-1-introductory-training)
      - [Linux History](#linux-history)
      - [Command Line Usage and Build Process](#command-line-usage-and-build-process)
      - [Process Management](#process-management)
      - [User Management](#user-management)
      - [Filesystem Management](#filesystem-management)
    - [Part 2: Intermediate Training](#part-2-intermediate-training)
      - [The Linux Programming Interface](#the-linux-programming-interface)
      - [Project: Linux Memory Manager](#project-linux-memory-manager)
    - [Part 3: Advanced Training](#part-3-advanced-training)
      - [Introduction to Assembly Language](#introduction-to-assembly-language)
      - [Tutorial on POSIX Threads](#tutorial-on-posix-threads)
      - [Signals as a Means of Interprocess Communications](#signals-as-a-means-of-interprocess-communications)
      - [Introduction to Kernel Modules](#introduction-to-kernel-modules)
      - [Building Embedded Linux File Systems and Kernel using Yocto Build System](#building-embedded-linux-file-systems-and-kernel-using-yocto-build-system)
      - [Kernel Namespaces and Container Software](#kernel-namespaces-and-container-software)
      - [Fundamentals of TCP/IP and Socket Programming](#fundamentals-of-tcpip-and-socket-programming)
  - [Skills Acquired](#skills-acquired)
  - [Instructor Information](#instructor-information)

---

## Training Content

### Part 1: Introductory Training

#### Linux History

We delved into the history of Linux, exploring its origins, development milestones, and the philosophy behind open-source software.

#### Command Line Usage and Build Process

Understanding the command line interface is fundamental to working with Linux-based embedded systems. We learned how to navigate the command line efficiently and explored the build process for compiling and linking software applications.

#### Process Management

- **Process Overview:** Understanding the concept of processes in Linux and how they interact with the operating system.
- **System Calls and Command Line Arguments:** Exploring system calls and their role in process management, along with handling command line arguments in C programs.
- **Process Creation:** Learning about process creation using functions such as `fork()` and `exec()`.

- **Orphan & Zombie Processes:** Understanding the concepts of orphan and zombie processes and their implications on system resources.

- **Bash Features:** Exploring advanced features of the Bash shell for scripting and automation.

- **Intro to Proc fs:** Introduction to the `/proc` filesystem and its role in providing information about processes and system resources.

- **IO Redirection in the Shell:** Mastering input/output redirection techniques in the shell for efficient command-line usage.

#### User Management

We covered user management concepts, including user account administration, permissions, and security practices.

#### Filesystem Management

- **Intro to HDD:** Understanding hard disk drive (HDD) fundamentals and their role in storing data on embedded systems.

- **Parsing MBR Partition Tables:** Exploring Master Boot Record (MBR) partition tables and techniques for parsing them.

- **File System Formatting, Mounting, and Architecture:** Learning about file system formats, mounting procedures, and the underlying architecture of file systems.

- **Directories, Files, Links, and Permissions:** Understanding the structure of directories and files, symbolic and hard links, and managing permissions for file access control.

- **Implementing “ls”:** Developing a simplified version of the `ls` command to list directory contents.

### Part 2: Intermediate Training

#### The Linux Programming Interface

In the second part of the training, we studied "The Linux Programming Interface," which provided an in-depth understanding of system programming concepts and APIs used in Linux.

#### Project: Linux Memory Manager

As a practical application of the concepts learned, we developed a project focused on creating a Linux memory manager. This project involved:

- **Memory Allocation and Deallocation:** Implementing custom memory allocation and deallocation routines.
- **Memory Mapping:** Understanding and utilizing memory mapping techniques.
- **Virtual Memory Management:** Exploring virtual memory concepts and implementing a basic virtual memory manager.

### Part 3: Advanced Training

#### Introduction to Assembly Language

- **Objective:** Demonstrate the portability of the UNIX/Linux interface through the use of assembly system calls in Glibc.
- **Key Topics:**
  - Basics of assembly language and its importance in low-level programming.
  - How system calls are implemented in assembly within the Glibc environment.
  - Calling conventions across different processors (e.g., x86, ARM).

#### Tutorial on POSIX Threads

- **Objective:** Explore the Native POSIX Thread Library (NPTL) and relevant kernel implementations.
- **Key Topics:**
  - Overview of POSIX threads (pthreads) and thread management.
  - Detailed walkthrough of thread creation, synchronization, and management in Linux.
  - Examination of kernel-level support for threading.

#### Signals as a Means of Interprocess Communications

- **Objective:** Discuss the role of signals in IPC and related system concepts.
- **Key Topics:**
  - Fundamentals of UNIX signals and their role in controlling processes.
  - Process states, Job Control, and pseudo terminals (PTYs).
  - Use cases and limitations of signals in modern IPC.

#### Introduction to Kernel Modules

- **Objective:** Explore kernel modules and pseudo file systems crucial for system monitoring.
- **Key Topics:**
  - Concepts and creation of Linux kernel modules.
  - Deep dive into /proc, /sys filesystems and their role in the Linux ecosystem.
  - Understanding Cgroup filesystem and its usage in resource management.

#### Building Embedded Linux File Systems and Kernel using Yocto Build System

- **Objective:** Learn to build customized Linux environments using different build systems.
- **Key Topics:**
  - Introduction to the Yocto project and its architecture.
  - Building a minimal Linux system for embedded devices.
  - Comparison with Debian-like file systems built using Bootstrap and Multistrap.

#### Kernel Namespaces and Container Software

- **Objective:** Examine how Linux namespaces support containerization technologies.
- **Key Topics:**
  - Overview of Linux namespaces (PID, net, IPC, mount, etc.).
  - Practical demonstrations using Docker, Podman, and Systemd-nspawn.
  - System calls associated with namespaces management.

#### Fundamentals of TCP/IP and Socket Programming

- **Objective:** Detailed study of network programming and the Linux network stack.
- **Key Topics:**
  - TCP/IP fundamentals and socket programming concepts.
  - Exploring the Linux kernel network stack.
  - Hands-on coding examples in creating network applications.

---

## Skills Acquired

- Proficiency in using the Linux command line interface for system administration and software development tasks.
- Understanding of process management concepts and system calls in Linux.
- Knowledge of file system management, including formatting, mounting, and permissions.
- Familiarity with Bash scripting for automation and task automation.
- Ability to work with embedded systems and perform low-level tasks such as parsing MBR partition tables.
- In-depth understanding of system programming concepts from "The Linux Programming Interface."
- Practical experience in developing a Linux memory manager.
- Understanding of assembly language and its role in system calls.
- Knowledge of POSIX threads and multi-threading in Linux.
- Insights into interprocess communication using signals.
- Experience with Linux kernel modules and file systems.
- Skills in building embedded Linux systems using the Yocto project.
- Understanding of Linux namespaces and containerization.
- Fundamentals of TCP/IP and socket programming.

---

## Instructor Information

**Instructor:** Reda Maher

**LinkedIn:** [Instructor's LinkedIn Profile URL](https://www.linkedin.com/in/reda-maher/)
