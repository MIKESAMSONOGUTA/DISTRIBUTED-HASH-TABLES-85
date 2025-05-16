#include "Visualizer.h"
#include "Node.h"
#include <iostream>
#include <fstream>
void Visualizer::printNodeStatus(const std::vector<Node*>& nodes) {
    std::cout << "\n--- Node Key Distribution ---\n";
    for (const auto& node : nodes) {
        node->printStatus();
    }
}