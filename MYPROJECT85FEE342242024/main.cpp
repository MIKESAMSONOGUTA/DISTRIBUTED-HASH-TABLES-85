#include <iostream>
#include <vector>
#include "Node.h"
#include "HashRing.h"
#include "Balancer.h"
#include <thread>
#include <chrono>
#include "NetworkManager.h"


int main() {
    // Step 1: Setup
    HashRing ring;
    std::vector<Node*> nodes;

    // Step 2: Add initial nodes to the ring
    Node* nodeA = new Node("NodeA");
    Node* nodeB = new Node("NodeB");
    nodes.push_back(nodeA);
    nodes.push_back(nodeB);

    nodeA->joinRing(ring);
    nodeB->joinRing(ring);

    // Step 3: Insert keys
    nodeA->storeData("apple", "red");
    nodeA->storeData("banana", "yellow");

    // Step 4: Replication
    nodeA->replicateData("apple", "red", ring, nodes, 2);

    // Step 5: Simulate network server start (mocked)
    // nodeA->startServer(...); // if implemented

    // Step 6: Heartbeat monitoring (mocked)
    // nodeA->startHeartbeatMonitor(nodes);

    // Step 7: Load balancing
    Balancer::redistributeKeys(nodes, ring);

    // Step 8: Visualization (basic)
    std::cout << "\n--- Node Data ---\n";
    for (auto node : nodes)
        node->printStatus();


    // Cleanup
    for (auto node : nodes)
        delete node;

    return 0;
}