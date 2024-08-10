#include "MeltEngine.h"

namespace MELT
{
    Engine::Engine():
        m_IsRunning(true),
        m_Window(nullptr)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            printf("Error: %s\n", SDL_GetError());
            return;
        }

        const char* glsl_version = "#version 150";

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);

        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        m_Window = SDL_CreateWindow(
                "MELT (V1.1)",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                1280,
                720,
                window_flags);

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
        glEnable(GL_DEPTH_TEST);
        while(m_IsRunning)
        {
            while(SDL_PollEvent(&m_Event))
            {
                UpdateEditorInput(m_Event);
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

#ifdef M_EDITOR
            UpdateEditor();
#endif
            SDL_GL_SwapWindow(m_Window);
        }
    }

    void Engine::Quit()
    {
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    SDL_Window* Engine::GetWindow()
    {
        return m_Window;
    }

    SDL_GLContext& Engine::GetGLContext()
    {
        return m_GLContext;
    }
}
