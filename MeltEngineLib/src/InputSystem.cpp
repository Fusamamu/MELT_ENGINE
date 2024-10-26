#include "InputSystem.h"

namespace MELT
{
    InputSystem::InputSystem()
    {
    }

    void InputSystem::Update(SDL_Event _event)
    {
        switch (_event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if (!mouseHeld[_event.button.button])
                    mouseDown[_event.button.button] = true;

                mouseHeld[_event.button.button] = true;
                SDL_GetMouseState(&MousePressPosition.x, &MousePressPosition.y);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseUp  [_event.button.button] = true;
                mouseHeld[_event.button.button] = false;
                break;
            case SDL_MOUSEMOTION:
                MousePreviousPosition = MousePosition;

                MousePosition.x = _event.motion.x;
                MousePosition.y = _event.motion.y;

                MouseDelta.x = MousePosition.x - MousePreviousPosition.x;
                MouseDelta.y = MousePosition.y - MousePreviousPosition.y;
                break;
            case SDL_KEYDOWN:
                if (!_event.key.repeat) { // Ignore repeated key events
                    keyDown[_event.key.keysym.scancode] = true;
                    keyHeld[_event.key.keysym.scancode] = true;
                }
                break;
            case SDL_KEYUP:
                keyUp  [_event.key.keysym.scancode] = true;
                keyHeld[_event.key.keysym.scancode] = false;
                break;
            case SDL_QUIT:
                break;
        }

//        MouseDelta.x = static_cast<float>(MousePosition.x - MousePressPosition.x);
//        MouseDelta.y = static_cast<float>(MousePosition.y - MousePressPosition.y);
//
//        MousePressPosition.x = MousePosition.x;
//        MousePressPosition.y = MousePosition.y;
    }

    void InputSystem::CheckMouseHoldStates()
    {
        Uint32 mouseState = SDL_GetMouseState(nullptr, nullptr);
        for (auto& button : {SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT, SDL_BUTTON_MIDDLE}) {
            if (mouseState & SDL_BUTTON(button)) {
                mouseHeld[button] = true;
            } else {
                mouseHeld[button] = false;
            }
        }
    }

    glm::vec2 InputSystem::GetMouseDelta()
    {
        glm::vec2 _delta
                {
                    MousePosition.x - MousePressPosition.x,
                    MousePosition.y - MousePressPosition.y
                };
        MousePressPosition.x = MousePosition.x;
        MousePressPosition.y = MousePosition.y;
        return _delta;
    }

    void InputSystem::ClearInput()
    {
        keyDown  .clear();
        keyUp    .clear();
        mouseDown.clear();
        mouseUp  .clear();
    }

    bool InputSystem::IsKeyPressed(SDL_Scancode key)
    {
        return keyDown[key];
    }

    bool InputSystem::IsKeyReleased(SDL_Scancode key)
    {
        return keyUp[key];
    }

    bool InputSystem::IsKeyHeld(SDL_Scancode key)
    {
        return keyHeld[key];
    }

    bool InputSystem::IsMouseButtonPressed(Uint8 button)
    {
        return mouseDown[button];
    }

    bool InputSystem::IsMouseButtonReleased(Uint8 button)
    {
        return mouseUp[button];
    }

    bool InputSystem::IsMouseButtonHeld(Uint8 button)
    {
        return mouseHeld[button];
    }

//    SDL_Point InputSystem::GetMousePosition()
//    {
//        return MousePosition;
//    }
}