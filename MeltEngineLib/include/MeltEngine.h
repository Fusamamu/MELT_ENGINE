#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace MELT
{
    class Engine
    {
    public:
        Engine();
        ~Engine();
        void Init();
        void Update();
        void Quit();
    private:
        bool m_IsRunning; 
        
        SDL_Window*   m_Window;
        SDL_GLContext m_GLContext;
        SDL_Event     m_Event;
    };
}
