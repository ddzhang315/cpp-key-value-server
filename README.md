# C++ Key-Value Server

A multithreaded in-memory key-value server written in C++17.
The server communicates over TCP using a simple text-based protocol and supports concurrent client connections through a fixed-size thread pool. Clients share a thread-safe in-memory key-value store protected by a mutex.

## Features

- TCP server using POSIX sockets
- Concurrent client handling with a fixed-size thread pool
- Thread-safe shared in-memory key-value store
- Command parsing and input validation
- Persistent client connections with newline-delimited commands
- Partial-send and interrupted-system-call handling
- RAII-based client socket cleanup

## Supported Commands

| Command | Description |
| --- | --- |
| `SET key value` | Insert a new key-value pair or overwrite an existing value |
| `GET key` | Retrieve the value associated with a key |
| `DELETE key` | Delete a key-value pair |
| `CONTAINS key` | Check whether a key exists |
| `SIZE` | Return the number of stored key-value pairs |
| `Q` | Close the client connection |

## Build

### Requirements

- Linux
- C++17-compatible compiler
- CMake

### Build from source

```bash
cmake -S . -B build
cmake --build build
```

### Run the server
```bash
./build/key_value_server
```
The server listens on `127.0.0.1:8080`.

Connect a client using Netcat in a separate terminal:

```bash
nc 127.0.0.1 8080
```
## Example
```text
SET language cpp
Server Response: Set success!

GET language
Server Response: cpp

CONTAINS language
Server Response: Key exists!

SIZE
Server Response: Size is : 1

DELETE language
Server Response: DELETE success!

GET language
Server Response: Item Not Found!

Q
Server Response: GoodBye
```

## Architecture

The server uses a shared in-memory key-value store across all connected clients. Incoming client connections are submitted to a fixed-size thread pool, where worker threads process commands independently. Access to the shared store is synchronized with a mutex.

```text
Client Connections
        |
        v
    TCP Server
        |
        v
    Thread Pool
        |
        v
  Client Handler
        |
        v
  Command Parser
        |
        v
 Command Executor
        |
        v
  KeyValueStore
   (mutex-protected)
```

## Testing

The project currently includes a basic thread-pool concurrency test that verifies task execution across multiple worker threads.

Additional unit and integration tests are planned for the key-value store, command parser, command executor, and TCP server.

## Future Work

- Expand automated unit and integration testing
- Add key expiration (TTL)
- Add persistence to disk
- Add graceful server shutdown
- Add load testing and performance benchmarks
