cmake_minimum_required(VERSION 3.16)
project(cpp_key_value_server VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)
enable_testing()

add_executable(key_value_server main.cpp keyValueStore.cpp commandParser.cpp tcpServer.cpp
commandExecutor.cpp threadPool.cpp)

add_executable(thread_pool_test threadPoolTest.cpp threadPool.cpp)
add_executable(key_value_store_test keyValueStore.cpp keyValueStoreTest.cpp)

add_test(NAME ThreadPoolTest COMMAND thread_pool_test)
add_test(NAME KeyValueStoreTest COMMAND key_value_store_test)

target_link_libraries(key_value_server PRIVATE Threads::Threads)
target_link_libraries(thread_pool_test PRIVATE Threads::Threads)
target_link_libraries(key_value_store_test PRIVATE Threads::Threads)
