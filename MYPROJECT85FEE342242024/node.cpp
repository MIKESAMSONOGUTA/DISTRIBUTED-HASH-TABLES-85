#pragma warning(push)
#pragma warning(disable : 26495)
#include "Node.h"
#include "HashRing.h"
#include <iostream>
#include "NetworkManager.h"
#include <ctime>
#include <thread>
#include <chrono>

Node::Node(const std::string& id)
    : nodeId(id), lastHeartbeatTime(std::chrono::steady_clock::now()) {
}


// Join the hash ring
void Node::joinRing(HashRing& ring) {
    ring.addNode(this);
    std::cout << nodeId << " joined the ring.\n";
}

// Leave the hash ring
void Node::leaveRing(HashRing& ring) {
    ring.removeNode(nodeId);
    std::cout << nodeId << " left the ring.\n";
}

// Store key-value data
void Node::storeData(const std::string& key, const std::string& value) {
    dataStore[key] = value;
    std::cout << nodeId << " stored [" << key << "] = " << value << "\n";
}

// Retrieve stored value
std::string Node::getData(const std::string& key) {
    if (dataStore.find(key) != dataStore.end()) {
        return dataStore[key];
    }
    return "";
}

// Replicate data to backup nodes
void Node::replicateData(const std::string& key, const std::string& value,
    HashRing& ring, const std::vector<Node*>& nodes,
    int replicaCount) {
    auto replicas = ring.getReplicas(this, nodes, replicaCount);
    for (Node* replica : replicas) {
        if (replica && replica != this) {
            replica->storeData(key, value);
            std::cout << nodeId << " replicated [" << key << "] to " << replica->nodeId << "\n";
        }
    }
}

// Print node data status
void Node::printStatus() const {
    std::cout << nodeId << " holds:\n";
    for (const auto& [key, value] : dataStore) {
        std::cout << "  " << key << " -> " << value << "\n";
    }
}

// Return number of keys stored
int Node::keyCount() const {
    return static_cast<int>(dataStore.size());
}
// Simulate sending data to another node
void Node::sendDataToNode(Node* to, const std::string& key, const std::string& value) {
    NetworkManager::sendData(this->getId(), to->getId(), key, value);
}

// Simulate requesting data from another node
void Node::requestDataFromNode(Node* to, const std::string& key) {
    NetworkManager::requestData(this, to, key);
}

void Node::startHeartbeatMonitor(std::vector<Node*>& nodes) {
    // Start monitoring other nodes' heartbeats
    while (isAlive) {
        for (auto& node : nodes) {
            if (node != this && !node->checkHeartbeat()) {
                std::cout << "[Failure Detection] Node " << node->nodeId << " is down!" << std::endl;
                // Trigger recovery/rebalancing
                // Implement recovery logic here
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Sleep for 5 seconds between checks
    }
}

bool Node::checkHeartbeat() {
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastHeartbeatTime);
    return duration.count() <= 10;
}


void Node::sendHeartbeat() {
    lastHeartbeatTime = std::chrono::steady_clock::now();
    std::cout << "[Heartbeat] Node " << nodeId << " sent a heartbeat signal.\n";
}
void Node::clearData() {
    dataStore.clear();  // Assuming dataStore is a map or similar container
}
std::string Node::getId() const {
    return id;
    }
const std::map<std::string, std::string>& Node::getAllData() const {
    return dataStore;  // assuming dataStore is std::map<std::string, std::string>
}

