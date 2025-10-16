# Session 01: Intro to Containers in Linux - System Programming under Linux

## Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Creating Root Filesystems](#creating-root-filesystems)
   - [Step-by-Step Instructions](#step-by-step-instructions)
     - [Install Debootstrap and Systemd-Nspawn](#1-install-debootstrap-and-systemd-nspawn)
     - [Create Root Filesystems](#2-create-root-filesystems)
   - [Ubuntu Jammy](#ubuntu-jammy)
   - [Debian Bookworm](#debian-bookworm)
     - [AMD64 Architecture](#amd64-architecture)
     - [ARM64 Architecture](#arm64-architecture)
     - [ARMEL Architecture](#armel-architecture)
     - [ARMHF Architecture](#armhf-architecture)
     - [I386 Architecture](#i386-architecture)
4. [Setting Up and Managing Containers](#setting-up-and-managing-containers)
   - [Set Root Password](#set-root-password)
   - [Booting Containers](#booting-containers)
5. [Notes](#notes)

---

## Introduction

This README provides a structured guide to setting up and managing Linux containers using debootstrap and systemd-nspawn. It includes detailed instructions for installing necessary packages, downloading and creating root filesystems for various architectures, setting root passwords, and booting into these environments.

---

## Prerequisites

Ensure you have the following packages installed:

```sh
sudo apt install debootstrap
sudo apt install systemd-container
sudo apt install qemu-user-static  # Needed for non-Intel containers
```

---

## Creating Root Filesystems

### Step-by-Step Instructions

#### 1. Install Debootstrap and Systemd-Nspawn

Ensure that `debootstrap` and `systemd-container` are installed on your system:

```sh
sudo apt install debootstrap
sudo apt install systemd-container
sudo apt install qemu-user-static  # Needed for non-Intel containers
```

#### 2. Create Root Filesystems

You need to specify the Debian release and the target directory for the root filesystem. Here are the steps for different architectures.

---

### Ubuntu Jammy

#### Create Root Filesystem

```sh
debootstrap jammy ./jammy
```

This command downloads the Ubuntu Jammy release and installs it into the `./jammy` directory.

#### Set Root Password

```sh
systemd-nspawn --directory=./jammy passwd
```

#### Boot the Container

```sh
systemd-nspawn --directory=./jammy --boot
```

---

### Debian Bookworm

#### AMD64 Architecture

##### Create Root Filesystem

```sh
debootstrap --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch amd64 bookworm ./amd64root http://ftp.debian.org/debian/
```

##### Create a Tarball

To reuse this root filesystem, you can create a tarball:

```sh
debootstrap --make-tarball=./amd64gcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch amd64 bookworm ./amd64root http://ftp.debian.org/debian/
```

##### Unpack from Tarball

If you have an existing tarball, you can unpack it:

```sh
debootstrap --unpack-tarball=/root/amd64gcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch amd64 bookworm ./amd64root http://ftp.debian.org/debian/
```

##### Set Root Password and Boot

```sh
systemd-nspawn --directory=./amd64root passwd
systemd-nspawn --directory=./amd64root --boot
```

---

### ARM64 Architecture

#### Create Root Filesystem

```sh
debootstrap --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch arm64 bookworm ./arm64root http://ftp.debian.org/debian/
```

#### Create a Tarball

```sh
debootstrap --make-tarball=./arm64gcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch arm64 bookworm ./arm64root http://ftp.debian.org/debian/
```

#### Unpack from Tarball

```sh
debootstrap --unpack-tarball=/root/arm64gcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch arm64 bookworm ./arm64root http://ftp.debian.org/debian/
```

#### Set Root Password and Boot

```sh
systemd-nspawn --directory=./arm64root passwd
systemd-nspawn --directory=./arm64root --boot
```

---

### ARMEL Architecture

#### Create Root Filesystem

```sh
debootstrap --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch armel bookworm ./armelroot http://ftp.debian.org/debian/
```

#### Create a Tarball

```sh
debootstrap --make-tarball=./armelgcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch armel bookworm ./armelroot http://ftp.debian.org/debian/
```

#### Unpack from Tarball

```sh
debootstrap --unpack-tarball=/root/armelgcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch armel bookworm ./armelroot http://ftp.debian.org/debian/
```

#### Set Root Password and Boot

```sh
systemd-nspawn --directory=./armelroot passwd
systemd-nspawn --directory=./armelroot --boot
```

---

### ARMHF Architecture

#### Create Root Filesystem

```sh
debootstrap --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch armhf bookworm ./armhfroot http://ftp.debian.org/debian/
```

#### Create a Tarball

```sh
debootstrap --make-tarball=./armhfgcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch armhf bookworm ./armhfroot http://ftp.debian.org/debian/
```

#### Unpack from Tarball

```sh
debootstrap --unpack-tarball=/root/armhfgcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch armhf bookworm ./armhfroot http://ftp.debian.org/debian/
```

#### Set Root Password and Boot

```sh
systemd-nspawn --directory=./armhfroot passwd
systemd-nspawn --directory=./armhfroot --boot
```

---

### I386 Architecture

#### Create Root Filesystem

```sh
debootstrap --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch i386 bookworm ./i386root http://ftp.debian.org/debian/
```

#### Create a Tarball

```sh
debootstrap --make-tarball=./i386gcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch i386 bookworm ./i386root http://ftp.debian.org/debian/
```

#### Unpack from Tarball

```sh
debootstrap --unpack-tarball=/root/i386gcc.tar --include=systemd-sysv,net-tools,iproute2,vlan,iputils-ping,ssh,gcc,binutils,build-essential --arch i386 bookworm ./i386root http://ftp.debian.org/debian/
```

#### Set Root Password and Boot

```sh
systemd-nspawn --directory=./i386root passwd
systemd-nspawn --directory=./i386root --boot
```

---

## Setting Up and Managing Containers

### Set Root Password

To set the root password for a container:

```sh
systemd-nspawn --directory=./<root_directory> passwd
```

### Booting Containers

To boot a container:

```sh
systemd-nspawn --directory=./<root_directory> --boot
```

---

## Notes

- Replace `<root_directory>` with the appropriate directory for your container.
- Ensure that you have appropriate permissions and the necessary packages installed before running these commands.
- Always verify the URLs and package names according to your distribution's repository.
