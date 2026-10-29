#include "Entity.h"

#include "GameManager.h"
#include "Debug.h"

#include <cassert>
#include <SDL3/SDL_render.h>

void Entity::Initialize(float radius, const Color& color)
{
    assert(radius > 0.f);

    mCircle.position = { 0.f, 0.f };
    mCircle.radius = radius;
    mCircle.color = color;
    mCircle.filled = true;

    mDirection = { 0.f, 0.f };

    mTarget.isSet = false;

    OnInitialize();
}

void Entity::Repulse(Entity* other)
{
    Vector2f pos1 = GetPosition();
    Vector2f pos2 = other->GetPosition();
    Vector2f normal = pos2 - pos1;

    float radius1 = mCircle.radius;
    float radius2 = other->mCircle.radius;

    float overlap = (normal.Magnitude() - (radius1 + radius2)) * 0.5f;

    Vector2f translation = overlap * normal.Normalized();

    Vector2f position1 = GetPosition() + translation;
    Vector2f position2 = other->GetPosition() - translation;

    SetPosition(position1);
    other->SetPosition(position2);
}

bool Entity::IsColliding(Entity* other) const
{
    Vector2f pos1 = GetPosition();
    Vector2f pos2 = other->GetPosition();

    float distSqr = Vector2f::DistanceSqr(pos1, pos2);

    float radius1 = mCircle.radius;
    float radius2 = other->mCircle.radius;

    float radiusSqr = (radius1 + radius2) * (radius1 + radius2);

    return distSqr < radiusSqr;
}

bool Entity::IsPointInside(Vector2f point) const
{
    Vector2f currentPos = GetPosition();

    return Vector2f::DistanceSqr(currentPos, point) < (mCircle.radius * mCircle.radius);
}

void Entity::Destroy()
{
    if (mToDestroy)
        return;

    mToDestroy = true;

    OnDestroy();
}

void Entity::SetPosition(Vector2f position, float ratioX, float ratioY)
{
    float size = mCircle.radius * 2.f;

    position.x -= size * ratioX;
    position.y -= size * ratioY;

    mCircle.position = position;

    if (mTarget.isSet)
    {
        GoTo(mTarget.position);
    }
}

Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
    float size = mCircle.radius * 2.f;
    Vector2f position = mCircle.position;

    position.x += size * ratioX;
    position.y += size * ratioY;

    return position;
}

bool Entity::GoToward(Vector2f position, float speed)
{
    Vector2f currentPos = GetPosition();
    Vector2f direction = position - currentPos;
    if (direction.Normalize() == false)
    {
        SetDirection({ 0.f, 0.f }, speed);
        mTarget.distance = 0.f;
        return false;
    }

    SetDirection(direction, speed);

    return true;
}

bool Entity::GoTo(Vector2f position, float speed)
{
    if (GoToward(position, speed) == false)
        return false;

    Vector2f currentPos = GetPosition();

    mTarget.position = position;
    mTarget.distance = Vector2f::Distance(currentPos, position);
    mTarget.isSet = true;

    return true;
}

void Entity::SetDirection(Vector2f direction, float speed)
{
    if (speed >= 0.f)
        mSpeed = speed;

    mDirection = direction.Normalized();
    mTarget.isSet = false;
}

void Entity::Update()
{
    float dt = GetDeltaTime();
    float distance = dt * mSpeed;
    Vector2f translation = mDirection * distance;

    mCircle.position += translation;

    if (mTarget.isSet)
    {
        Vector2f currentPos = GetPosition();
        Debug::DrawLine(currentPos, mTarget.position, Color::Cyan);
        Debug::DrawCircle(mTarget.position, 5.f, Color::Magenta, true);

        mTarget.distance -= distance;

        if (mTarget.distance <= 0.f)
        {
            mTarget.isSet = false;
            SetPosition(mTarget.position);
            mDirection = { 0.f, 0.f };
        }
    }

    OnUpdate();
}

void Entity::Draw(SDL_Renderer* renderer) const
{
    mCircle.Draw(renderer);
}

Scene* Entity::GetScene() const
{
    return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
    return GameManager::Get()->GetDeltaTime();
}
