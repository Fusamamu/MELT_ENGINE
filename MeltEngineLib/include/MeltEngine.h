#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <functional>
//#include "imgui.h"
//#include "imgui_impl_sdl2.h"
//#include "imgui_impl_opengl3.h"


namespace MELT
{
    class Engine
    {
    public:
        std::function<void(void)> UpdateEngine;

        std::function<void(SDL_Event)> UpdateEditorInput;
        std::function<void(void)> UpdateEditor;
        Engine();
        ~Engine();

        void Init();
        void Update();
        void Quit();

        SDL_Window* GetWindow();
        SDL_GLContext& GetGLContext();
    private:
        bool m_IsRunning; 

        SDL_Window*   m_Window;
        SDL_GLContext m_GLContext;
        SDL_Event     m_Event;
    };
}
