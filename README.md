# 🗃️ DistKV++: A High-Performance Distributed Key-Value Store in C++

## 📌 Overview

This project implements a **simple distributed key-value store** in C++ using **TCP sockets** and **multithreading**. It mimics a basic version of Redis, where multiple storage nodes communicate to **store, replicate, and retrieve** key-value pairs.

It supports:
- `SET <key> <value>` → Save a key-value pair
- `GET <key>` → Retrieve the value from key
- **Replication** across nodes
- Basic error handling and multithreaded client support

## 🎯 Motivation

In real-world systems, relying on a single storage server is risky:
- If one server fails, **all data might be lost** or **service becomes unavailable**.
- By distributing and replicating data across multiple nodes, the system becomes **fault-tolerant**, **scalable**, and **resilient**.

This project helps you learn:
- Distributed system concepts
- Socket programming in C++
- Multithreading
- Data replication



- Each node is a TCP server.
- When a `SET` command is received, the node stores it **and replicates to peer nodes**.
- `GET` looks up the local storage.

## 📁 File Structure
````
.
├── main.cpp # Entry point
├── server.cpp/.h # TCP server & request handling
├── storage.cpp/.h # In-memory key-value storage
├── replica.cpp/.h # Replication logic
├── test.sh # Auto test script
├── README.md # This file
````

## 🔧 Build Instructions

Requires a C++ compiler (e.g., g++) with C++11+ and pthreads.

```bash
g++ main.cpp server.cpp storage.cpp replica.cpp -o kv_store -pthread -std=c++17-pthread
`````

## 🚀 Running the System
In terminal 1:

```bash
./kv_store 9000

````
In Terminal 2 :
```bash
./kv_store 9001

````

## 🧪 Testing Manually
Use ```netcat (nc)``` to send commands:
```bash
# Open terminal
nc localhost 9000
SET name john
OK
GET name
john
````

## ✅ Automated Testing
``` bash 
chmod +x test.sh
./test.sh
```

## 🧪 Automated Testing

This will:

- Test basic set/get  
- Test replication between nodes  
- Stress test 30 keys  
- Check edge cases like missing keys  

## ❗ Known Issues

- Replication is asynchronous and fire-and-forget, no retry on failure.  
- Only supports two nodes, but architecture allows for easy expansion.  
- No data persistence to disk.  
- No conflict resolution if two nodes set the same key differently.  

## 💡 Ideas for Improvement

- Add master node for coordination  
- Implement consistency models (eventual, strong, quorum)  
- Add hashing or sharding  
- Add persistence (e.g., to file or SQLite)  
- Add CLI client  
