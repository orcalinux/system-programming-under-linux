# Socket Programming Examples

## Socket Programming in C++

This guide will walk you through the basic concepts and steps required for socket programming in C++. Each section includes code snippets with detailed explanations to help you understand the functionality of each component.

---

### 1. Creating a Socket

A socket is an endpoint for communication. When you create a socket, you're essentially creating a means to communicate over a network.

- `socket(AF_INET, SOCK_STREAM, 0)`: This call creates a socket.
  - `AF_INET`: Specifies the address family (IPv4 in this case).
  - `SOCK_STREAM`: Specifies the type of socket (stream socket for TCP).
  - `0`: Specifies the protocol (0 means the default protocol for the given address family and socket type).

#### Code

```cpp
// create_socket.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    std::cout << "Socket created successfully" << std::endl;

    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Socket created successfully
```

#### How to Run

```sh
g++ create_socket.cpp -o create_socket
./create_socket
```

---

### 2. Binding the Socket

Binding a socket associates it with a specific IP address and port number, so it can listen for incoming connections on that address and port.

- `bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr))`: This call binds the socket to the specified IP address and port.
  - `serverSocket`: The socket file descriptor.
  - `(sockaddr*)&serverAddr`: A pointer to a `sockaddr_in` structure that specifies the address to bind to.
  - `sizeof(serverAddr)`: The size of the `sockaddr_in` structure.

#### Code

```cpp
// bind_socket.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;            // IPv4
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
    serverAddr.sin_port = htons(8080);          // Port 8080

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Socket bound successfully" << std::endl;

    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Socket bound successfully
```

#### How to Run

```sh
g++ bind_socket.cpp -o bind_socket
./bind_socket
```

---

### 3. Listening on the Socket

Listening on a socket tells the system that the socket is ready to accept incoming connection requests.

- `listen(serverSocket, SOMAXCONN)`: This call puts the server socket into a passive mode, where it waits for incoming connection requests.
  - `serverSocket`: The socket file descriptor.
  - `SOMAXCONN`: The maximum number of pending connections the socket can have.

#### Code

```cpp
// listen_socket.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
```

#### How to Run

```sh
g++ listen_socket.cpp -o listen_socket
./listen_socket
```

---

### 4. Accepting a Connection

Accepting a connection means the server will handle incoming connection requests.

- `accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize)`: This call accepts an incoming connection.
  - `serverSocket`: The socket file descriptor.
  - `(sockaddr*)&clientAddr`: A pointer to a `sockaddr_in` structure that will hold the address of the client.
  - `&clientAddrSize`: A pointer to a variable that will hold the size of the client address structure.

#### Code

```cpp
// accept_connection.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    // Accept a client connection
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Connection accepted from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
Connection accepted from 127.0.0.1:[client_port]
```

#### How to Run

```sh
g++ accept_connection.cpp -o accept_connection
./accept_connection
```

---

### 5. Communicating with the Client

After accepting a connection, the server can send and receive data to/from the client.

- `send(clientSocket, message, strlen(message), 0)`: This call sends data to the client.
  - `clientSocket`: The socket file descriptor of the accepted client.
  - `message`: A pointer to the data to be sent.
  - `strlen(message)`: The length of the data to be sent.
  - `0`: Flags (0 means no special options).

#### Code

```cpp
// communicate_with_client.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (

bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    // Accept a client connection
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Connection accepted from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

    // Communicate with the client
    const char* message = "Hello from the server!\n";
    send(clientSocket, message, strlen(message), 0);

    // Close the client and server sockets
    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
Connection accepted from 127.0.0.1:[client_port]
```

#### How to Run

```sh
g++ communicate_with_client.cpp -o communicate_with_client
./communicate_with_client
```

#### How to Test

1. **Run the server**:

   ```sh
   ./communicate_with_client
   ```

2. **Open another terminal and connect using `nc`**:

   - Using `nc`:

     ```sh
     nc 127.0.0.1 8080
     ```

   - Using `telnet`:
     ```sh
     telnet 127.0.0.1 8080
     ```

3. **You should see the message "Hello from the server!" in the client terminal.**

---

## Advanced Socket Programming

### 6. TCP Server and Client for Uppercase Conversion

This example demonstrates a TCP server and client where the client sends text to the server, the server converts it to uppercase, and then sends it back to the client.

#### TCP Server

```cpp
// tcp_server.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>

void toUpperCase(char* str, int length) {
    std::transform(str, str + length, str, ::toupper);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        close(serverSocket);
        return -1;
    }

    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, 4096, 0);
    if (bytesReceived < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        close(clientSocket);
        close(serverSocket);
        return -1;
    }

    toUpperCase(buffer, bytesReceived);

    send(clientSocket, buffer, bytesReceived, 0);

    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### TCP Client

```cpp
// tcp_client.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        close(clientSocket);
        return -1;
    }

    const char* message = "hello server";
    send(clientSocket, message, strlen(message), 0);

    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, 4096, 0);
    if (bytesReceived < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        close(clientSocket);
        return -1;
    }

    std::cout << "Received from server: " << std::string(buffer, 0, bytesReceived) << std::endl;

    close(clientSocket);
    return 0;
}
```

#### How to Run

1. **Compile the server and client**:

   ```sh
   g++ tcp_server.cpp -o tcp_server
   g++ tcp_client.cpp -o tcp_client
   ```

2. **Run the server**:

   ```sh
   ./tcp_server
   ```

3. **Run the client** in another terminal:

   ```sh
   ./tcp_client
   ```

#### Expected Output (Client)

```
Received from server: HELLO SERVER
```

---

### 7. UDP Server and Client for Uppercase Conversion

This example demonstrates a UDP server and client where the client sends text to the server, the server converts it to uppercase, and then sends it back to the client.

#### UDP Server

```cpp
// udp_server.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>

void toUpperCase(char* str, int length) {
    std::transform(str, str + length, str, ::toupper);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    char buffer[4096];
    int bytesReceived = recvfrom(serverSocket, buffer, 4096, 0, (sockaddr*)&clientAddr, &clientAddrSize);
    if (bytesReceived < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        close(serverSocket);
        return -1;
    }

    toUpperCase(buffer, bytesReceived);

    sendto(serverSocket, buffer, bytesReceived, 0, (sockaddr*)&clientAddr, clientAddrSize);

    close(serverSocket);
    return 0;
}
```

#### UDP Client

```cpp
// udp_client.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    const char* message = "hello server";
    sendto(clientSocket, message, strlen(message), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[4096];
    socklen

_t serverAddrSize = sizeof(serverAddr);
    int bytesReceived = recvfrom(clientSocket, buffer, 4096, 0, (sockaddr*)&serverAddr, &serverAddrSize);
    if (bytesReceived < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        close(clientSocket);
        return -1;
    }

    std::cout << "Received from server: " << std::string(buffer, 0, bytesReceived) << std::endl;

    close(clientSocket);
    return 0;
}
```

#### How to Run

1. **Compile the server and client**:

   ```sh
   g++ udp_server.cpp -o udp_server
   g++ udp_client.cpp -o udp_client
   ```

2. **Run the server**:

   ```sh
   ./udp_server
   ```

3. **Run the client** in another terminal:

   ```sh
   ./udp_client
   ```

#### Expected Output (Client)

```
Received from server: HELLO SERVER
```

---

## Summary

By running these individual programs, you will gain a deeper understanding of how each component works in the context of C++ web server development. The examples cover the creation, binding, listening, accepting, and communication aspects of sockets, as well as file reading and HTTP request parsing.

### Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/)
- [Linux Socket Programming by Example](https://www.amazon.com/Linux-Socket-Programming-Example-Warren/dp/0789722410)
- [Unix Network Programming by W. Richard Stevens](https://www.amazon.com/Unix-Network-Programming-Sockets-Networking/dp/0131411551)
- [C++ Networking: How to Write Network Applications in C++](https://www.educative.io/courses/c-plus-plus-networking)

---

By following this guide, you'll have a solid foundation in socket programming with C++ and be well-equipped to build more complex networked applications.
