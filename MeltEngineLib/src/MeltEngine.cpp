#include "MeltEngine.h"

namespace MELT
{
    Engine::Engine():
        m_IsRunning(true),
        m_Window(nullptr)
    {
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);                                         

        m_Window = SDL_CreateWindow(
                "MELT ENGINE",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                800,
                600,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if(!m_Window)
        {
            SDL_Quit();
            return;
        }

        m_GLContext = SDL_GL_CreateContext(m_Window);
         
        if (!m_GLContext) 
        {
            std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_Window);
            SDL_Quit();
            return;
        }

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK) 
        {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            SDL_GL_DeleteContext(m_GLContext);
            SDL_DestroyWindow(m_Window);
            SDL_Quit();
            return;
        }
    }

    Engine::~Engine()
    {
        
    }
   
    void Engine::Init()
    {

    } 

    void Engine::Update()
    {
        while(m_IsRunning)
        {
            while(SDL_PollEvent(&m_Event))
            {
                switch(m_Event.type)
                {
                    case SDL_QUIT:
                        m_IsRunning = false;
                        break;
                    case SDL_KEYDOWN:
                        if(m_Event.key.keysym.sym == SDLK_ESCAPE)
                            m_IsRunning = false;
                        break;
                }
            }

            glEnable(GL_DEPTH_TEST);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            SDL_GL_SwapWindow(m_Window);
        } 
    }

    void Engine::Quit()
    {
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }
}
