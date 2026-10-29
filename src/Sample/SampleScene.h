#pragma once

#include "Scene.h"
#include "../pf-grid/Grid.h"
#include <Vector>

#include <deque>


class DummyEntity;

class SampleScene : public Scene
{

    Grid m_grid{ 10, 3 };
    DummyEntity* m_player;
    std::vector<DummyEntity*> m_obstacles;
    std::deque<Vector2f> m_positions;

    float m_cellHeight;
    float m_cellWidth;
private:
    void DrawGrid(int _gridSize);
    int getGridIndex(const Vector2f& _mousePos);
public:
    void OnInitialize() override;
    void OnUpdate() override;
};
