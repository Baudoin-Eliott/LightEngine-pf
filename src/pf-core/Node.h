#pragma once
#include <deque>

template<typename T>
struct Node {

    T* data;

    bool visited = false;
    Node* from = nullptr;

    std::deque<Node*> neighbors = {};
};
