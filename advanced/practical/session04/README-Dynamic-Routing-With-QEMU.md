# Dynamic Routing in Virtual Machines Using QEMU

## Overview

This guide provides a comprehensive explanation of setting up and configuring dynamic routing in virtual machines (VMs) using QEMU. It covers the basics of dynamic routing, the necessary tools, and step-by-step instructions to implement and test dynamic routing algorithms. The guide focuses on using Quagga, a popular routing software suite, to manage dynamic routing protocols such as RIP, OSPF, and BGP.

## Table of Contents

1. [Introduction to Dynamic Routing](#introduction-to-dynamic-routing)
2. [Dynamic Routing Protocols](#dynamic-routing-protocols)
   - [RIP (Routing Information Protocol)](#rip-routing-information-protocol)
   - [OSPF (Open Shortest Path First)](#ospf-open-shortest-path-first)
   - [BGP (Border Gateway Protocol)](#bgp-border-gateway-protocol)
3. [Setting Up the Environment](#setting-up-the-environment)
   - [Creating Virtual Machines with QEMU](#creating-virtual-machines-with-qemu)
   - [Creating VMs with Yocto Image](#creating-vms-with-yocto-image)
4. [Configuring Dynamic Routing in VMs](#configuring-dynamic-routing-in-vms)
   - [Installing Quagga Routing Suite](#installing-quagga-routing-suite)
   - [Configuring RIP](#configuring-rip)
   - [Configuring OSPF](#configuring-ospf)
   - [Configuring BGP](#configuring-bgp)
5. [Testing and Verifying the Configuration](#testing-and-verifying-the-configuration)
6. [Scripts for Setting Up Network Bridges](#scripts-for-setting-up-network-bridges)
7. [Conclusion](#conclusion)

---

## Introduction to Dynamic Routing

Dynamic routing is a method where routers automatically adjust the paths that data packets take based on current network conditions. Unlike static routing, which requires manual configuration, dynamic routing uses algorithms and protocols to determine the best path for data transmission.

### Benefits of Dynamic Routing
- **Automatic Path Adjustment**: Automatically adapts to changes in the network, such as link failures or congestion.
- **Scalability**: Suitable for large and complex networks.
- **Efficiency**: Optimizes the routing of packets, improving overall network performance.

---

## Dynamic Routing Protocols

### RIP (Routing Information Protocol)
RIP is a distance-vector routing protocol that uses hop count as the metric to determine the best path. It is simple to configure and suitable for small networks.

### OSPF (Open Shortest Path First)
OSPF is a link-state routing protocol that uses the shortest path first (SPF) algorithm to determine the best path. It is more complex than RIP but provides faster convergence and better scalability.

### BGP (Border Gateway Protocol)
BGP is a path-vector protocol used for routing between autonomous systems on the Internet. It is highly scalable and used by large networks and ISPs.

---

## Setting Up the Environment

### Creating Virtual Machines with QEMU

1. **Install QEMU**:
    ```sh
    sudo apt-get install qemu-kvm qemu-utils
    ```

2. **Create Disk Images for VMs**:
    Create disk images for each VM that will act as a router.
    ```sh
    qemu-img create -f qcow2 router1.img 20G
    qemu-img create -f qcow2 router2.img 20G
    qemu-img create -f qcow2 router3.img 20G
    ```

3. **Install Ubuntu on Each VM**:
    Boot each VM with an Ubuntu ISO to install the operating system.
    ```sh
    qemu-system-x86_64 -cdrom ubuntu.iso -boot d -m 2G -hda router1.img
    ```

4. **Start VMs**:
    Start each VM and configure network interfaces.
    ```sh
    qemu-system-x86_64 -m 512 -hda router1.img -net nic -net tap,ifname=tap0,script=no,downscript=no -daemonize
    qemu-system-x86_64 -m 512 -hda router2.img -net nic -net tap,ifname=tap1,script=no,downscript=no -daemonize
    qemu-system-x86_64 -m 512 -hda router3.img -net nic -net tap,ifname=tap2,script=no,downscript=no -daemonize
    ```

### Creating VMs with Yocto Image

1. **Build Yocto Image**:
    Follow the Yocto Project instructions to build an image with networking support.

2. **Run the Yocto Image with QEMU**:
    ```sh
    qemu-system-x86_64 -m 512 -hda yocto-router1.img -net nic -net tap,ifname=tap0,script=no,downscript=no -daemonize
    qemu-system-x86_64 -m 512 -hda yocto-router2.img -net nic -net tap,ifname=tap1,script=no,downscript=no -daemonize
    qemu-system-x86_64 -m 512 -hda yocto-router3.img -net nic -net tap,ifname=tap2,script=no,downscript=no -daemonize
    ```

**Note**: In the case of Yocto images, you may need to install additional packages. Refer to [Yocto Package Installation Guide](https://github.com/Mahmoud-Abdelraouf/STmicro-System-Programming-under-Linux/blob/main/05.Advanced/Practical/Session04/README-Yocto-Package-Installation.md) for detailed instructions.

### Configuring Network Bridges on the Host
To allow VMs to communicate, you need to create network bridges on the host machine.

1. **Create a Bridge**:
    ```sh
    sudo ip link add name br0 type bridge
    sudo ip link set dev br0 up
    ```

2. **Add TAP Interfaces to the Bridge**:
    ```sh
    sudo ip link set dev tap0 master br0
    sudo ip link set dev tap1 master br0
    sudo ip link set dev tap2 master br0
    ```

---

## Configuring Dynamic Routing in VMs

### Installing Quagga Routing Suite

1. **Install Quagga on Each VM**:
    ```sh
    sudo apt-get install quagga
    ```

2. **Enable IP Forwarding**:
    ```sh
    echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward
    ```

3. **Configure Quagga**:
    Edit the configuration files for Quagga located in `/etc/quagga`.

### Configuring RIP

1. **Edit the `zebra.conf` file** on each VM:
    ```sh
    sudo nano /etc/quagga/zebra.conf
    ```

    Add the following lines:
    ```plaintext
    hostname Router1
    password zebra
    enable password zebra
    ```

2. **Edit the `ripd.conf` file** on each VM:
    ```sh
    sudo nano /etc/quagga/ripd.conf
    ```

    Add the following lines:
    ```plaintext
    hostname Router1
    router rip
     network eth0
    line vty
    ```

3. **Start the Quagga services** on each VM:
    ```sh
    sudo systemctl start zebra
    sudo systemctl start ripd
    ```

### Configuring OSPF

1. **Edit the `ospfd.conf` file** on each VM:
    ```sh
    sudo nano /etc/quagga/ospfd.conf
    ```

    Add the following lines:
    ```plaintext
    hostname Router1
    password zebra
    enable password zebra
    !
    router ospf
     network 192.168.1.0/24 area 0
     network 192.168.2.0/24 area 0
    line vty
    ```

2. **Start the Quagga services** on each VM:
    ```sh
    sudo systemctl start zebra
    sudo systemctl start ospfd
    ```

### Configuring BGP

1. **Edit the `bgpd.conf` file** on each VM:
    ```sh
    sudo nano /etc/quagga/bgpd.conf
    ```

    Add the following lines:
    ```plaintext
    hostname Router1
    password zebra
    enable password zebra
    !
    router bgp 65001
     neighbor 192.168.1.2 remote-as 65002
     network 192.168.1.0/24
    line vty
    ```

2. **Start the Quagga services** on each VM:
    ```sh
    sudo systemctl start zebra
    sudo systemctl start bgpd
    ```

---

## Testing and Verifying the Configuration

To verify the dynamic routing configuration, you can use various commands to check the routing tables and ensure that routes are being correctly propagated.

### Checking Routing Tables

1. **Check the routing table** on each VM:
    ```sh
    ip route show
    ```

2. **Check the OSPF neighbors** on each VM:
    ```sh
    sudo vtysh -c "show ip ospf neighbor"
    ```

3. **Check the BGP neighbors** on each VM:
    ```sh
    sudo vtysh -c "show ip bgp summary"
    ```

### Testing Connectivity

1. **Ping between routers**:
    ```sh
    ping <destination-router-ip>
    ```

2. **Traceroute to check the path**:
    ```sh
    traceroute <destination-ip>
    ```

---

## Scripts for Setting Up Network Bridges

To automate the process of setting up the network bridges and starting the VMs, you can use the following scripts:

### Start Script for Three Machines

```sh
#!/bin/bash

# Create TAP interfaces
sudo ip tuntap add mode tap tap0
sudo ip tuntap add mode tap tap1
sudo ip tuntap add mode tap tap2

# Create a bridge and add the TAP interfaces
sudo ip link add name br0 type bridge
sudo ip link set dev br0 up
sudo ip link set dev tap0 master br0
sudo ip link set dev tap1 master br0
sudo ip link set dev tap2 master br0

# Start VMs
qemu-system-x86_64 -m 512 -hda yocto-router1.img -net nic -net tap,ifname=tap0,script=no,downscript=no -daemonize
qemu-system-x86_64 -m 512 -hda yocto-router2.img -net nic -net tap,ifname=tap1,script=no,downscript=no -daemonize
qemu-system-x86_64 -m 512 -hda yocto-router3.img -net nic -net tap,ifname=tap2,script=no,downscript=no -daemonize
```

### Cleanup Script for Three Machines

```sh
#!/bin/bash

# Stop VMs
sudo pkill qemu-system-x86_64

# Remove TAP interfaces from bridge
sudo ip link set dev tap0 nomaster
sudo ip link set dev tap1 nomaster
sudo ip link set dev tap2 nomaster

# Delete bridge
sudo ip link delete br0

# Delete TAP interfaces
sudo ip tuntap del mode tap tap0
sudo ip tuntap del mode tap tap1
sudo ip tuntap del mode tap tap2
```

---

By following this guide, you can set up and configure dynamic routing in a virtualized environment using QEMU and Quagga. This setup allows you to simulate real-world networking scenarios and understand how dynamic routing protocols like RIP, OSPF, and BGP work. Dynamic routing offers flexibility and efficiency, making it suitable for complex and large-scale networks.
