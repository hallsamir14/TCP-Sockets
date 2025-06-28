// server_socket.h

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <string>

class Server_Socket {
private:
  /*
  server_fd is the file descriptor for the listening server socket. 
  It is created by the socket() system call and is used to listen for incoming client connections 
  (typically with bind(), listen(), and accept()).
  - - - The main listening socket for the server (waits for connections).
  */
  int server_fd;

  /* 
  server_socket holds the file descriptor (an integer) returned by the accept() system call. 
  It represents the connection to a specific client. 
  Each time a client connects, accept() returns a new socket file descriptor, 
  which is stored in server_socket and used for communication with that client.
  - - - The socket for a specific client connection (used for data exchange with that client).
  */
  int server_socket;
  /*
  status is used as a flag or state indicator for the server socket object. 
  For example, it might indicate whether the server is currently running (1 for active, 0 for inactive), 
  or track the current state of the server (e.g., initialized, listening, closed). 
  It does not represent a socket or connection, but rather the operational state of the server instance.
  - - - Tracks the state or activity of the server as a whole.
  */
  bool status;

  void bindSocket(struct sockaddr_in &address);
  void setSocketOptions();
  void listenForConnections();
  void acceptAndHandleClient(struct sockaddr_in &address);

public:
  Server_Socket();
  // start method will ...
  void Start();
  // stop moethod will ...
  void Stop();
  // status method to return status on socket instance
  bool Get_status();
};

#endif // SERVER_SOCKET_H
