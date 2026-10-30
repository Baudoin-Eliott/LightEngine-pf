#pragma once
#include <vector>
#include <limits>

template<typename T>
struct Node {

    T* data;

    bool visited = false;
    Node* from = nullptr;
    float dist = std::numeric_limits<float>::infinity();

    std::vector<Node*> neighbors = {};
};
