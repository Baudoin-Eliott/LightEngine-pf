#include "GameManager.h"

#include "Entity.h"
#include "Debug.h"
#include "InputManager.h"

#include <string>
#include <cassert>

#include "SDL3/SDL.h"
#include <SDL_ttf.h>

GameManager::GameManager()
{
    mpWindow = nullptr;
    mpRenderer = nullptr;
    mpTextEngine = nullptr;
    mpFont = nullptr;
    mDeltaTime = 0.0f;
    mpScene = nullptr;
    mWindowWidth = -1;
    mWindowHeight = -1;
    mClearColor = Color::Black;
}

GameManager* GameManager::Get()
{
    static GameManager mInstance;

    return &mInstance;
}

GameManager::~GameManager()
{
    while (mEntities.empty() == false)
    {
        Entity* entity = mEntities.front();
        mEntities.pop_front();

        delete entity;
    }

    while (mEntitiesToAdd.empty() == false)
    {
        Entity* entity = mEntitiesToAdd.front();
        mEntitiesToAdd.pop_front();

        delete entity;
    }

    delete mpScene;

    TTF_CloseFont(mpFont);
    TTF_DestroyRendererTextEngine(mpTextEngine);
    TTF_Quit();

    SDL_DestroyRenderer(mpRenderer);
    SDL_DestroyWindow(mpWindow);
    SDL_Quit();
}

bool GameManager::Initialize(int width, int height, const char* title, Color clearColor)
{
    assert(mpWindow == nullptr);
    if (mpWindow != nullptr)
        return false;

    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return false;
    }

    if (SDL_CreateWindowAndRenderer(title, width, height, 0, &mpWindow, &mpRenderer) == false)
    {
        SDL_Log("Window and renderer creation failed: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == false)
    {
        SDL_Log("SDL_ttf initialization failed: %s", SDL_GetError());
        return false;
    }

    mpTextEngine = TTF_CreateRendererTextEngine(mpRenderer);
    if (mpTextEngine == nullptr)
    {
        SDL_Log("Text renderer creation failed: %s", SDL_GetError());
        return false;
    }

    const char* basePath = SDL_GetBasePath();
    if (basePath == nullptr)
    {
        SDL_Log("Application path unavailable: %s", SDL_GetError());
        return false;
    }

    const std::string fontPath = std::string(basePath) + "res/LightEngine/Fonts/Abel-Regular.ttf";
    mpFont = TTF_OpenFont(fontPath.c_str(), 20.f);
    if (mpFont == nullptr)
    {
        SDL_Log("Font loading failed: %s", SDL_GetError());
        return false;
    }

    if (SDL_SetRenderVSync(mpRenderer, 1) == false)
    {
        SDL_Log("VSync activation failed: %s", SDL_GetError());
        return false;
    }

    if (SDL_SetRenderDrawBlendMode(mpRenderer, SDL_BLENDMODE_BLEND) == false)
    {
        SDL_Log("Draw blend mode setup failed: %s", SDL_GetError());
        return false;
    }

    mWindowWidth = width;
    mWindowHeight = height;
    mClearColor = clearColor;

    return true;
}

void GameManager::Run()
{
    InputManager* input = InputManager::Get();

    uint64 previousTime = SDL_GetTicksNS();
    while (input->IsQuit() == false)
    {
        const uint64 frameStart = SDL_GetTicksNS();
        SetDeltaTime(frameStart - previousTime);
        previousTime = frameStart;

        input->Update();

        Update();

        Draw();
    }
}

void GameManager::Update()
{
    mpScene->OnUpdate();

    mEntities.splice(mEntities.end(), mEntitiesToAdd);

    //Update
    for (Entity* entity : mEntities)
    {
        if (entity->ToDestroy() == false)
            entity->Update();
    }

    //Collision
    for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
    {
        auto it2 = it1;
        ++it2;
        for (; it2 != mEntities.end(); ++it2)
        {
            Entity* entity = *it1;
            Entity* otherEntity = *it2;

            if (entity->ToDestroy() || otherEntity->ToDestroy())
                continue;

            if (entity->IsColliding(otherEntity) == false)
                continue;

            if (entity->IsRigidBody() && otherEntity->IsRigidBody())
                entity->Repulse(otherEntity);

            entity->OnCollision(otherEntity);
            otherEntity->OnCollision(entity);
        }
    }

    for (auto it = mEntities.begin(); it != mEntities.end(); )
    {
        Entity* entity = *it;

        if (entity->ToDestroy() == false)
        {
            ++it;
            continue;
        }

        delete entity;
        it = mEntities.erase(it);
    }
}

void GameManager::Draw()
{
    SDL_SetRenderDrawColor(mpRenderer,
        mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
    SDL_RenderClear(mpRenderer);

    for (Entity* entity : mEntities)
    {
        entity->Draw(mpRenderer);
    }

    Debug::Draw(mpRenderer, mpTextEngine, mpFont);

    SDL_RenderPresent(mpRenderer);
}
