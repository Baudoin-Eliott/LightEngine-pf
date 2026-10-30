#pragma once
#include "Node.h"

//GetPathV1
#include <deque>

//GetPathV2
#include "BinaryHeap.h"


namespace pf {
    template<typename T>
    Node<T>* GetPath(Node<T>* _start, Node<T>* _end) {
        std::deque<Node<T>*> nodes;
        _start->visited = true;
        nodes.push_back(_start);

        while (nodes.empty() == false) {
                
            Node<T>* n = nodes.front();
            nodes.pop_front();

            for (Node<T>* neighbor : n->neighbors) {

                if (neighbor->visited == true) continue;

                neighbor->from = n;
                neighbor->visited = true;

                if (neighbor == _end) return neighbor;

                nodes.push_back(neighbor);
            }
        }
        return _end; //normalement from est a nullptr donc on sais que pas de solution
    }

    template<typename T, typename costFn>
    Node<T>* GetPathV2(Node<T>* _start, Node<T>* _end, costFn _cost) {

        using QueueEntry = std::pair<float, Node<T>*>;

        auto comp = [](const QueueEntry& _a, const QueueEntry& _b) {return _a.first > _b.first;};


        BinaryHeap<QueueEntry, decltype(comp)> bh(comp);
        _start->dist = 0.f;
        bh.push({ 0.f, _start });

        while (bh.empty() == false) {
            QueueEntry entry = bh.top();
            bh.pop();

            Node<T>* n = entry.second;

            if (entry.first > n->dist) continue;
            if (n == _end) return n;

            for (Node<T>* neighbor : n->neighbors) {
                float newDist = n->dist + _cost(n, neighbor);
                if (newDist < neighbor->dist) {
                    neighbor->dist = newDist;
                    neighbor->from = n;
                    bh.push({ newDist, neighbor });
                }
            }

        }

        _end->from = nullptr;
        return _end;

    }
}
