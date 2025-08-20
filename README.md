# KeyMesh

[![C++][cpp-badge]][cpp-url]
[![License][license-badge]][license-url]

*👀 High-performance distributed key-value store in C++*

## Overview

This project implements a **distributed key-value store** in C++ using **TCP sockets** and **multithreading**, mimicking a simplified Redis. Multiple nodes communicate to **store, replicate, and retrieve** key-value pairs.

Supports:

* `SET <key> <value>` → Save a key-value pair
* `GET <key>` → Retrieve value from key
* **Replication** across nodes
* Basic error handling and multithreaded client support

## Motivation

Single server storage is risky due to failures. Distributing and replicating data across nodes enhances **fault tolerance**, **scalability**, and **resilience**. This project introduces concepts like TCP socket programming, multithreading, and replication in C++.

## File Structure

```
.
├── main.cpp          # Entry point
├── server.cpp/.h     # TCP server & request handling
├── storage.cpp/.h    # In-memory key-value storage
├── replica.cpp/.h    # Replication logic
├── test.sh           # Automated test script
├── README.md         # This file
```

## Build Instructions

Requires a C++11+ compiler with pthreads.

```bash
g++ main.cpp server.cpp storage.cpp replica.cpp -o kv_store -pthread -std=c++17
```

## Running the System

In terminal 1:

```bash
./kv_store 9000
```

In terminal 2:

```bash
./kv_store 9001
```

## Manual Testing

Use `netcat (nc)` to send commands:

```bash
nc localhost 9000
SET name john
OK
GET name
john
```

## Automated Testing

```bash
chmod +x test.sh
./test.sh
```

Tests include:

* Basic set/get
* Replication between nodes
* Stress test with multiple keys
* Edge cases (missing keys)

## Known Issues

* Replication is asynchronous, no retry on failure.
* Only supports two nodes (easy to expand).
* No persistence to disk.
* No conflict resolution for concurrent key sets.

## Ideas for Improvement

* Add master node for coordination
* Implement consistency models (eventual, strong, quorum)
* Add hashing/sharding
* Add persistence (file or SQLite)
* Add CLI client

---

[cpp-badge]: https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white
[cpp-url]: https://isocpp.org/
[license-badge]: https://img.shields.io/badge/license-MIT-green
[license-url]: https://opensource.org/licenses/MIT
