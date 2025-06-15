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

Client_Socket::Client_Socket() {
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd < 0) {
    throw std::runtime_error("Socket creation error");
  }
}

// TODO:define param to allow server IP and Port to be passed as argument to
// connectToServer()
void Client_Socket::ConnectToServer() {
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid address/ Address not supported");
  }

  if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    throw std::runtime_error("Connection failed");
  }

  LOG(INFO) << "Connected to Server" << std::endl;
}

// TODO:define param to allow message to be passed as argument to sendMessage()
void Client_Socket::SendMessage() {
  std::string message = "Client Message";
  char buffer[BUFFER_SIZE] = {0};

  send(client_fd, message.c_str(), message.length(), 0);
  LOG(INFO) << "Message Sent to Server" << std::endl;
  int valread = read(client_fd, buffer, BUFFER_SIZE);
  if (valread < 0) {
    throw std::runtime_error("Read error");
  }
  LOG(INFO) << "Server Message:" << buffer << std::endl;
}
