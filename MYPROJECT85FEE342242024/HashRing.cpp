#include "HashRing.h"
#include "Node.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

HashRing::HashRing(int virtualNodes) : virtualNodeCount(virtualNodes) {}

int HashRing::computeHash(const std::string& key) {
    return Utils::hashKey(key);
}

// Add real node with virtual nodes
void HashRing::addNode(Node* node) {
    for (int i = 0; i < virtualNodeCount; ++i) {
        std::string virtualId = node->nodeId + "#v" + std::to_string(i);
        int hash = computeHash(virtualId);
        ring[hash] = node;
        nodeHashMap[node->nodeId].push_back(hash);
    }
}

// Remove node and its virtual nodes
void HashRing::removeNode(const std::string& nodeId) {
    auto it = nodeHashMap.find(nodeId);
    if (it != nodeHashMap.end()) {
        for (int hash : it->second) {
            ring.erase(hash);
        }
        nodeHashMap.erase(it);
    }
}

// Get primary node for a key
Node* HashRing::getNodeForKey(const std::string& key) {
    if (ring.empty()) return nullptr;

    int hash = computeHash(key);
    auto it = ring.lower_bound(hash);
    if (it == ring.end()) it = ring.begin(); // wrap around
    return it->second;
}

// Get list of next N distinct replicas after a node
std::vector<Node*> HashRing::getReplicas(Node* origin, const std::vector<Node*>& nodes, int replicaCount) {
    std::vector<Node*> replicas;
    std::vector<int> sortedHashes;
    for (const auto& [hash, node] : ring)
        sortedHashes.push_back(hash);

    std::sort(sortedHashes.begin(), sortedHashes.end());

    Node* prev = origin;
    int found = 0;

    for (const int& h : sortedHashes) {
        Node* node = ring[h];
        if (node != prev && std::find(replicas.begin(), replicas.end(), node) == replicas.end()) {
            replicas.push_back(node);
            prev = node;
            if (++found == replicaCount) break;
        }
    }

    return replicas;
}
