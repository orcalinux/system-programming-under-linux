# Session 03: Working with Yocto

## Overview

This README provides a structured guide to setting up and working with Yocto, a powerful build system for creating custom Linux distributions for embedded devices. It includes steps for installing necessary prerequisites, downloading recipes, building images, and adding additional layers.

For more detailed documentation, refer to the [Yocto Project Documentation](https://docs.yoctoproject.org/index.html).

## Table of Contents

1. [Install Prerequisites](#install-prerequisites)
2. [Downloading and Setting Up Yocto](#downloading-and-setting-up-yocto)
3. [Building an Image](#building-an-image)
4. [Adding More Layers](#adding-more-layers)
5. [Post-Build Steps](#post-build-steps)
6. [QEMU Monitor and Running QEMU](#qemu-monitor-and-running-qemu)
7. [Saving the Kernel and Root Filesystem](#saving-the-kernel-and-root-filesystem)
8. [Resources](#resources)

---

## Install Prerequisites

Before setting up Yocto, ensure you have the required packages installed on your system. Follow the instructions provided in the [Yocto Project Quick Start Guide](https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html).

Run the following command to install the prerequisites:

```sh
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
    build-essential chrpath socat libsdl1.2-dev xterm lz4
```

---

## Downloading and Setting Up Yocto

1. **Clone the Poky Repository**

   Download the Yocto recipes by cloning the Poky repository. Make sure to use the appropriate branch (e.g., scarthgap):

   ```sh
   git clone -b <release-name> git://git.yoctoproject.org/poky
   ```

2. **Set Up the Build Environment**

   Navigate to the poky directory and set up the build environment:

   ```sh
   cd poky
   source oe-init-build-env ../build-qemux86-64
   ```

---

## Building an Image

1. **Configure Local Settings**

   Inside the build directory, update the machine and download directories in `conf/local.conf`:

   ```sh
   MACHINE ??= "qemux86-64"
   DL_DIR ?= "/home/mahmoud/yocto2024/<release-name>/downloads"
   ```

2. **Build the Image**

   In the build directory, issue the following command to build a minimal core image:

   ```sh
   bitbake core-image-minimal
   ```

---

## Adding More Layers

You can add more layers to enhance your Yocto build. While this is not necessary, it is recommended.

1. **Clone Additional Layers**

   For example, to add the `meta-odroid` layer, clone the repository:

   ```sh
   cd poky
   git clone https://github.com/akuster/meta-odroid
   ```

2. **Check Out the Correct Branch**

   Ensure that the layer is on the same release branch as Yocto (Poky). For instance, if Poky is on the `scarthgap` branch:

   ```sh
   cd meta-odroid
   git checkout scarthgap
   ```

3. **Update `bblayers.conf`**

   Update `conf/bblayers.conf` to include the new layer:

   ```sh
   BBLAYERS ?= " \
     /home/mahmoud/yocto2024/<release-name>/poky/meta \
     /home/mahmoud/yocto2024/<release-name>/poky/meta-poky \
     /home/mahmoud/yocto2024/<release-name>/poky/meta-yocto-bsp \
     /home/mahmoud/yocto2024/<release-name>/poky/meta-odroid \
   "
   ```

The first three layers are added by default by Poky.

---

## Post-Build Steps

1. **Build Finished**

   After the build is finished, you will find the image in `tmp/deploy/images/`.

2. **Navigate to the Image Directory**

   ```sh
   cd tmp/deploy/images/qemux86-64
   ```

3. **Run the Image**

   ```sh
   runqemu core-image-minimal-qemux86-64 nographic
   ```

4. **Save the Image File System and Your Information**

   It is recommended to copy the `bzImage-qemux86-64.bin` and `core-image-minimal-qemux86-64.ext4` files to a new directory. This is because any further changes you make in the Yocto build environment may overwrite your current image:

   ```sh
   mkdir -p ~/yocto2024/<release-name>/qemux86-64-demo
   cp tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.ext4 ~/yocto2024/<release-name>/qemux86-64-demo
   cp tmp/deploy/images/qemux86-64/bzImage-qemux86-64.bin ~/yocto2024/<release-name>/qemux86-64-demo 
   ```

5. **Run Your Saved Image**

   ```sh
   runqemu ~/yocto2024/<release-name>/qemux86-64-demo/core-image-minimal-qemux86-64.ext4 ~/yocto2024/<release-name>/qemux86-64-demo/bzImage-qemux86-64.bin nographic
   ```

---

## QEMU Monitor and Running QEMU

QEMU Monitor is a command-line interface that allows you to control and interact with QEMU while it is running. It provides various commands to manage the virtual machine.

### Running QEMU Normally

To run QEMU with a graphical interface (default mode), you can use the following command:

```sh
runqemu core-image-minimal-qemux86-64
```

This will launch the QEMU emulator with a graphical interface where you can interact with your running image.

### Running QEMU in `nographic` Mode

In some cases, such as when you are working on a server without a graphical interface or when you want to run QEMU in the background, you can use the `nographic` option:

```sh
runqemu core-image-minimal-qemux86-64 nographic
```

This will run QEMU without opening a graphical window. You can interact with the virtual machine through the terminal.

### Using QEMU Monitor

When running QEMU, you can access the QEMU Monitor by pressing `Ctrl + Alt + 2`. This will switch the terminal to the QEMU Monitor interface. To switch back to the guest console, press `Ctrl + Alt + 1`.

In the QEMU Monitor, you can use various commands to control the VM, such as:

- `info`: Display information about the VM.
- `stop`: Stop the VM.
- `cont`: Continue running the VM.
- `quit`: Quit QEMU.

Example commands:

```sh
info status
stop
cont
quit
```

---

## Saving the Kernel and Root Filesystem

After building the image with Yocto, it is recommended to save the kernel and root filesystem files (`bzImage-qemux86-64.bin` and `core-image-minimal-qemux86-64.ext4`) to a separate directory. This helps prevent any changes made in the Yocto environment from affecting your built image.

1. **Create a New Directory:**

   ```sh
   mkdir -p ~/yocto2024/<release-name>/saved-images
   ```

2. **Copy the Image Files:**

   ```sh
   cp tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.ext4 ~/yocto2024/<release-name>/saved-images
   cp tmp/deploy/images/qemux86-64/bzImage-qemux86-64.bin ~/yocto2024/<release-name>/saved-images
   ```

3. **Run Your Saved Image:**

   ```sh
   runqemu ~/yocto2024/<release-name>/saved-images/core-image-minimal-qemux86-64.ext4 ~/yocto2024/<release-name>/saved-images/bzImage-qemux86-64.bin nographic
   ```

---

## Resources

- [Yocto Project Documentation](https://docs.yoctoproject.org/index.html)
- [Yocto Project Releases](https://wiki.yoctoproject.org/wiki/Releases)
- [Yocto Project Overview Video](https://youtu.be/8M8U1EgnUVw?si=1cH194i2Bgcd8TZJ)
