#pragma once
#include "../pf-core/Node.h"
#include "Cell.h"
#include <vector>

struct Grid {
    std::vector<Node<Cell>> map;

    int size;

    Grid(int _size, int _wallRatio);
    Grid(int _size);

    void ResetGrid();
private:
    void addNeighBors();
    bool isWalkable(int _index);
};
