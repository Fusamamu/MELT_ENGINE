#include "MeltEngine.h"

namespace MELT
{
    float Engine::ScreenWidth  = 1600.0f;
    float Engine::ScreenHeight = 1200.0f;
    glm::vec2 Engine::CurrentOffset { };
    glm::vec2 Engine::MouseWorldPosition { };

    Engine::Engine():
        m_IsRunning(true),
        m_Window(nullptr)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            printf("Error: %s\n", SDL_GetError());
            return;
        }

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
                static_cast<int>(ScreenWidth),
                static_cast<int>(ScreenHeight),
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

    Engine::~Engine() = default;

    void Engine::Init()
    {
        ECSCoord.Init();
        ECSCoord.RegisterComponent<Camera>   ();
        ECSCoord.RegisterComponent<Transform>();
        ECSCoord.RegisterComponent<Renderer> ();

        auto _cameraControlSystem = ECSCoord.RegisterSystem<CameraControlSystem>();
        {
            Signature _signature;
            _signature.set(ECSCoord.GetComponentType<Camera>());
            _signature.set(ECSCoord.GetComponentType<Transform>());
            ECSCoord.SetSystemSignature<CameraControlSystem>(_signature);
        }
        _cameraControlSystem->Init();

        m_RenderSystem = ECSCoord.RegisterSystem<RenderSystem>();
        {
            Signature signature;
            signature.set(ECSCoord.GetComponentType<Renderer>());
            signature.set(ECSCoord.GetComponentType<Transform>());
            ECSCoord.SetSystemSignature<RenderSystem>(signature);
        }
        m_RenderSystem->Init();
        m_RenderSystem->ECSCoord = &ECSCoord;
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

                            ScreenWidth  = static_cast<float>(_width);
                            ScreenHeight = static_cast<float>(_height);

                            m_RenderSystem->mFrameBuffer->RescaleFrameBuffer(2 * _width, 2 * _height);
                            m_RenderSystem->m_2DGridShader->Use();
                            m_RenderSystem->m_2DGridShader->SetVec2UniformScreenSize(glm::vec2(_width, _height));
                        }
                        break;
                    case SDL_KEYDOWN:
                        if(m_Event.key.keysym.sym == SDLK_ESCAPE)
                            m_IsRunning = false;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        if (m_Event.button.button == SDL_BUTTON_RIGHT)
                        {
                            // Start dragging
                            isDragging = true;
                            SDL_GetMouseState(&initialMouseX, &initialMouseY);
                            initialMouseX -= static_cast<int>(CurrentOffset.x);
                            initialMouseY -= static_cast<int>(CurrentOffset.y);
                        }


                        if (m_Event.button.button == SDL_BUTTON_LEFT)
                        {
                            glm::vec2 _mousePos {MouseWorldPosition.x, MouseWorldPosition.y };

//                            float distance = glm::distance(_mousePos, m_Quad->WorldPosition);

//                            if(distance < 100.0f)
//                            {
//                                m_BasicShader->Use();
//                                m_BasicShader->SetVec3UniformColor(glm::vec3(1.0, 0.0, 0.0));
//                            }
//                            else
//                            {
//                                m_BasicShader->Use();
//                                m_BasicShader->SetVec3UniformColor(glm::vec3(1.0, 1.0, 1.0));
//                            }

                        }
                        break;

                    case SDL_MOUSEBUTTONUP:
                        if (m_Event.button.button == SDL_BUTTON_RIGHT) {
                            // Stop dragging
                            isDragging = false;
                        }
                        break;

                    case SDL_MOUSEMOTION:
                        if (isDragging) {
                            // Update current mouse position
                            SDL_GetMouseState(&currentMouseX, &currentMouseY);

                            // Calculate the drag offset
                            int offsetX = (currentMouseX - initialMouseX);
                            int offsetY = (currentMouseY - initialMouseY);

                            CurrentOffset.x = static_cast<float>(offsetX);
                            CurrentOffset.y = static_cast<float>(offsetY);

                            m_RenderSystem->m_2DGridShader->Use();
                            m_RenderSystem->m_2DGridShader->SetVec2UniformOrigin(CurrentOffset);
                        }
                        break;
                }
            }

            //Input
            //Update
//            m_BasicShader->Use();
//            glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (MouseWorldPosition.x, MouseWorldPosition.y, 0.0f));
//            _model = glm::scale(_model, glm::vec3(25.0f, 25.0f, 1.0f));
//            m_BasicShader->SetMat4UniformModel(_model);

            //Render
            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef M_EDITOR
            m_RenderSystem->Update(0.0f);
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
