#include "Grid.h"
#include <random>


bool Grid::isWalkable(int _index) {
    return map[_index].data->isWalkable;
}

Grid::Grid(int _size, int _wallRatio) : size(_size) {

    srand(time(NULL));

    //on cree les node avec les datas
    for (size_t i = 0; i < _size * _size; i++) {
        Node<Cell> node;

        Cell* cell = new Cell();
        cell->col = i % _size;
        cell->row = i / _size;
        cell->isWalkable = i == 0 ? true : rand() % _wallRatio != 0 ? true : false;

        node.data = cell;
        map.push_back(node);
    }

    //on ajoute les voisins
    for (int i = 0; i < _size * _size; i++) {

        std::deque<Node<Cell>*> neighbors;

        if (i + 1 < _size * _size && isWalkable(i + 1) && map[i].data->col != size-1) {
            neighbors.push_back(&map[i + 1]);
        }

        if (i - 1 >= 0 && isWalkable(i - 1) && map[i].data->col != 0) {
            neighbors.push_back(&map[i - 1]);
        }

        if (i + _size < _size * _size && isWalkable(i + _size)) {
            neighbors.push_back(&map[i + _size]);
        }

        if (i - _size >= 0 && isWalkable(i - _size)) {
            neighbors.push_back(&map[i - _size]);
        }

        map[i].neighbors = neighbors;
    }

    //ok normalement ici tout est bon

}


void Grid::ResetGrid() {
    for (size_t i = 0; i < size * size; i++)
    {
        map[i].visited = false;
        map[i].from = nullptr;
    }
}
