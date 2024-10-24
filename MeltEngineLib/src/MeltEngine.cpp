#include "MeltEngine.h"

namespace MELT
{
    float Engine::ScreenWidth  = 30.0f;
    float Engine::ScreenHeight = 30.0f;

    //glm::vec2 Engine::CurrentOffset { };
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
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
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
        TextureMng.Init();

        ECSCoord.Init();
        ECSCoord.RegisterComponent<Camera>   ();
        ECSCoord.RegisterComponent<Transform>();
        ECSCoord.RegisterComponent<Renderer> ();
        ECSCoord.RegisterComponent<SpriteRenderer>();

        auto _cameraControlSystem = ECSCoord.RegisterSystem<CameraControlSystem>();
        {
            Signature _signature;
            _signature.set(ECSCoord.GetComponentType<Transform>());
            _signature.set(ECSCoord.GetComponentType<Camera>());
            ECSCoord.SetSystemSignature<CameraControlSystem>(_signature);
        }
        _cameraControlSystem->Init();

        m_RenderSystem = ECSCoord.RegisterSystem<RenderSystem>();
        {
            Signature signature;
            signature.set(ECSCoord.GetComponentType<Transform>());
            signature.set(ECSCoord.GetComponentType<SpriteRenderer>());
            ECSCoord.SetSystemSignature<RenderSystem>(signature);
        }
        m_RenderSystem->Init();
        m_RenderSystem->Engine   = this;
        m_RenderSystem->ECSCoord = &ECSCoord;
    }

    void Engine::Update()
    {
        glEnable(GL_DEPTH_TEST);

        while(m_IsRunning)
        {
            UpdateInput ();
            UpdateLogic ();
            UpdateRender();
        }
    }

    void Engine::UpdateInput()
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

//                        ScreenWidth  = static_cast<float>(_width) * ZoomFactor;
//                        ScreenHeight = static_cast<float>(_height)* ZoomFactor;

                        m_RenderSystem->EditorSceneFrameBuffer->RescaleFrameBuffer(2 * _width, 2 * _height);
                        m_RenderSystem->GridShader2D->Use();
                        m_RenderSystem->GridShader2D->SetVec2UniformScreenSize(glm::vec2(_width, _height));
                    }
                    break;
                case SDL_KEYDOWN:
                    if(m_Event.key.keysym.sym == SDLK_ESCAPE)
                        m_IsRunning = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:

                    if (m_Event.button.button == SDL_BUTTON_RIGHT)
                    {
                        isDragging = true;
                        SDL_GetMouseState(&initialMouseX, &initialMouseY);
                    }

                    if (m_Event.button.button == SDL_BUTTON_LEFT)
                    {
                        m_LeftMouseDrag = true;
                        SDL_GetMouseState(&initialMouseX, &initialMouseY);

                        glm::vec3 _mousePos {MouseWorldPosition.x, MouseWorldPosition.y, 0 };

                        bool _entitySelected = false;

                        for(int _i = 0; _i < ECSCoord.m_EntityManager->ActiveEntities.size(); _i++)
                        {
                            auto _entity = ECSCoord.m_EntityManager->ActiveEntities[_i];

                            Transform& _transform = ECSCoord.GetComponent<Transform>(_entity);

                            auto _dist = glm::distance(_mousePos, _transform.Position);

                            if(_dist < 1.0f)
                            {
                                ECSCoord.SelectedEntity = _entity;
                                _entitySelected = true;
                                break;
                            }
                        }

                        if(!_entitySelected)
                            ECSCoord.SelectedEntity = -1;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    {
                        if (m_Event.button.button == SDL_BUTTON_LEFT)
                            m_LeftMouseDrag = false;

                        if (m_Event.button.button == SDL_BUTTON_RIGHT)
                            isDragging = false;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (isDragging)
                    {
                        float offsetX = m_Event.motion.x - initialMouseX;
                        float offsetY = m_Event.motion.y - initialMouseY;

                        initialMouseX = m_Event.motion.x;
                        initialMouseY = m_Event.motion.y;

                        MainCamera.Position.x -= offsetX * 0.5f;
                        MainCamera.Position.y += offsetY * 0.5f;
                    }

                    if(m_LeftMouseDrag)
                    {
                        if(ECSCoord.SelectedEntity != -1)
                        {
                            Transform& _transform = ECSCoord.GetComponent<Transform>(ECSCoord.SelectedEntity);

                            _transform.Position.x = MouseWorldPosition.x;
                            _transform.Position.y = MouseWorldPosition.y;
                        }
                    }
                    break;

                case SDL_MOUSEWHEEL:

                    break;
            }
        }
    }

    void Engine::UpdateLogic()
    {

    }

    void Engine::UpdateRender()
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef M_EDITOR
        m_RenderSystem->Update(0.0f);
        UpdateEditor();
#endif
        SDL_GL_SwapWindow(m_Window);
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
