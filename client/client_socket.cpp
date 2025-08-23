// client_socket.cpp

#include "client_socket.h"
#include <arpa/inet.h>
#include <glog/logging.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "127.0.0.2"
#define BUFFER_SIZE 1024

/*
Client node class that defines an instance of a client-side socket.
*/

Client_Socket::Client_Socket(
    std::function<int(int, struct sockaddr *, socklen_t)> connectFunc)
    : connectFunc_(connectFunc), client_fd(-1), status(0) {
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd < 0) {
    throw std::runtime_error("Socket creation error");
  }
}

// connectToServer()
bool Client_Socket::ConnectToServer() {
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid address/ Address not supported");
    return 0;
  }

  if (connectFunc_(client_fd, (struct sockaddr *)&server_addr,
                   sizeof(server_addr)) < 0) {
    throw std::runtime_error("Connection failed");
    return 0;
  }

  LOG(INFO) << "Connected to Server" << std::endl;
  return 1;
}

bool Client_Socket::SendMessage() {
  /*
  TODO refactor to customize behavior of 'send' function
  Something here is causeing an exception/interrupt for unit test case
  */
  std::string message = "Client Message";
  char buffer[BUFFER_SIZE] = {0};

  send(client_fd, message.c_str(), message.length(), 0);
  LOG(INFO) << "Message Sent to Server" << std::endl;
  int valread = read(client_fd, buffer, BUFFER_SIZE);
  if (valread < 0) {
    throw std::runtime_error("Read error");
    return 0;
  }
  LOG(INFO) << "Server Message:" << buffer << std::endl;
  return 1;
}
