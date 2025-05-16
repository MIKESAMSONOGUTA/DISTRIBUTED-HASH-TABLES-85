#pragma once
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <ctime>

class HashRing;
class Node;

class Node {
public:
    std::string nodeId;
    std::map<std::string, std::string> dataStore;

    Node(const std::string& id);

    void joinRing(HashRing& ring);
    void leaveRing(HashRing& ring);

    void storeData(const std::string& key, const std::string& value);
    std::string getData(const std::string& key);

    void replicateData(const std::string& key, const std::string& value,
        HashRing& ring, const std::vector<Node*>& nodes,
        int replicaCount);

    void printStatus() const;
    int keyCount() const;

    void sendDataToNode(Node* to, const std::string& key, const std::string& value);
    void requestDataFromNode(Node* to, const std::string& key); 
    void startHeartbeatMonitor(std::vector<Node*>& nodes);
    bool checkHeartbeat();
    void sendHeartbeat();
    void clearData();
    std::string getId() const;
    const std::map<std::string, std::string>& getAllData() const;

        
    private:
        bool isAlive = true;
        std::chrono::steady_clock::time_point lastHeartbeatTime;
        std::string id;
        

};

