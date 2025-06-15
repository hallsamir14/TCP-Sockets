#include "server_socket.h"
#include <arpa/inet.h>
#include <cstring>
#include <glog/logging.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  // Configure and initialize logger
  FLAGS_logtostderr = 1; // Log all messages to stderr
  google::InitGoogleLogging("server_main");

  Server_Socket server = Server_Socket();

  server.Start();
  server.Stop();

  return 0;
}