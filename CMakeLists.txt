cmake_minimum_required(VERSION 3.10)
project(SocketApps)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Custom target to run the setup script
add_custom_target(setup
    COMMAND ${CMAKE_COMMAND} -E echo "Running setup script to install required packages..."
    COMMAND ${CMAKE_COMMAND} -E env bash ${PROJECT_SOURCE_DIR}/scripts/debian_packages_install.sh
)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/client)
include_directories(${PROJECT_SOURCE_DIR}/server)

# Source files
set(CLIENT_SRC
    ${PROJECT_SOURCE_DIR}/client/client_main.cpp
    ${PROJECT_SOURCE_DIR}/client/client_socket.cpp
)
set(SERVER_SRC
    ${PROJECT_SOURCE_DIR}/server/server_main.cpp
    ${PROJECT_SOURCE_DIR}/server/server_socket.cpp
)

# Output binaries
set(CLIENT_BIN ${PROJECT_SOURCE_DIR}/client/client.bin)
set(SERVER_BIN ${PROJECT_SOURCE_DIR}/server/server.bin)

# Find glog
find_package(glog REQUIRED)

# Client executable
add_executable(client ${CLIENT_SRC})
target_link_libraries(client glog::glog)

# Server executable
add_executable(server ${SERVER_SRC})
target_link_libraries(server glog::glog)

set_target_properties(client PROPERTIES OUTPUT_NAME "client.bin")
set_target_properties(server PROPERTIES OUTPUT_NAME "server.bin")

# Custom clean target
add_custom_target(custom_clean
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean.cmake
)
file(WRITE ${CMAKE_BINARY_DIR}/cmake_clean.cmake
"file(REMOVE_RECURSE ${CLIENT_BIN} ${SERVER_BIN})\n"
)

# GoogleTest integration
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Client tests
add_executable(client_test client/tests/client_test.cpp client/client_socket.cpp)
target_link_libraries(client_test gtest_main glog::glog)
add_test(NAME client_test COMMAND client_test)

# Server tests
add_executable(server_test server/tests/server_test.cpp server/server_socket.cpp)
target_link_libraries(server_test gtest_main glog::glog)
add_test(NAME server_test COMMAND server_test)

# Run target (optional, launches server and client in new terminals)
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E echo "Launching server and client in separate terminals..."
    COMMAND gnome-terminal -- bash -c "${SERVER_BIN}; exec bash"
    COMMAND gnome-terminal -- bash -c "${CLIENT_BIN}; exec bash"
    DEPENDS server client
)