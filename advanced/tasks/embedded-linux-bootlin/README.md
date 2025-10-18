# Embedded Linux with QEMU Bootlin

## Table of Contents

- [Embedded Linux with QEMU Bootlin](#embedded-linux-with-qemu-bootlin)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Project Structure](#project-structure)
  - [Getting Started](#getting-started)
  - [Requirements](#requirements)
    - [Ubuntu/Debian](#ubuntudebian)
    - [Fedora](#fedora)
    - [Arch Linux](#arch-linux)
  - [Usage](#usage)
    - [Running QEMU](#running-qemu)
    - [Building the Kernel](#building-the-kernel)
    - [Debugging](#debugging)
  - [Resources](#resources)
  - [License](#license)

## Introduction

This project is a comprehensive guide and set of resources for learning embedded Linux development using QEMU, provided by Bootlin. The materials include lab exercises, a tarball with additional files, and presentation slides.

## Project Structure

```
embedded-linux-bootlin/
├── embedded-linux-qemu-labs.pdf         # Lab exercises PDF
├── embedded-linux-qemu-labs.tar.xz      # Tarball with additional lab files
├── embedded-linux-qemu-slides.pdf       # Presentation slides PDF
```

## Getting Started

To get started with this project, follow these steps:

1. **Download and extract the lab files:**

   ```sh
   tar -xf embedded-linux-qemu-labs.tar.xz -C /path/to/extract/
   ```

2. **Read the lab exercises:**
   Open `embedded-linux-qemu-labs.pdf` to understand the exercises and follow the instructions provided.

3. **Review the presentation slides:**
   Open `embedded-linux-qemu-slides.pdf` to get an overview and in-depth knowledge of embedded Linux using QEMU.

## Requirements

To work through the exercises in this project, you need the following tools installed on your development machine:

- QEMU
- GCC (GNU Compiler Collection)
- Make
- Linux kernel source code (as specified in the labs)
- A Linux-based operating system (recommended)

You can install these tools using the following commands:

### Ubuntu/Debian

```sh
sudo apt-get update
sudo apt-get install qemu gcc make
```

### Fedora

```sh
sudo dnf install qemu gcc make
```

### Arch Linux

```sh
sudo pacman -S qemu gcc make
```

## Usage

### Running QEMU

To start QEMU with a specific configuration, follow the steps in the lab exercises PDF. Generally, you will use a command like this:

```sh
qemu-system-x86_64 -kernel /path/to/kernel -initrd /path/to/initrd -append "root=/dev/ram rdinit=/sbin/init"
```

### Building the Kernel

To compile and build the Linux kernel for QEMU, you need to configure it properly:

1. **Navigate to the kernel source directory:**

   ```sh
   cd /path/to/linux-source
   ```

2. **Configure the kernel:**

   ```sh
   make menuconfig
   ```

3. **Build the kernel:**
   ```sh
   make -j$(nproc)
   ```

### Debugging

QEMU provides various options for debugging:

```sh
qemu-system-x86_64 -s -S -kernel /path/to/kernel
```

This command starts QEMU in a halted state and waits for a GDB connection on port 1234.

## Resources

Here are some valuable resources for further reading and understanding:

1. **[Bootlin's Training Materials](https://bootlin.com/training/embedded-linux/):** Official training materials for embedded Linux.
2. **[QEMU Documentation](https://qemu.readthedocs.io/en/latest/):** Official QEMU documentation.
3. **[Kernel Newbies](https://kernelnewbies.org/):** A community for aspiring Linux kernel developers.

## License

This project is licensed under the [GPL License](../../../LICENSE).
