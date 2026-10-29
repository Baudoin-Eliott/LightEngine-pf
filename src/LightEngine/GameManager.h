#pragma once

#include <list>

#include "Color.h"
#include "Utils.h"

class Entity;
class Scene;
class Debug;

struct SDL_Window;
struct SDL_Renderer;
struct TTF_TextEngine;
struct TTF_Font;

class GameManager
{
    std::list<Entity*> mEntities;
    std::list<Entity*> mEntitiesToAdd;

    SDL_Window* mpWindow;
    SDL_Renderer* mpRenderer;
    TTF_TextEngine* mpTextEngine;
    TTF_Font* mpFont;

    Scene* mpScene;

    float mDeltaTime;

    int mWindowWidth;
    int mWindowHeight;

    Color mClearColor;

private:
    GameManager();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    bool Initialize(int width, int height, const char* title, Color clearColor);
    void Run();
    void Update();
    void Draw();

    void SetDeltaTime(uint64 deltaTimeNS) { mDeltaTime = static_cast<float>(deltaTimeNS) / 1000000000.f; }

    SDL_Window* GetWindow() const { return mpWindow; }

public:
    ~GameManager();
    static GameManager* Get();

    SDL_Renderer* GetRenderer() const { return mpRenderer; }
    TTF_TextEngine* GetTextEngine() const { return mpTextEngine; }
    TTF_Font* GetFont() const { return mpFont; }

    template<typename T>
    void LaunchScene(int width = 1280, int height = 720, const char* title = "LightEngine", Color clearColor = Color::Black);

    float GetDeltaTime() const { return mDeltaTime; }
    Scene* GetScene() const { return mpScene; }

    friend class Scene;
};

#include "GameManager.inl"
