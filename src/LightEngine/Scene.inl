#pragma once

#include <type_traits>

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"

template<typename T>
T* Scene::CreateEntity(float radius, const Color& color)
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

    T* newEntity = new T();

    Entity* entity = newEntity;
    mpGameManager->mEntitiesToAdd.push_back(entity);
    entity->Initialize(radius, color);

    return newEntity;
}
