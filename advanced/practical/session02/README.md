# Session 02: Working with Podman and Docker - System Programming under Linux

## Overview

This README provides a structured guide to setting up and managing containers using Podman and Docker, including detailed instructions for installing necessary packages, pulling and running images, configuring registries, and using various container-related commands.

## Table of Contents

1. [Overview](#overview)
2. [Prerequisites](#prerequisites)
3. [Podman Installation](#podman-installation)
4. [Using Podman](#using-podman)
   - [Searching for Images](#searching-for-images)
   - [Pulling Images](#pulling-images)
   - [Running Containers](#running-containers)
   - [Managing Containers](#managing-containers)
5. [Configuring Registries](#configuring-registries)
6. [Using Docker](#using-docker)
7. [Community and Support](#community-and-support)
8. [Conclusion](#conclusion)

---

## Prerequisites

Ensure you have the following packages and tools installed on your system:

- Git
- CMake
- Python 3
- Other essential tools for building software (gcc, make, etc.)

---

## Podman Installation

Podman is a daemonless container engine for developing, managing, and running OCI Containers on your Linux system.

### Installation on Ubuntu 22.04

To install Podman on Ubuntu 22.04, run the following commands:

```sh
sudo apt update
sudo apt install podman
```

---

## Using Podman

### Searching for Images

To search for images on Docker Hub, use the `podman search` command:

```sh
podman search nginx --filter=is-official
```

This command searches for images related to "nginx" on Docker Hub and filters for official images only. Here is an example output:

```sh
INDEX       NAME                     DESCRIPTION                                      STARS       OFFICIAL    AUTOMATED
docker.io   docker.io/library/nginx  Official build of Nginx.                         19857       [OK]
docker.io   docker.io/library/unit   Official build of NGINX Unit: Universal Web ...  29          [OK]
```

### Pulling Images

To pull an image from Docker Hub, use the `podman pull` command:

```sh
podman pull docker.io/library/nginx
```

Example output:

```sh
Trying to pull docker.io/library/nginx:latest...
Getting image source signatures
Copying blob 09f376ebb190 skipped: already exists  
Copying blob de3b062c0af7 done  
Copying blob a11fc495bafd done  
Copying blob 999643392fb7 done  
Copying blob 45337c09cd57 done  
Copying blob 933cc8470577 done  
Copying blob 971bb7f4fb12 done  
Copying config e784f45604 done  
Writing manifest to image destination
Storing signatures
e784f4560448b14a66f55c26e1b4dad2c2877cc73d001b7cd0b18e24a700a070
```

### Running Containers

To run a container from the pulled image:

```sh
podman run --name basic_httpd -dt -p 8080:80/tcp docker.io/nginx
```

This command runs an Nginx container, mapping port 8080 on your host to port 80 in the container.

### Managing Containers

- **List running containers**:

  ```sh
  podman ps
  ```

  Example output:

  ```sh
  CONTAINER ID  IMAGE                           COMMAND               CREATED         STATUS             PORTS                 NAMES
  e5c5c256d422  docker.io/library/nginx:latest  nginx -g daemon o...  45 seconds ago  Up 45 seconds ago  0.0.0.0:8080->80/tcp  basic_httpd
  ```

- **List all containers**:

  ```sh
  podman ps -a
  ```

  Example output:

  ```sh
  CONTAINER ID  IMAGE                           COMMAND               CREATED      STATUS                  PORTS                 NAMES
  8fa0fe0d9a6b  docker.io/library/nginx:latest  nginx -g daemon o...  6 weeks ago  Exited (0) 6 weeks ago  0.0.0.0:8080->80/tcp  basic_httpd
  4a65496986e4  docker.io/library/nginx:latest  nginx -g daemon o...  5 weeks ago  Exited (0) 5 weeks ago  0.0.0.0:8080->80/tcp  st_httpd
  ```

- **Start a stopped container**:

  ```sh
  podman start 8fa0fe0d9a6b
  ```

- **Stop a running container**:

  ```sh
  podman stop 8fa0fe0d9a6b
  ```

- **Inspect a container**:

  ```sh
  podman inspect 8fa0fe0d9a6b | grep '"Name"'
  ```

  Example output:

  ```sh
  "Name": "basic_httpd",
  ```

You can start and stop containers by name as well:

```sh
podman start "basic_httpd"
podman stop "basic_httpd"
```

---

## Configuring Registries

To configure container registries, edit the `/etc/containers/registries.conf` file.

### Example Configuration

To set Docker Hub as the default unqualified search registry:

```sh
unqualified-search-registries = ["docker.io"]
```

To change the default search registry to Red Hat:

```sh
unqualified-search-registries = ["registry.redhat.io"]
```

### Searching Specific Registries

- **Search Docker Hub**:

  ```sh
  podman search docker.io/httpd
  ```

- **Search Red Hat Registry**:

  ```sh
  podman search registry.redhat.io/httpd
  ```

Example of a successful search:

```sh
podman search httpd --filter=is-official
INDEX       NAME                     DESCRIPTION                     STARS       OFFICIAL    AUTOMATED
docker.io   docker.io/library/httpd  The Apache HTTP Server Project  4709        [OK]
```

---

## Using Docker

Docker is another popular container engine that you might use during your training. Here are some basic Docker commands:

### Searching for Images

To search for images on Docker Hub:

```sh
docker search nginx
```

### Pulling Images

To pull an image from Docker Hub:

```sh
docker pull nginx
```

### Running Containers

To run a container from the pulled image:

```sh
docker run -d -p 8080:80 nginx
```

### Managing Containers

- **List running containers**:

  ```sh
  docker ps
  ```

- **List all containers**:

  ```sh
  docker ps -a
  ```

- **Start a stopped container**:

  ```sh
  docker start <container_id_or_name>
  ```

- **Stop a running container**:

  ```sh
  docker stop <container_id_or_name>
  ```

- **Inspect a container**:

  ```sh
  docker inspect <container_id_or_name>
  ```

---

## Community and Support

Join the community forums, mailing lists, and GitHub repositories for support, discussions, and contributions. 

- [Podman Community](https://podman.io/community/)
- [Docker Community](https://www.docker.com/community)
