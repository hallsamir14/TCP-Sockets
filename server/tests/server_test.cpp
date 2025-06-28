#include <gtest/gtest.h>
#include "server_socket.h"

TEST(ServerSocketTest, StartSetsStatusTrue) {
    Server_Socket server;
    server.Start();
    EXPECT_TRUE(server.Get_status());
}

