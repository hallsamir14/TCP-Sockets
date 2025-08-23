/*
Client_Socket() class
*/
#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>

class Client_Socket {
private:
  bool status;
  int client_fd;

public:
  Client_Socket();
  bool ConnectToServer();
  bool SendMessage();
};

#endif // CLIENT_SOCKET_H