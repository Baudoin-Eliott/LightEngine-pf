#pragma once

#include "Rendering.h"
#include "Vector.h"
#include "Color.h"

struct SDL_Renderer;

class Scene;

class Entity
{
    struct Target
    {
        Vector2f position;
        float distance = 0.f;
        bool isSet = false;
    };

protected:
    Circle mCircle;
    Vector2f mDirection;
    Target mTarget;
    float mSpeed = 0.f;
    int mTag = -1;
    bool mRigidBody = false;
    bool mToDestroy = false;

public:
    void SetPosition(Vector2f position, float ratioX = 0.5f, float ratioY = 0.5f);
    bool GoTo(Vector2f position, float speed = -1.f);
    void SetDirection(Vector2f direction, float speed = -1.f);
    bool GoToward(Vector2f position, float speed = -1.f);
    void SetSpeed(float speed) { mSpeed = speed; }
    void SetTag(int tag) { mTag = tag; }
    float GetRadius() const { return mCircle.radius; }
    void SetRigidBody(bool isRigidBody) { mRigidBody = isRigidBody; }
    bool IsRigidBody() const { return mRigidBody; }

    Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;

    bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other) const;
    bool IsPointInside(Vector2f point) const;

    void Destroy();
    bool ToDestroy() const { return mToDestroy; }

    template<typename T>
    T* GetScene() const;

    Scene* GetScene() const;
    float GetDeltaTime() const;

    template<typename T>
    T* CreateEntity(float radius, const Color& color);

protected:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void OnUpdate() {}
    virtual void OnCollision(Entity* collidedWith) {}
    virtual void OnInitialize() {}
    virtual void OnDestroy() {}

private:
    void Update();
    void Draw(SDL_Renderer* renderer) const;
    void Initialize(float radius, const Color& color);
    void Repulse(Entity* other);

    friend class GameManager;
    friend class Scene;
};

#include "Entity.inl"
