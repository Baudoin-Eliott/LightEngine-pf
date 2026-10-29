#pragma once

#include "Entity.h"

#include <cassert>

#include "GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
    T* scene = dynamic_cast<T*>(GetScene());
    assert(scene != nullptr);
    return scene;
}

template<typename T>
T* Entity::CreateEntity(float radius, const Color& color)
{
    return GetScene()->CreateEntity<T>(radius, color);
}
