#pragma once
#include "../pf-core/Node.h"
#include "Cell.h"
#include <vector>

struct Grid {
    std::vector<Node<Cell>> map;

    int size;

    Grid(int _size, int _wallRatio);

    void ResetGrid();
private:
    bool isWalkable(int _index);
};
