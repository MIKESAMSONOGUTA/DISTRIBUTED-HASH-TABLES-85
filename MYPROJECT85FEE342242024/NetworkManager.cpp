#include "NetworkManager.h"
#include <iostream>
#include <thread>
#include <string>
void NetworkManager::sendData(const std::string& from, const std::string& to, const std::string& key, const std::string& value) {
    std::cout << "[NetworkManager] Sending data from " << from << " to " << to
        << ": key=" << key << ", value=" << value << std::endl;
}

// Implement requestData method
void NetworkManager::requestData(Node* from, Node* to, const std::string& key) {
    std::string value = to->getData(key);
    if (value.empty()) {
        std::cout << "[Network] " << from->nodeId << " requested " << key << " from " << to->nodeId << ", but data not found.\n";
    }
    else {
        std::cout << "[Network] " << from->nodeId << " requested " << key << " from " << to->nodeId << ", received: " << value << "\n";
    }

  
    }