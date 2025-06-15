#include "client_socket.h"
#include <glog/logging.h>

// Driver code for client socket

int main(int argc, char *argv[]) {
  // Configure and initialize logger
  FLAGS_logtostderr = 1; // Log all messages to stderr
  google::InitGoogleLogging("server_main");
  Client_Socket client = Client_Socket();
  client.ConnectToServer();
  client.SendMessage();
  return 0;
}