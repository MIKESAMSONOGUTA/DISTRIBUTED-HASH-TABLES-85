#pragma once
#include <vector>
#ifndef BALANCER_H
#define BALANCER_H


class Node;
class HashRing;

class Balancer {
public:
    static void redistributeKeys(std::vector<Node*>& nodes, HashRing& ring);
#endif
};
