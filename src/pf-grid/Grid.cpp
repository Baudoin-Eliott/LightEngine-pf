#include "Grid.h"
#include <random>
#define FNL_IMPL
#include "FastNoiseLite.h"

inline float lissage(float _height) {
    if (_height < -0.5f)  return -0.51f;   // abysses
    if (_height < -0.3f) return - 0.31f;   // eau profonde
    if (_height < -0.15f) return - 0.151f;   // eau moyenne
    if (_height < -0.05f) return - 0.051f;   // eau peu profonde
    if (_height < 0.0f) return  -0.1f;   // sable humide
    if (_height < 0.05f) return  0.049f;   // sable
    if (_height < 0.1f) return  0.09f;   // prairie
    if (_height < 0.2f)  return 0.19f;    // herbe
    if (_height < 0.3f)  return 0.29f;    // forêt claire
    if (_height < 0.4f)  return 0.39f;    // forêt dense
    if (_height < 0.5f)  return 0.49f;    // collines
    if (_height < 0.6f)  return 0.59f;   // roche
    if (_height < 0.7f)  return 0.69f;   // haute roche
    return 0.79f;                         // neige
}

inline bool isOnSameHeight(float _a, float _b) {
    std::vector<float> heights{ -0.5f, -0.3f, -0.15f, -0.05f, 0.0f, 0.05f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f };

    size_t i;
    for (i = 0; i < heights.size() - 1; i++) {
        if (_a < heights[i]) break;
    }
    size_t j;
    for (j = 0; j < heights.size() - 1; j++) {
        if (_a < heights[j]) break;
    }
    return i == j;
}


void Grid::addNeighBors()
{

    //on ajoute les voisins
    for (int i = 0; i < size * size; i++) {

        std::vector<Node<Cell>*> neighbors;

        if (i + 1 < size * size && isWalkable(i + 1) && map[i].data->col != size - 1) {
            neighbors.push_back(&map[i + 1]);
        }

        if (i - 1 >= 0 && isWalkable(i - 1) && map[i].data->col != 0) {
            neighbors.push_back(&map[i - 1]);
        }

        if (i + size < size * size && isWalkable(i + size)) {
            neighbors.push_back(&map[i + size]);

            //diagonal bas

            //gauche
            if (i + size - 1 >= 0 && isWalkable(i + size - 1) && map[i].data->col != 0 && isOnSameHeight(map[i].data->height,map[i + size - 1].data->height)) {
                neighbors.push_back(&map[i + size - 1]);
            }

            //droite
            if (i + size + 1 < size * size && isWalkable(i + size + 1) && map[i].data->col != 0 && isOnSameHeight(map[i].data->height,map[i + size + 1].data->height)) {
                neighbors.push_back(&map[i + size + 1]);
            }
        }

        if (i - size >= 0 && isWalkable(i - size)) {
            neighbors.push_back(&map[i - size]);

            //diagonal haut
            // 
            //gauche
            if (i - size - 1 >= 0 && isWalkable(i - size - 1) && map[i].data->col != 0 && isOnSameHeight(map[i].data->height,map[i - size - 1].data->height)) {
                neighbors.push_back(&map[i - size - 1]);
            }

            //droite
            if (i - size + 1 < size * size && isWalkable(i - size + 1) && map[i].data->col != 0 && isOnSameHeight(map[i].data->height,map[i - size + 1].data->height)) {
                neighbors.push_back(&map[i - size + 1]);
            }
        }



        map[i].neighbors = neighbors;
    }
}

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
        cell->height = 0.f;
        node.data = cell;
        map.push_back(node);
    }

    addNeighBors();
    //ok normalement ici tout est bon

}

Grid::Grid(int _size) : size(_size) {

    fnl_state noise = fnlCreateState();
    noise.seed = time(NULL);
    

    //on cree les node avec les datas
    for (size_t i = 0; i < _size * _size; i++) {
        Node<Cell> node;

        Cell* cell = new Cell();
        cell->col = i % _size;
        cell->row = i / _size;
        cell->isWalkable = true;
        cell->height = (fnlGetNoise2D(&noise, cell->col, cell->row));

        node.data = cell;
        map.push_back(node);
    }
    addNeighBors();

    //ok normalement ici tout est bon

}


void Grid::ResetGrid() {
    for (size_t i = 0; i < size * size; i++)
    {
        map[i].visited = false;
        map[i].from = nullptr;
        map[i].dist = std::numeric_limits<float>::infinity();
    }
}
