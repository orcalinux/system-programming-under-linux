# Setting Up and Running a CentOS Container on Ubuntu using Docker and Systemd-nspawn

## Overview

This guide provides step-by-step instructions to download CentOS using Docker and run it within a container using `systemd-nspawn` on an Ubuntu system.

## Table of Contents

- [Setting Up and Running a CentOS Container on Ubuntu using Docker and Systemd-nspawn](#setting-up-and-running-a-centos-container-on-ubuntu-using-docker-and-systemd-nspawn)
  - [Overview](#overview)
  - [Table of Contents](#table-of-contents)
  - [Install Required Packages](#install-required-packages)
  - [Download CentOS with Docker](#download-centos-with-docker)
  - [Configure the CentOS Container](#configure-the-centos-container)
  - [Start the CentOS Container](#start-the-centos-container)
  - [Enter the CentOS Container](#enter-the-centos-container)
  - [Additional Notes](#additional-notes)

---

## Install Required Packages

Ensure you have `docker.io` and `systemd-container` installed on your Ubuntu system:

```sh
sudo apt update
sudo apt install docker.io systemd-container
```

---

## Download CentOS with Docker

Use Docker to create a CentOS root filesystem.

1. **Pull the CentOS Docker Image**

   ```sh
   sudo docker pull centos:7
   ```

2. **Create a Directory for the CentOS Root Filesystem**

   ```sh
   sudo mkdir -p /var/lib/machines/centos7
   ```

3. **Export the Docker Image to a Tar File**

   ```sh
   sudo docker save centos:7 -o centos7.tar
   ```

4. **Extract the Tar File into the Directory**

   ```sh
   sudo tar -xf centos7.tar -C /var/lib/machines/centos7
   ```

---

## Configure the CentOS Container

1. **Set a Root Password**

   Start the container and set a root password:

   ```sh
   sudo systemd-nspawn -D /var/lib/machines/centos7 /bin/bash
   passwd
   exit
   ```

2. **Configure the Container Network (optional)**

   If you want to set up networking for the container, you can create a configuration file:

   ```sh
   sudo nano /etc/systemd/nspawn/centos7.nspawn
   ```

   Add the following lines to configure the network:

   ```ini
   [Network]
   Zone=trusted
   ```

3. **Ensure that the CentOS Container Has a Working resolv.conf**

   ```sh
   sudo cp /etc/resolv.conf /var/lib/machines/centos7/etc/resolv.conf
   ```

---

## Start the CentOS Container

Start the container using `systemd-nspawn`:

```sh
sudo systemd-nspawn -D /var/lib/machines/centos7 --boot
```

This will boot the CentOS container.

---

## Enter the CentOS Container

You can enter the CentOS container using:

```sh
sudo machinectl shell centos7
```

Or directly using `systemd-nspawn`:

```sh
sudo systemd-nspawn -D /var/lib/machines/centos7
```

---

## Additional Notes

- **Network Configuration:** You might need to configure networking within the CentOS container depending on your use case.
- **Persistent Storage:** Ensure that any persistent data is correctly mapped to volumes outside the container if necessary.
- **Resource Limits:** Configure resource limits for the container using systemd unit files if needed.

By following these steps, you will be able to download CentOS using Docker, create a container, and run it within `systemd-nspawn` on your Ubuntu system.
