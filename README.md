# 🗃️ Distributed Key-Value Store in C++

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
Testing Result
```bash
[INFO] Running Distributed Key-Value Store Tests

[INFO] Step 1: SET to Node 9000
OK
OK
OK
OK
OK
[INFO] Step 2: GET from Node 9001 (replica)
[FAIL] GET user1 on port 9001 =>  (expected alice)
[PASS] GET user2 on port 9001 => bob
[PASS] GET user3 on port 9001 => carol
[PASS] GET user4 on port 9001 => dave
[PASS] GET user5 on port 9001 => elena
[INFO] Step 3: SET to Node 9001
OK
OK
OK
OK
OK
[INFO] Step 4: GET from Node 9000 (replica)
[FAIL] GET city1 on port 9000 => Not Found (expected tokyo)
[FAIL] GET city2 on port 9000 => Not Found (expected seoul)
[FAIL] GET city3 on port 9000 => Not Found (expected beijing)
[FAIL] GET city4 on port 9000 => Not Found (expected bangkok)
[FAIL] GET city5 on port 9000 => Not Found (expected jakarta)
[INFO] Step 5: Overwrite key test
OK
[PASS] GET user1 on port 9001 => anthony
[INFO] Step 6: Stress test with 30 keys
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
[PASS] Stress test passed for all 30 keys (9000 ➜ 9001)
[INFO] Step 7: Request non-existent key
[FAIL] GET nokey on port 9000 returned: Not Found

[INFO] ✅ All automated tests completed.
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

## 👨‍💻 Author

Created by **Junxiang Huang (Anthony)**  
💬 Languages: C++, Python, Bahasa, 中文  
🚀 Interested in distributed systems and ML engineering
