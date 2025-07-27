#include "server_socket.h"
#include <arpa/inet.h>
#include <glog/logging.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "127.0.0.2"
#define BUFFER_SIZE 1024
#define MAX_REQUEST 3

void Server_Socket::bind_socket(struct sockaddr_in &address) {
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    throw std::runtime_error("Bind failed");
  }
}

void Server_Socket::set_socket_options() {
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)) < 0) {
    throw std::runtime_error("Set socket options failed");
  }
}

void Server_Socket::listen_for_connections() {
  if (listen(server_fd, MAX_REQUEST) < 0) {
    throw std::runtime_error("Listen failed");
  }
}

void Server_Socket::accept_and_handle_client(struct sockaddr_in &address) {
  socklen_t addrlen = sizeof(address);
  server_socket = acceptFunc_(server_fd, (struct sockaddr *)&address, &addrlen);
  if (server_socket < 0) {
    throw std::runtime_error("Accept failed");
  }

  char buffer[BUFFER_SIZE] = {0};
  std::string message = "Server Message";

  read(server_socket, buffer, sizeof(buffer) - 1);
  LOG(INFO) << "[Inbound Message]:" << buffer << std::endl;

  send(server_socket, message.c_str(), message.length(), 0);
  LOG(INFO) << "[Outbound Message]:"
            << "Message:" << message << std::endl;
}

Server_Socket::Server_Socket(std::function<int(int, struct sockaddr*, socklen_t*)> acceptFunc)
: acceptFunc_(acceptFunc), server_fd(-1), server_socket(-1), status(0) {

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  status = 0;
  if (server_fd < 0) {
    throw std::runtime_error("Socket creation failed");
  }
}

void Server_Socket::Start() {

  if (status == 0) {
    LOG(INFO) << "Starting Server Socket" << std::endl;
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_IP);
    address.sin_port = htons(PORT);

    LOG(INFO) << "Address Type:" << address.sin_family << std::endl;
    LOG(INFO) << "Host IP:" << SERVER_IP << std::endl;
    LOG(INFO) << "Host PORT:" << PORT << std::endl;

    status = 1;
    set_socket_options();
    bind_socket(address);
    listen_for_connections();

    LOG(INFO) << "Server Listening..." << std::endl;

    accept_and_handle_client(address);
  }

  else if (status == 1) {
    LOG(INFO) << "Server Socket Is Already Active" << std::endl;
  }
}

void Server_Socket::Stop() {
  if (status == 1) {
    close(server_socket);
    LOG(INFO) << "Closing Server Socket" << std::endl;
    status = 0;
  }

  else if (status == 0) {
    LOG(INFO) << "Socket Is Not Active" << std::endl;
  }
}

bool Server_Socket::Get_status() { return status; }
