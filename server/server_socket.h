// server_socket.h

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <functional>
#include <sys/socket.h>

class Server_Socket {
private:
  /*
  server_fd is the file descriptor for the listening server socket.
  It is created by the socket() system call and is used to listen for incoming
  client connections (typically with bind(), listen(), and accept()).
  - - - The main listening socket for the server (waits for connections).
  */
  int server_fd;

  /*
  server_socket holds the file descriptor (an integer) returned by the accept()
  system call. It represents the connection to a specific client. Each time a
  client connects, accept() returns a new socket file descriptor, which is
  stored in server_socket and used for communication with that client.
  - - - The socket for a specific client connection (used for data exchange with
  that client).
  */
  int server_socket;

  /*
  status is used as a flag or state indicator for the server socket object.
  For example, it might indicate whether the server is currently running (1 for
  active, 0 for inactive), or track the current state of the server (e.g.,
  initialized, listening, closed). It does not represent a socket or connection,
  but rather the operational state of the server instance.
  - - - Tracks the state or activity of the server as a whole.
  */
  bool status;

  /*
  bindSocket method binds the server socket to a specified network address,
  represented by the sockaddr_in structure passed by reference. This operation
  is used to associate the socket with a specific port and IP address for
  listening to incoming connections. If the binding fails, it throws a
  std::runtime_error exception
  */
  void bind_socket(struct sockaddr_in &address);

  /*
  setSocketOptions method configures socket options for the server socket,
  enabling address and port reuse by using the setsockopt function.
  If the configuration fails, it throws a std::runtime_error exception.
  */
  void set_socket_options();

  /*
  The Server_Socket::listenForConnections method initiates the server socket to
  listen for incoming connections, with a backlog of 3. If the listen system
  call fails, it throws a std::runtime_error exception.
  */
  void listen_for_connections();

  /*
  The Server_Socket::acceptAndHandleClient method accepts a client connection on
  a server socket using the provided sockaddr_in address, reads an inbound
  message from the client, logs it, and sends a predefined server message back
  to the client while logging the outbound message. If the connection acceptance
  fails, it throws a std::runtime_error exception.
  */
  void accept_and_handle_client(struct sockaddr_in &address);

  /*
  acceptFunc_ is a callable object (std::function) that encapsulates the behavior of the accept system call.
  By default, it points to the standard ::accept function, but it can be replaced with a custom implementation,
  such as a mock function for testing. This enables dependency injection, allowing the accept logic to be
  customized or simulated without modifying the Server_Socket class itself. The injected function should match
  the signature of the standard accept call: int(int sockfd, struct sockaddr *addr, socklen_t *addrlen).
  */
  std::function<int(int, struct sockaddr*, socklen_t*)> acceptFunc_;

public:
  /*
  Server_Socket() constructor initializes a Server_Socket object
  by creating a socket with the AF_INET address family and SOCK_STREAM type.
  If the socket creation fails, it throws a std::runtime_error exception.
  */
  Server_Socket(std::function<int(int, struct sockaddr*, socklen_t*)> acceptFunc = ::accept);

  /*
  Start method initializes and starts a server socket by configuring its
  address, setting socket options, binding it, and listening for incoming
  connections. If the server socket instance is already active, a log message
  indicating status is sent to stdout.
  */
  void Start();

  /*
  Stop method is responsible for stopping the server socket by closing it if the
  socket is active. If the socket is not active, a log message indicating status
  is sent to stdout.
  */
  void Stop();

  /*
  Get_status method returns the current value of the status member variable,
  indicating the status of the server socket instance
  */
  bool Get_status();
};

#endif // SERVER_SOCKET_H
