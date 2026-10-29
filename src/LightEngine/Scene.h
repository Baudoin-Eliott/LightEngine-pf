#pragma once

#include "Color.h"

class GameManager;

class Scene
{
private:
    GameManager* mpGameManager = nullptr;

    void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }

protected:
    Scene() = default;

    virtual void OnInitialize() = 0;
    virtual void OnUpdate() = 0;

public:
    virtual ~Scene() = default;

    template<typename T>
    T* CreateEntity(float radius, const Color& color = Color::White);

    float GetDeltaTime() const;

    int GetWindowWidth() const;
    int GetWindowHeight() const;

    friend class GameManager;
};

#include "Scene.inl"
