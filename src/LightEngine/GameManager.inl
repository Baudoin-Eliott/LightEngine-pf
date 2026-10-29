#pragma once

#include <cassert>
#include <type_traits>

#include "GameManager.h"
#include "Scene.h"

template<typename T>
void GameManager::LaunchScene(int width, int height, const char* title, Color clearColor)
{
    static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

    assert(mpScene == nullptr);

    if (mpScene != nullptr)
        return;

    if (Initialize(width, height, title, clearColor) == false)
        return;

    T* newScene = new T();
    mpScene = newScene;

    mpScene->SetGameManager(this);
    mpScene->OnInitialize();

    Run();
}
