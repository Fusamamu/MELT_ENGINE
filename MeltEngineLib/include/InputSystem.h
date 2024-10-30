#pragma once
#include "Core.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace MELT
{
    class InputSystem
    {
    public:
        SDL_Point MousePressPosition    { 0, 0 };
        SDL_Point MousePreviousPosition { 0, 0 };
        SDL_Point MousePosition         { 0, 0 };

        glm::vec2 MouseDelta { 0, 0 };

        glm::vec3 MouseScreenWorldPosition { };
        /** @brief Mouse position of application window. Coord(0,0) starts from top left corner of the window application*/
        glm::vec2 MouseWindowPosition      { };
        /** @brief Mouse screen position of a camera window.(Scene editor window)*/
        glm::vec2 MouseScreenPosition      { };

        InputSystem(const InputSystem& _other) = delete;
        InputSystem& operator=(const InputSystem& _other) = delete;

        static InputSystem& Instance()
        {
            static InputSystem _instance;
            return _instance;
        }

        void Update(SDL_Event _event);
        void CheckMouseHoldStates();
        void ClearInput();
        bool IsKeyPressed (SDL_Scancode key);
        bool IsKeyReleased(SDL_Scancode key);
        bool IsKeyHeld    (SDL_Scancode key);

        bool IsMouseButtonPressed (Uint8 button);
        bool IsMouseButtonReleased(Uint8 button);
        bool IsMouseButtonHeld    (Uint8 button);

        glm::vec2 GetMouseDelta();

    private:
        InputSystem();

        std::unordered_map<SDL_Scancode, bool> keyDown;
        std::unordered_map<SDL_Scancode, bool> keyUp;
        std::unordered_map<SDL_Scancode, bool> keyHeld;

        std::unordered_map<Uint8, bool> mouseDown;
        std::unordered_map<Uint8, bool> mouseUp;
        std::unordered_map<Uint8, bool> mouseHeld;
    };

    #define Input InputSystem::Instance()
}