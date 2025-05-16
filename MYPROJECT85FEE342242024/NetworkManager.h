#pragma once
#include <string>
#include "Node.h"

class NetworkManager {
public:
    static void sendData(const std::string& from, const std::string& to,const std::string& key, const std::string& value);
    static void sendData(Node* from, Node* to, const std::string& key, const std::string& value);
    static void requestData(Node* from, Node* to, const std::string& key);
};
