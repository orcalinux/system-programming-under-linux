# Discovering How VMs Deal with TAP Devices

## Overview

This guide explores how virtual machines (VMs) interact with TAP (Network TAP) devices. We demonstrate how to create a TAP device in the kernel, and how it appears as a file in user space without showing up in the filesystem. This guide includes an explanation of clone devices in the kernel, necessary ioctl calls, and a detailed breakdown of the provided C program. Additionally, resources for further reading on clone devices and ioctl are included.

## Table of Contents

1. [Introduction to TAP Devices](#introduction-to-tap-devices)
2. [Creating and Using TAP Devices](#creating-and-using-tap-devices)
3. [Understanding Clone Devices in Linux](#understanding-clone-devices-in-linux)
4. [C Program Explanation](#c-program-explanation)
5. [Compiling and Running the Program](#compiling-and-running-the-program)
6. [Resources](#resources)

---

## Introduction to TAP Devices

TAP devices are virtual network kernel devices. They provide user-space programs with access to the network layer. TAP devices operate at Layer 2 of the OSI model, handling Ethernet frames. They are used in various virtualization solutions like QEMU to provide network connectivity to VMs.

**Key Points:**
- TAP devices are created and managed using the `tun` module.
- They allow reading and writing of Ethernet frames.
- Commonly used for network simulation and virtualization.

## Creating and Using TAP Devices

To create and use a TAP device, follow these steps:

1. **Load the tun module:**
    ```sh
    sudo modprobe tun
    ```

2. **Create a TAP device using `ip` or `tunctl` command:**
    ```sh
    sudo ip tuntap add dev tap0 mode tap
    sudo ip link set tap0 up
    ```

3. **Assign an IP address to the TAP device:**
    ```sh
    sudo ip addr add 192.168.1.1/24 dev tap0
    ```

4. **Use the TAP device in a program:**
   - Open the `/dev/net/tun` device.
   - Configure it using `ioctl` system calls.
   - Use the returned file descriptor for read/write operations.

## Understanding Clone Devices in Linux

The concept of a clone device is critical in kernel development. In Linux, the `/dev/net/tun` is a special file representing the TUN/TAP device driver. This driver can create multiple network interfaces, which are not pre-defined in the filesystem.

When a user-space program opens `/dev/net/tun` and performs an `ioctl` call with `TUNSETIFF`, the kernel allocates a new network interface (either TUN or TAP, depending on the flags). This interface is a clone device, dynamically created by the kernel. The user-space program receives a file descriptor (fd) for this device, allowing it to interact with the network interface directly.

**Key Points:**
- Clone devices are dynamically created and do not appear in the filesystem.
- They allow user-space programs to directly interact with network interfaces.
- This mechanism is widely used in virtualization and network simulation.

## C Program Explanation

The provided C program (`tapClient.c`) demonstrates how to create and use a TAP device. The program performs the following steps:

1. **Include necessary headers:**
    ```c
    #include <sys/socket.h>
    #include <linux/if.h>
    #include <linux/if_tun.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include "arp_protocol_handler.h"
    #include "ethernet_frame_handler.h"
    #include "icmp_protocol_handler.h"
    #include "ipv4_protocol_handler.h"
    ```

2. **Define the TAP device name:**
    ```c
    #define TAP_DEVICE "tap4"
    ```

3. **Function to create TAP device (tun_alloc.c):**
    ```c
    /**
     * @file tun_alloc.c
     * @brief Function to allocate and configure a TAP device.
     */

    #include "tap_device_client.h"

    int tun_alloc(char *dev, int flags) {
        struct ifreq ifr;
        int fd, err;
        char *clonedev = "/dev/net/tun";

        // Open the clone device
        if ((fd = open(clonedev, O_RDWR)) < 0) {
            return fd;
        }

        // Preparation of the struct ifr, of type "struct ifreq"
        memset(&ifr, 0, sizeof(ifr));
        ifr.ifr_flags = flags;
        if (*dev) {
            strncpy(ifr.ifr_name, dev, IFNAMSIZ);
        }

        // Try to create the device
        if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
            close(fd);
            return err;
        }

        // Write back the name of the interface to the variable "dev"
        strcpy(dev, ifr.ifr_name);
        return fd;
    }
    ```

4. **Main function (tap_device_client.c):**
    ```c
    /**
     * @file tap_device_client.c
     * @brief Main program for the TAP device client.
     */

    #include "tap_device_client.h"

    int main(int argc, char** argv) {
        char tap_name[IFNAMSIZ];
        int tap_fd;
        unsigned char buffer[1500];
        int nread;
        int i;

        // Connect to the tap device
        strcpy(tap_name, TAP_DEVICE);
        tap_fd = tun_alloc(tap_name, IFF_TAP | IFF_NO_PI);

        if (tap_fd < 0) {
            perror("Allocating interface");
            exit(1);
        }

        // Read data coming from the kernel
        while (1) {
            nread = read(tap_fd, buffer, sizeof(buffer));
            if (nread < 0) {
                perror("Reading from interface");
                close(tap_fd);
                exit(1);
            }

            printf("\n =========================================================\n");
            for (i = 0; i < nread; i++) {
                printf("%x ", buffer[i]);
                if (!(i % 10)) printf("\n");
            }
            // Send a ping reply
            replyToPing(tap_fd, buffer, nread);
        }
        return 0;
    }
    ```

5. **Function to reply to ping requests (reply_to_ping.c):**
    ```c
    /**
     * @file reply_to_ping.c
     * @brief Function to send a reply to a received ping (ICMP Echo Request).
     */

    #include "tap_device_client.h"

    void replyToPing(int fd, unsigned char* buff, int buffSize) {
        uint8_t myMacAddress[6] = {0xe4, 0xfa, 0xff, 0xaa, 0xba, 0xcc};
        static uint16_t id = 0;
        int nWrite;
        ethernet_t *ethernetPacketPointer;
        unsigned char copy_buff[1500];

        ethernetPacketPointer = (ethernet_t *) buff;
        memcpy(ethernetPacketPointer->recv_mac, ethernetPacketPointer->send_mac, 6);
        memcpy(ethernetPacketPointer->send_mac, myMacAddress, 6);

        // ARP Protocol
        if (ntohs(ethernetPacketPointer->type_len) == 0x0806) {
            arpPacket_t *arpPacketPointer;
            uint32_t tempIP;

            arpPacketPointer = (arpPacket_t *)(buff + sizeof(ethernet_t));
            tempIP = arpPacketPointer->destIP.iIP4;
            arpPacketPointer->destIP.iIP4 = arpPacketPointer->sourceIP.iIP4;
            arpPacketPointer->sourceIP.iIP4 = tempIP;

            arpPacketPointer->operation = ntohs(2);
            memcpy(arpPacketPointer->dest_mac, arpPacketPointer->source_mac, 6);
            memcpy(arpPacketPointer->source_mac, myMacAddress, 6);

            nWrite = write(fd, buff, buffSize);
            if (nWrite < 0) {
                perror("Writing to interface");
                close(fd);
                exit(1);
            }
        }
        // IPv4 Protocol
        else if (ntohs(ethernetPacketPointer->type_len) == 0x0800) {
            ipv4Packet_t *ipv4PacketPointer;
            ipv4Packet_t *ipv4PacketPointer_copy;
            uint32_t tempIP;
            uint16_t tmpchecksum;
            ipv4PacketPointer = (ipv4Packet_t *)(buff + sizeof(ethernet_t));
            printf("IPv4 checksum=%x\n", ipv4PacketPointer->checksum);
            memcpy(copy_buff, buff, buffSize);
            ipv4PacketPointer_copy = (ipv4Packet_t *)(copy_buff + sizeof(ethernet_t));
            ipv4PacketPointer_copy->checksum = 0;
            printf("IPv4 checksum computed=%x\n", htons(internetChecksum(ipv4PacketPointer_copy, sizeof(ipv4Packet_t), 0)));

            if (ipv4PacketPointer->protocol == 1) {
                tempIP = ipv4PacketPointer->destIP.iIP4;
                ipv4PacketPointer->destIP.iIP4 = ipv4PacketPointer->sourceIP.iIP4;
                ipv4PacketPointer->sourceIP.iIP4 = tempIP;
                ipv4PacketPointer->identification = ++id;
                ipv4PacketPointer->checksum = 0;
                ipv4PacketPointer->checksum = htons(internetChecksum(ipv4PacketPointer, sizeof(ipv4Packet_t), 0));
                int icmpDataLength = buffSize - (sizeof(ethernet_t) + sizeof(ipv4Packet_t) + sizeof(icmpheader_t));
                icmpheader_t *icmpPacketPointer;
                icmpPacketPointer = (icmpheader_t *)(buff + sizeof(ethernet_t) + sizeof(ipv4Packet_t));
                icmpPacketPointer->type = ICMP_ECHO_REPLY;
                printf("--------ICMP CHECKSUM \n");
                icmpPacketPointer->checksum = 0;
                tmpchecksum = internetChecksum(icmpPacketPointer, sizeof(icmpheader_t) + icmpDataLength, 0);
                icmpPacketPointer->checksum = htons(tmpchecksum);
                printf("debug id=%d checksum=%x\n", id, tmpchecksum);
                printf("debug icmpPacketPointer->id=%d icmpPacketPointer->seqnumber=%d\n", icmpPacketPointer->id, icmpPacketPointer->seqnumber);
                nWrite = write(fd, buff, buffSize);
                if (nWrite < 0) {
                    perror("Writing to interface");
                    close(fd);
                    exit(1);
                }
            }
        }
    }
    ```

6. **Function to calculate the internet checksum (internet_checksum.c):**
    ```c
    /**
     * @file internet_checksum.c
     * @brief Function to calculate the Internet checksum.
     */

    #include "tap_device_client.h"

    uint16_t internetChecksum(const void* addr, size_t count, uint32_t pseudoHeaderChecksum) {
        uint32_t sum = pseudoHeaderChecksum;
        const uint8_t* data = addr;

        while (count > 1) {
            printf("data[%ld]=%x data[%ld]=%x\n", count, data[0], count-1, data[1]);
            sum += (data[0] << 8) | data[1];
            data += 2;
            count -= 2;
        }

        if (count > 0) {
            sum += data[0] << 8;
        }

        while (sum >> 16) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
        printf("-----Checksum return=%x\n", (~sum & 0xFFFF));
        return ~sum & 0xFFFF;
    }
    ```

## Compiling and Running the Program

1. **Compile the program:**
    ```sh
    gcc -o tap_device_client tap_device_client.c tun_alloc.c internet_checksum.c reply_to_ping.c
    ```

2. **Run the program with root privileges:**
    ```sh
    sudo ./tap_device_client
    ```

3. **Run the script to ping:**
    ```sh
    bash tapClientScript.cmd
    ```

4. **Capture packets using tshark:**
    ```sh
    sudo tshark -i tap4 -T fields -e eth.src -e eth.dst -e ip.src -e ip.dst
    ```

5. **Set up the TAP interface and assign an IP:**
    ```sh
    sudo ip link set tap4 up
    sudo ip addr add 172.16.1.1/24 dev tap4
    ping 172.16.1.2
    ```

## Resources

- [Linux Kernel Documentation on TUN/TAP](https://www.kernel.org/doc/Documentation/networking/tuntap.txt)
- [ioctl Manual](http://man7.org/linux/man-pages/man2/ioctl.2.html)
- [QEMU Documentation](https://www.qemu.org/documentation/)
- [Network Programming Guide](https://www.oreilly.com/library/view/linux-network-programming/9780596002558/)
