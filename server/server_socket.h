// server_socket.h

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <string>

class Server_Socket {
private:
  // declare server socket descriptor and socket data members
  int server_fd;
  int server_socket;
  bool status;
  void bindSocket(struct sockaddr_in &address);
  void setSocketOptions();
  void listenForConnections();
  void acceptAndHandleClient(struct sockaddr_in &address);

public:
  Server_Socket();
  // start and stop methods will return status code
  bool Start();
  bool Stop();
  // status method to return status on socket instance
  bool Get_status();
};

#endif // SERVER_SOCKET_H
