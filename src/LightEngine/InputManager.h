#pragma once

#include <SDL3/SDL_events.h>
#include <unordered_map>
#include "Vector.h"

class InputManager
{
    enum class State
    {
        None,

        Down,
        Held,
        Up,
    };

    bool mQuit = false;
    std::unordered_map<SDL_Keycode, State> mKeys;
    std::unordered_map<int, State> mMouseButtons;

private:
    InputManager() = default;
    void Update();

    bool IsKey(SDL_Keycode key, State state) const;
    bool IsMouse(int button, State state) const;

public:
    static InputManager* Get();

    bool IsKeyDown(SDL_Keycode key) const;
    bool IsKeyHeld(SDL_Keycode key) const;
    bool IsKeyUp(SDL_Keycode key) const;

    bool IsMouseDown(int button) const;
    bool IsMouseHeld(int button) const;
    bool IsMouseUp(int button) const;
    Vector2f GetMousePosition() const;

    bool IsQuit() const { return mQuit; }

    friend class GameManager;
};
