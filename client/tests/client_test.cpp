#include "client_socket.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(ClientSocketTest, TestClientConnectToServer) {
  auto mock_connect = [](int, struct sockaddr *, socklen_t) { return 0; };
  EXPECT_TRUE(Client_Socket(mock_connect).ConnectToServer());
}
TEST(ClientSocketTest, TestClientSendMessage) {
  // TODO finish implementation
  auto mock_connect = [](int, struct sockaddr *, socklen_t) { return 0; };
  Client_Socket client = Client_Socket(mock_connect);
  EXPECT_TRUE(client.ConnectToServer());
  // EXPECT_FALSE(client.SendMessage());
}