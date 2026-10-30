#include "SampleScene.h"
#include "../pf-core/Utils.h"
#include "DummyEntity.h"
#include "InputManager.h"
#include "Debug.h"

#include <iostream>

inline Color heightToColor(float _height) {
    if (_height < -0.5f)  return Color(10, 30, 100);   // abysses
    if (_height < -0.3f)  return Color(20, 60, 160);   // eau profonde
    if (_height < -0.15f) return Color(40, 110, 200);   // eau moyenne
    if (_height < -0.05f) return Color(80, 170, 220);   // eau peu profonde
    if (_height < 0.0f)  return Color(230, 215, 150);   // sable humide
    if (_height < 0.05f) return Color(240, 225, 130);   // sable
    if (_height < 0.1f)  return Color(170, 210, 100);   // prairie
    if (_height < 0.2f)  return Color(100, 180, 70);    // herbe
    if (_height < 0.3f)  return Color(50, 140, 50);    // forêt claire
    if (_height < 0.4f)  return Color(30, 100, 40);    // forêt dense
    if (_height < 0.5f)  return Color(120, 90, 60);    // collines
    if (_height < 0.6f)  return Color(130, 130, 130);   // roche
    if (_height < 0.7f)  return Color(180, 180, 180);   // haute roche
    return Color(250, 250, 255);                         // neige
}

void SampleScene::fillWall() {
    for (size_t i = 0; i < m_grid.size; i++) {
        for (size_t j = 0; j < m_grid.size; j++) {
            const Cell* cell = m_grid.map[j + i * m_grid.size].data;
            if (cell->isWalkable == false) {
                Debug::DrawRectangle({ j * m_cellWidth + m_cellWidth / 2, i * m_cellHeight + m_cellHeight / 2 }, { m_cellWidth, m_cellHeight }, Color::Red, true);
            }
            else {
                Debug::DrawRectangle(
                    { j * m_cellWidth + m_cellWidth / 2, i * m_cellHeight + m_cellHeight / 2 },
                    { m_cellWidth, m_cellHeight },
                    heightToColor(cell->height),
                    true);
            }
        }
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
   
}

void SampleScene::OnUpdate()
{
   
    InputManager* input = InputManager::Get();
    fillWall();
    Vector2f mousePos = input->GetMousePosition();

    if (input->IsMouseHeld(SDL_BUTTON_LEFT)) {

        int index = getGridIndex(mousePos);
        std::cout << index << std::endl;


        auto valide = [](int _index, int _gridSize) {return _index >= 0 && _index < _gridSize * _gridSize;};

        if (valide(index, m_grid.size)) {
            int playerPos = getGridIndex(m_player->GetPosition());

            m_grid.ResetGrid();

            auto heightComp = [](const Node<Cell>* _a, const Node<Cell>* _b)
                {
                    return std::fabs(_a->data->height - _b->data->height) * 10000 + (_a->data->col != _b->data->col && _a->data->row != _b->data->row) ? sqrt(2) : 1.f;
                };

            Node<Cell>* end = pf::GetPathV2(&m_grid.map[playerPos], &m_grid.map[index], heightComp);

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

    if (input->IsKeyUp(SDLK_SPACE)) {
        m_player->SetPosition(m_positions.back());
        m_positions.clear();
    }

    if (m_positions.empty() == false) {

        m_player->GoTo({ m_positions[0].x, m_positions[0].y}, 100.f);
        float dist = Vector2f::DistanceSqr(m_player->GetPosition(), { m_positions[0].x, m_positions[0].y });
        if (dist < 0.001f) {
            m_positions.pop_front();
        }

        for (Vector2f p : m_positions) {
            Debug::DrawCircle(p, m_cellWidth / 5, Color::Red, true);
        }
    }



    

}
