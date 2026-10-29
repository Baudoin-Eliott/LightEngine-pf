#include "InputManager.h"

InputManager* InputManager::Get()
{
    static InputManager instance;
    return &instance;
}

void InputManager::Update()
{
    for (auto it = mKeys.begin(); it != mKeys.end(); ++it)
    {
        if (it->second == State::Down)
            it->second = State::Held;
        else if (it->second == State::Up)
            it->second = State::None;
    }

    for (auto it = mMouseButtons.begin(); it != mMouseButtons.end(); ++it)
    {
        if (it->second == State::Down)
            it->second = State::Held;
        else if (it->second == State::Up)
            it->second = State::None;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            mQuit = true;
            break;

        case SDL_EVENT_KEY_DOWN:
            if (event.key.repeat == false)
                mKeys[event.key.key] = State::Down;
            break;

        case SDL_EVENT_KEY_UP:
            mKeys[event.key.key] = State::Up;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mMouseButtons[event.button.button] = State::Down;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            mMouseButtons[event.button.button] = State::Up;
            break;

        case SDL_EVENT_WINDOW_FOCUS_LOST:
            mKeys.clear();
            mMouseButtons.clear();
            break;
        }
    }
}

bool InputManager::IsKey(SDL_Keycode key, State state) const
{
    auto it = mKeys.find(key);
    if (it == mKeys.end())
        return false;

    return it->second == state;
}

bool InputManager::IsKeyDown(SDL_Keycode key) const
{
    return IsKey(key, State::Down);
}

bool InputManager::IsKeyHeld(SDL_Keycode key) const
{
    return IsKey(key, State::Down) || IsKey(key, State::Held);
}

bool InputManager::IsKeyUp(SDL_Keycode key) const
{
    return IsKey(key, State::Up);
}

bool InputManager::IsMouse(int button, State state) const
{
    auto it = mMouseButtons.find(button);
    if (it == mMouseButtons.end())
        return false;

    return it->second == state;
}

bool InputManager::IsMouseDown(int button) const
{
    return IsMouse(button, State::Down);
}

bool InputManager::IsMouseHeld(int button) const
{
    return IsMouse(button, State::Down) || IsMouse(button, State::Held);
}

bool InputManager::IsMouseUp(int button) const
{
    return IsMouse(button, State::Up);
}

Vector2f InputManager::GetMousePosition() const
{
    Vector2f mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    return mouse;
}
