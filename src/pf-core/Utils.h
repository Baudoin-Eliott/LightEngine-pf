#pragma once
#include "Node.h"

namespace pf {
    template<typename T>
    Node<T>* getPath(Node<T>* _start, Node<T>* _end) {

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




        /* Recursive Way
        if (_start == _end) return _end;
        _start->visited = true;
        for (Node<T>* n : _start->neighbors) {

            if (n->visited) continue;

            n->from = _start;
            return getPath(n, _end);
        }
        */
    }
}
