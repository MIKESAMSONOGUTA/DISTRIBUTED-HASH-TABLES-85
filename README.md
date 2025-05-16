Distributed Hash Table (DHT) in C++

This project is a simulation of a **Distributed Hash Table (DHT)** implemented in C++ using Visual Studio 2022. It demonstrates how nodes can be distributed in a hash ring, store and replicate key-value pairs, handle dynamic node joining, and maintain system health via heartbeats.

## 🔧 Features

Node Creation
  Dynamically create and add nodes to the hash ring.

Hash Ring Management
  Consistent hashing with virtual nodes to ensure even key distribution.

Data Storage & Replication 
  Keys are distributed and replicated to improve fault tolerance.

Heartbeat Mechanism
  Nodes periodically send heartbeats to monitor availability.

Key Redistribution
  Balancer redistributes keys when new nodes join.

       Technologies

- C++17 (required for structured bindings)
- Visual Studio 2022
- Standard Template Library (STL)

How to Run

1. Open the solution in **Visual Studio 2022**.
2. Set `main.cpp` as the startup file.
3. Press `Ctrl + F5` to build and run without debugging.
4. Observe node behavior, data replication, and heartbeat output in the console.


