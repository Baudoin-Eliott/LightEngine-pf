#pragma once
#include "Entity.h"

class DummyEntity : public Entity
{
public:
    void OnCollision(Entity* other) override;
};
