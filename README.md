# Socket Applications

TCP Sockets are a foundational client-server modeled implemenation of TCP using socket programming. Various versions of this project can serve as a base for more complex TCP socket-based implementations.

![Alt text](image.png)

## Features

- **Client-Server Communication**: Establishes a connection between a client and a server using TCP sockets.
- **Message Exchange**: Allows the client to send messages to the server and receive responses.
- **Error Handling**: Includes basic error handling for socket operations.
- **Logging**: Integrates Google Logging Library (glog) for logging messages and errors.

## Project Structure

The project is organized into the following directories and files:

    BasicSocket/ 
    ├── client/ 
    |    ├── client_main.cpp │ 
    |    ├── client_socket.cpp │ 
    |    └── client_socket.h 
    ├── server/ 
    |    ├── server_main.cpp │ 
    |    ├── server_socket.cpp │ 
    |    └── server_socket.h 
    ├── .gitignore 
    ├── CMakeLists.txt
    └── README.md


### Client

- **client_main.cpp**: The entry point for the client application. It creates a `Client_Socket` object, connects to the server, and sends a message.
- **client_socket.cpp**: Implements the `Client_Socket` class, which handles socket creation, connection to the server, and message sending.
- **client_socket.h**: Declares the `Client_Socket` class and its methods.

### Server

- **server_main.cpp**: The entry point for the server application. It creates a `Server_Socket` object and starts the server.
- **server_socket.cpp**: Implements the `Server_Socket` class, which handles socket creation, binding, listening for connections, and handling client messages.
- **server_socket.h**: Declares the `Server_Socket` class and its methods.

## Build and Run Source

**Create Build Directory**
```
mkdir build
cd build
```

**Generate Build Files with CMake**
```
cmake ..
```

**Run Setup Script**
```
cmake --build . --target setup
```

**Build Project**
```
make
```

**Clean Build Artifacts**
```
make custom_clean
```

**Run Server (w/Output)**
```
./server.bin
```

**Run Server (No Output)**
```
./server.bin > /dev/null 2>&1 &
```

**Run Client**
```
./client.bin
```

**Cleanup Server Process**
```
killall server.bin
```


## Developer Guide

**Supported Address Families/Types**

| Address Family Arg Value | Description                    |
|--------------------------|--------------------------------|
| AF_UNSPEC       0        | Unspecified                    |
| AF_UNIX         1        | Unix domain sockets            |
| AF_INET         2        | Internet IP Protocol           |
| AF_AX25         3        | Amateur Radio AX.25            |
| AF_IPX          4        | Novell IPX                     |
| AF_APPLETALK    5        | Appletalk DDP                  |
| AF_NETROM       6        | Amateur radio NetROM           |
| AF_BRIDGE       7        | Multiprotocol bridge           |
| AF_AAL5         8        | Reserved for Werner's ATM      |
| AF_X25          9        | Reserved for X.25 project      |
| AF_INET6        10       | IP version 6                   |
| AF_MAX          12       | For now..                      |