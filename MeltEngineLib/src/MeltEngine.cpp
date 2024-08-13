#include "MeltEngine.h"

namespace MELT
{
    Engine::Engine():
        m_IsRunning(true),
        m_Window(nullptr)
        //m_2DGridShader(Shader("../MeltEngineLib/res/shaders/Basic.shader"))
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

        auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        m_Window = SDL_CreateWindow(
                "MELT (V1.1)",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                800,
                600,
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

        m_Quad = new Quad();

        m_BasicShader  = new Shader("../MeltEngineLib/res/shaders/Basic.shader");
        m_2DGridShader = new Shader("../MeltEngineLib/res/shaders/2DGrid.shader");

        glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view  = glm::lookAt(
                    glm::vec3(0.0f, 0.0f, 3.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f)
                );

        glm::mat4 _projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

        m_2DGridShader->Use();
        m_2DGridShader->SetMat4UniformModel     (_model);
        m_2DGridShader->SetMat4UniformView      (_view);
        m_2DGridShader->SetMat4UniformProjection(_projection);
        m_2DGridShader->SetVec2UniformScreenSize(glm::vec2(800, 600));
    }

    Engine::~Engine() = default;

    void Engine::Init()
    {

    } 

    void Engine::Update()
    {
        bool isDragging = false;
        int initialMouseX, initialMouseY;
        int currentMouseX, currentMouseY;

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
                    case SDL_WINDOWEVENT:
                        if(m_Event.window.event == SDL_WINDOWEVENT_RESIZED)
                        {
                            GLsizei _width  = m_Event.window.data1;
                            GLsizei _height = m_Event.window.data2;

                            std::cout << "SDL WINDOW : " << _width << " , " << _height << std::endl;

                            m_Quad->RescaleFrameBuffer(2 * _width, 2 * _height);

                            m_2DGridShader->Use();
                            m_2DGridShader->SetVec2UniformScreenSize(glm::vec2(_width, _height));
                        }
                        break;
                    case SDL_KEYDOWN:
                        if(m_Event.key.keysym.sym == SDLK_ESCAPE)
                            m_IsRunning = false;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        if (m_Event.button.button == SDL_BUTTON_LEFT) {
                            // Start dragging
                            isDragging = true;
                            SDL_GetMouseState(&initialMouseX, &initialMouseY);
                        }
                        break;

                    case SDL_MOUSEBUTTONUP:
                        if (m_Event.button.button == SDL_BUTTON_LEFT) {
                            // Stop dragging
                            isDragging = false;
                        }
                        break;

                    case SDL_MOUSEMOTION:
                        if (isDragging) {
                            // Update current mouse position
                            SDL_GetMouseState(&currentMouseX, &currentMouseY);

                            // Calculate the drag offset
                            int offsetX = currentMouseX - initialMouseX;
                            int offsetY = currentMouseY - initialMouseY;

                            // Handle the offset as needed
                            // For example, move an object, scroll a view, etc.

                            m_2DGridShader->Use();
                            m_2DGridShader->SetVec2UniformOrigin(glm::vec2(offsetX, offsetY));
                        }
                        break;
                }
            }

            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            m_Quad->Draw();
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
