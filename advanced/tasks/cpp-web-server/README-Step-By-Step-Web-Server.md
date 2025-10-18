# Step-by-Step Guide to C++ Web Server Components

This guide will walk you through the basic concepts and steps required for socket programming in C++. Each section includes code snippets with detailed explanations to help you understand the functionality of each component. By going through each step individually, you will be well-prepared to build and understand a C++ web server.

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

    // Close the socket
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

### 4. Accepting Connections

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

### 5. Receiving Data

Receiving data from the client allows the server to handle client requests.

- `recv(clientSocket, buffer, 4096, 0)`: This call receives data from the client.
  - `clientSocket`: The socket file descriptor of the accepted client.
  - `buffer`: A pointer to a buffer to store the received data.
  - `4096`: The maximum number of bytes to read.
  - `0`: Flags (0 means no special options).

#### Code

```cpp
// receive_data.cpp
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
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) <

0) {
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

    // Receive data from the client
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, 4096, 0);
    if (bytesReceived < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        return -1;
    }
    std::cout << "Received: " << std::string(buffer, 0, bytesReceived) << std::endl;

    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
Received: [data from client]
```

#### How to Run

```sh
g++ receive_data.cpp -o receive_data
./receive_data
```

---

### 6. Sending Data

Sending data to the client allows the server to respond to client requests.

- `send(clientSocket, message, strlen(message), 0)`: This call sends data to the client.
  - `clientSocket`: The socket file descriptor of the accepted client.
  - `message`: A pointer to the data to be sent.
  - `strlen(message)`: The length of the data to be sent.
  - `0`: Flags (0 means no special options).

#### Code

```cpp
// send_data.cpp
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
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    // Accept a client connection
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return -1;
    }

    // Send data to the client
    const char* message = "Hello from the server!\n";
    send(clientSocket, message, strlen(message), 0);

    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
Data sent to client
```

#### How to Run

```sh
g++ send_data.cpp -o send_data
./send_data
```

---

### 7. Reading a File

This example shows how to read a file's content into a string using `std::ifstream`.

#### Code

```cpp
// read_file.cpp
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filePath) {
    // Open the file
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    // Read the file's content into a stringstream
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    // Read the content of the file "public/index.html"
    std::string content = readFile("public/index.html");
    // Print the content
    std::cout << content << std::endl;
    return 0;
}
```

#### Expected Output

```
[Content of public/index.html]
```

#### How to Run

```sh
g++ read_file.cpp -o read_file
./read_file
```

---

### 8. Parsing an HTTP Request

This example shows how to parse an HTTP request.

#### Code

```cpp
// parse_http_request.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <map>

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
};

HttpRequest parseRequest(const std::string& request) {
    std::istringstream stream(request);
    HttpRequest req;
    std::string line;

    // Parse the request line
    std::getline(stream, line);
    std::istringstream lineStream(line);
    lineStream >> req.method >> req.path >> req.version;

    // Parse the headers
    while (std::getline(stream, line) && line != "\r") {
        std::istringstream headerStream(line);
        std::string key;
        std::string value;
        std::getline(headerStream, key, ':');
        std::getline(headerStream, value);
        if (!key.empty() && !value.empty()) {
            req.headers[key] = value;
        }
    }

    return req;
}

int main() {
    // Sample raw HTTP request
    std::string rawRequest = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n";
    // Parse the HTTP request
    HttpRequest request = parseRequest(rawRequest);

    // Print the parsed request
    std::cout << "Method: " << request.method << std::endl;
    std::cout << "Path: " << request.path << std::endl;
    std::cout << "Version: " << request.version << std::endl;
    for (const auto& header : request.headers) {
        std::cout << "Header: " << header.first << " = " << header.second << std::endl;
    }

    return 0;
}
```

#### Expected Output

```
Method: GET
Path: /
Version: HTTP/1.1
Header: Host = 127.0.0.1
Header: Connection = close
```

#### How to Run

```sh
g++ parse_http_request.cpp -o parse_http_request
./parse_http_request
```

---

### 9. Parsing and Processing a Text File

This example shows how to read a text file and process its content.

#### Code

```cpp
// parse_text_file.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> parseFile(const std::string& filePath) {
    std::vector<std::string> lines;
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main() {
    std::string filePath = "data.txt";
    std::vector<std::string> lines = parseFile(filePath);

    std::cout << "File content:" << std::endl;
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
    return 0;
}
```

#### Expected Output

```
[Content of data.txt]
```

#### How to Run

```sh
g++ parse_text_file.cpp -o parse_text_file
./parse_text_file
```

Create a `data.txt` file with some sample content for this example.

---

### 10. Reading and Parsing HTTP Body

This example shows how to read and parse the body of an HTTP request.

#### Code

```cpp
// parse_http_body.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <map>

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};

HttpRequest parseRequest(const std::string& request) {
    std::istringstream stream(request);


 HttpRequest req;
    std::string line;

    // Parse the request line
    std::getline(stream, line);
    std::istringstream lineStream(line);
    lineStream >> req.method >> req.path >> req.version;

    // Parse the headers
    while (std::getline(stream, line) && line != "\r") {
        std::istringstream headerStream(line);
        std::string key;
        std::string value;
        std::getline(headerStream, key, ':');
        std::getline(headerStream, value);
        if (!key.empty() && !value.empty()) {
            req.headers[key] = value;
        }
    }

    // Parse the body
    if (std::getline(stream, line) && line.empty()) {
        std::getline(stream, req.body);
    }

    return req;
}

int main() {
    // Sample raw HTTP request with body
    std::string rawRequest = "POST / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\nContent-Length: 11\r\n\r\nHello World";
    // Parse the HTTP request
    HttpRequest request = parseRequest(rawRequest);

    // Print the parsed request
    std::cout << "Method: " << request.method << std::endl;
    std::cout << "Path: " << request.path << std::endl;
    std::cout << "Version: " << request.version << std::endl;
    for (const auto& header : request.headers) {
        std::cout << "Header: " << header.first << " = " << header.second << std::endl;
    }
    std::cout << "Body: " << request.body << std::endl;

    return 0;
}
```

#### Expected Output

```
Method: POST
Path: /
Version: HTTP/1.1
Header: Host = 127.0.0.1
Header: Connection = close
Header: Content-Length = 11
Body: Hello World
```

#### How to Run

```sh
g++ parse_http_body.cpp -o parse_http_body
./parse_http_body
```

---

By running these individual programs, you will gain a deeper understanding of how each component works in the context of a C++ web server. This step-by-step guide provides a clear and concise path to mastering the basics of socket programming, file handling, and HTTP request parsing in C++.

### Resources

- [Building an HTTP Server from Scratch in C++](https://osasazamegbe.medium.com/showing-building-an-http-server-from-scratch-in-c-2da7c0db6cb7)
- [What You Need to Know to Build a Simple HTTP Server from Scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)

---

By following this README, you should be able to understand and build the individual components required for a C++ web server. The guide is designed to provide clear and incremental learning steps to build your confidence and understanding in C++ network programming.
