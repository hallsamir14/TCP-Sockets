#include "server_socket.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(ServerSocketTest, TestServerSocketStart) {
  // TODO complete impolementation
  auto mock_accept = [](int, struct sockaddr*, socklen_t*) { return 42; };
  Server_Socket server(mock_accept);
  EXPECT_NO_THROW(server.Start());
  EXPECT_EQ(server.Get_status(),1);
}

TEST(ServerSocketTest, TestServerSocketStop) {
  // TODO complete impolementation
  auto mock_accept = [](int, struct sockaddr*, socklen_t*) { return 42; };
  Server_Socket server(mock_accept);
  server.Start();
  EXPECT_EQ(server.Get_status(),1);
  EXPECT_NO_THROW(server.Stop());
  EXPECT_EQ(server.Get_status(),0);
}
