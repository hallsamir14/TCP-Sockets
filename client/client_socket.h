/*
Client_Socket() class
*/
#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <functional>
#include <sys/socket.h>

class Client_Socket {
private:
  /*
  status Indicates the current connection status of the client socket process.
  True if connected to the server, false otherwise.
  */
  bool status;

  /*
  File descriptor for client socket.
  Used to identify and manage the socket connection to the server.
  */
  int client_fd;

  /*
  Mock connect function,defaults to standard std::connect function.
  Object or value can be injected for custom implementation
  The injected function should match the signature of the standard accept call:
  int(int __fd, struct sockaddr* , socklen_t).
  */
  std::function<int(int, struct sockaddr *, socklen_t)> connectFunc_;

public:
  /*
  Constructor. Initializes the client socket object and sets up any required
  resources.
  */
  Client_Socket(std::function<int(int, struct sockaddr *, socklen_t)>
                    connectFunc = ::connect);

  /*
  Attempts to connect the client socket to the server.
  Returns true if the connection is successful, false otherwise.
  */
  bool ConnectToServer();

  /*
  Sends a message to the server and optionally receives a response.
  Returns true if the message is sent and a response is received successfully,
  false otherwise.
  */
  bool SendMessage();
};

#endif // CLIENT_SOCKET_H