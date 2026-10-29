#include "SampleScene.h"
#include "../pf-core/Utils.h"
#include "DummyEntity.h"
#include "InputManager.h"
#include "Debug.h"

#include <iostream>

bool isValid(int _index, int _gridSize) {
    return _index >= 0 && _index < _gridSize * _gridSize;
}

void SampleScene::DrawGrid(int _gridSize)
{

    Color color(255, 0, 0);
    for (size_t i = 0; i < _gridSize; i++) {
        Vector2f start{ 0.f, i * m_cellHeight };
        Vector2f end{ (float)(GetWindowWidth()), i * m_cellHeight };


        Debug::DrawLine(start, end, color);

        start.x = i * m_cellWidth;
        start.y = 0.f;

        end.x = i * m_cellWidth;
        end.y = (float)(GetWindowHeight());
        Debug::DrawLine(start, end, color);
    }

}

int SampleScene::getGridIndex(const Vector2f& _Pos) {

    int indexX = _Pos.x / m_cellWidth;
    int indexY = _Pos.y / m_cellHeight;


    return indexX + indexY * m_grid.size;
}

void SampleScene::OnInitialize()
{

    int WindowHeight = GetWindowHeight();
    int WindowWidth = GetWindowWidth();

    m_cellHeight = WindowHeight / m_grid.size;
    m_cellWidth = WindowWidth / m_grid.size;

    m_player = CreateEntity<DummyEntity>(m_cellHeight / 2, Color::Blue);

    for (size_t i = 0; i < m_grid.size; i++) {
        for (size_t j = 0; j < m_grid.size; j++) {
            if (m_grid.map[j  + i * m_grid.size].data->isWalkable == true) continue;

            DummyEntity* e = CreateEntity<DummyEntity>(m_cellHeight / 2, Color::Red);
            e->SetPosition({ j * m_cellWidth, i * m_cellHeight }, 0.f, 0.f);
            m_obstacles.push_back(e);
        }
    }


}

void SampleScene::OnUpdate()
{
   
    InputManager* input = InputManager::Get();

    Vector2f mousePos = input->GetMousePosition();

    DrawGrid(m_grid.size);


    if (input->IsMouseUp(SDL_BUTTON_LEFT)) {

        int index = getGridIndex(mousePos);
        std::cout << index << std::endl;
        if (isValid(index, m_grid.size)) {
            int playerPos = getGridIndex(m_player->GetPosition());

            std::cout << playerPos << std::endl;
            m_grid.ResetGrid();
            Node<Cell>* end = pf::getPath(&m_grid.map[playerPos], &m_grid.map[index]);

            if (end->from != nullptr) {

                m_positions.clear();
                while (end->from != nullptr) {
                    Vector2f pos;
                    pos.x = end->data->col * m_cellWidth + m_cellWidth / 2;
                    pos.y = end->data->row * m_cellHeight + m_cellHeight / 2;
                    m_positions.push_front(pos);
                    end = end->from;
                }
                
            }
        }
    }


    if (m_positions.empty() == false) {

        m_player->GoTo({ m_positions[0].x, m_positions[0].y}, 1000.f);
        float dist = Vector2f::DistanceSqr(m_player->GetPosition(), { m_positions[0].x, m_positions[0].y });
        if (dist < 0.1f) {
            m_positions.pop_front();
        }

        for (Vector2f p : m_positions) {
            Debug::DrawCircle(p, m_cellWidth / 5, Color::Yellow, true);
        }
    }



    

}
