#pragma once
#include <map>
#include <string>
#include <vector>

class Node;

class HashRing {
public:
    HashRing(int virtualNodes = 3); // default: 3 virtual nodes per physical node

    void addNode(Node* node);
    void removeNode(const std::string& nodeId);
    Node* getNodeForKey(const std::string& key);

    std::vector<Node*> getReplicas(Node* origin, const std::vector<Node*>& nodes, int replicaCount);

private:
    std::map<int, Node*> ring; // hash -> node
    std::map<std::string, std::vector<int>> nodeHashMap; // nodeId -> virtual hashes
    int virtualNodeCount;

    int computeHash(const std::string& key);
};
