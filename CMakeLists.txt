cmake_minimum_required(VERSION 3.16)
project(cpp_key_value_server VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(key_value_server main.cpp keyValueStore.cpp commandParser.cpp tcpServer.cpp
commandExecutor.cpp threadPool.cpp)

target_link_libraries(key_value_server PRIVATE Threads::Threads)