# Introductory Training in Linux Systems Programming

## Overview

This document provides an outline of the introductory training on Linux systems programming. The training covers fundamental concepts such as the history of Linux, command line usage, process management, user management, and filesystem management. Each section provides insights into key topics and practical skills necessary for working with Linux-based systems.

## Table of Contents

1. [Linux History](#linux-history)
2. [Command Line Usage and Build Process](#command-line-usage-and-build-process)
3. [Process Management](#process-management)
4. [User Management](#user-management)
5. [Filesystem Management](#filesystem-management)
6. [Resources](#resources)

---

## Linux History

We delved into the history of Linux, exploring its origins, development milestones, and the philosophy behind open-source software.

### Key Topics:
- Origins and evolution of Linux.
- Key milestones in Linux development.
- Philosophy and principles of open-source software.

## Command Line Usage and Build Process

Understanding the command line interface is fundamental to working with Linux-based embedded systems. We learned how to navigate the command line efficiently and explored the build process for compiling and linking software applications.

### Key Topics:
- Navigating the command line.
- Commonly used command line commands.
- Build process for compiling and linking applications.

## Process Management

### Process Overview

Understanding the concept of processes in Linux and how they interact with the operating system.

### System Calls and Command Line Arguments

Exploring system calls and their role in process management, along with handling command line arguments in C programs.

### Process Creation

Learning about process creation using functions such as `fork()` and `exec()`.

### Orphan & Zombie Processes

Understanding the concepts of orphan and zombie processes and their implications on system resources.

### Bash Features

Exploring advanced features of the Bash shell for scripting and automation.

### Intro to Proc fs

Introduction to the `/proc` filesystem and its role in providing information about processes and system resources.

### IO Redirection in the Shell

Mastering input/output redirection techniques in the shell for efficient command-line usage.

## User Management

We covered user management concepts, including user account administration, permissions, and security practices.

### Key Topics:
- User account administration.
- Managing permissions and access control.
- Security practices for user management.

## Filesystem Management

### Intro to HDD

Understanding hard disk drive (HDD) fundamentals and their role in storing data on embedded systems.

### Parsing MBR Partition Tables

Exploring Master Boot Record (MBR) partition tables and techniques for parsing them.

### File System Formatting, Mounting, and Architecture

Learning about file system formats, mounting procedures, and the underlying architecture of file systems.

### Directories, Files, Links, and Permissions

Understanding the structure of directories and files, symbolic and hard links, and managing permissions for file access control.

### Implementing “ls”

Developing a simplified version of the `ls` command to list directory contents.

---

## Resources

This training provided a solid foundation in Linux systems programming, covering essential topics and practical skills. For further reading and practice, consider exploring the following resources:

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Linux Command Line and Shell Scripting Bible](https://www.wiley.com/en-us/Linux+Command+Line+and+Shell+Scripting+Bible,+3rd+Edition-p-9781118983843)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- [Linux Kernel Documentation](https://www.kernel.org/doc/html/latest/)
