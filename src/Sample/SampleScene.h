#pragma once

#include "Scene.h"
#include "../pf-grid/Grid.h"
#include <Vector>

#include <deque>


class DummyEntity;

class SampleScene : public Scene
{

    Grid m_grid{ 180 };
    DummyEntity* m_player;
    std::deque<Vector2f> m_positions;

    float m_cellHeight;
    float m_cellWidth;

private:
    int getGridIndex(const Vector2f& _mousePos);
    void fillWall();

public:
    void OnInitialize() override;
    void OnUpdate() override;
};
