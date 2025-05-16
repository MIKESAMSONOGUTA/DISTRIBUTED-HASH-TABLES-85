#include "Balancer.h"
#include "Node.h"
#include "HashRing.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

void Balancer::redistributeKeys(std::vector<Node*>& nodes, HashRing& ring) {
    // Optional: sort nodes by key count
    std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return a->keyCount() > b->keyCount();
        });

    if (nodes.empty()) return;

    Node* mostLoaded = nodes.front();
    Node* leastLoaded = nodes.back();

    if (mostLoaded->keyCount() - leastLoaded->keyCount() < 2) return; // Balance OK

    std::map<std::string, std::string> toMove;

    // Transfer some keys from most loaded to least loaded
    int transferCount = (mostLoaded->keyCount() - leastLoaded->keyCount()) / 2;
    int moved = 0;

    for (const auto& [key, value] : mostLoaded->dataStore) {
        if (moved++ >= transferCount) break;
        leastLoaded->storeData(key, value);
        toMove[key] = value;
    }

    for (const auto& [key, _] : toMove) {
        mostLoaded->dataStore.erase(key);
    }

    std::cout << "[Balancer] Redistributed " << moved << " keys.\n";
}