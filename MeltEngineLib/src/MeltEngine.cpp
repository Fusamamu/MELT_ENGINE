#include "MeltEngine.h"

namespace MELT
{
    float Engine::ScreenWidth  = 30.0f;
    float Engine::ScreenHeight = 30.0f;

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
        _cameraControlSystem->OnStart();

        m_RenderSystem = ECSCoord.RegisterSystem<RenderSystem>();
        {
            Signature signature;
            signature.set(ECSCoord.GetComponentType<Transform>());
            signature.set(ECSCoord.GetComponentType<SpriteRenderer>());
            ECSCoord.SetSystemSignature<RenderSystem>(signature);
        }
        m_RenderSystem->OnStart();
        m_RenderSystem->Engine   = this;
        m_RenderSystem->ECSCoord = &ECSCoord;

        TargetRenderPipeline = new RenderPipeline();
        TargetRenderPipeline->Init(this);


        // Load the dynamic library
        void* _handle = dlopen("/Users/pengaki/Desktop/MeltSampleProject/build/libCustomNativeScript.dylib", RTLD_LAZY);
        if (!_handle) {
            std::cerr << "Cannot open library: " << dlerror() << std::endl;
            return;
        }
        else
        {
            std::cout << "Success dll" << std::endl;
        }

        void* func = dlsym(_handle, "CreateCustomSystem");
        const char* _error = dlerror();
        if (_error)
            std::cerr << "Failed to find function: " << _error << std::endl;

        using CreateScriptInstanceFn = INativeSystem* (*)();

        auto createInstance = reinterpret_cast<CreateScriptInstanceFn>(func);
        if (createInstance) {
            // Create and use the script instance
            INativeSystem* script = createInstance();
            script->OnStart();
            script->OnInputUpdate(0.0);

            delete script;  // Clean up the instance after use
        }

        dlclose(_handle);
    }

    void Engine::Update()
    {
        glEnable(GL_DEPTH_TEST);

        while(m_IsRunning)
        {
            UpdateInput ();
            UpdateLogic ();
            UpdateRender();
            gEventManager.DispatchEvents();

            SDL_Delay(16);
        }
    }

    void Engine::UpdateInput()
    {
        Input.ClearInput();
        while(SDL_PollEvent(&m_Event))
        {
            Input.Update(m_Event);
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

                        TargetRenderPipeline->EditorSceneFrameBuffer->RescaleFrameBuffer(2 * _width, 2 * _height);

                        m_RenderSystem->EditorSceneFrameBuffer->RescaleFrameBuffer(2 * _width, 2 * _height);
                        m_RenderSystem->GridShader2D->Use();
                        m_RenderSystem->GridShader2D->SetVec2UniformScreenSize(glm::vec2(_width, _height));
                    }
                    break;
            }
        }
        Input.CheckMouseHoldStates();
    }

    void Engine::UpdateLogic()
    {
        switch(CurrentMode)
        {
            case EngineMode::EDIT_MODE:
                if(Input.IsKeyPressed(SDL_SCANCODE_ESCAPE))
                {
                    m_IsRunning = false;
                }

                if(Input.IsMouseButtonPressed(SDL_BUTTON_LEFT))
                {
                    for(Node& _node : NodeMng.SceneNodes)
                        _node.isSelected = false;
                    SelectObject(Input.MouseScreenPosition, MainCamera);
                }

                if(Input.IsMouseButtonHeld(SDL_BUTTON_LEFT))
                {
                    if(NodeMng.CurrentSelectedNode != nullptr && NodeMng.CurrentSelectedNode->isSelected)
                    {
                        Transform& _transform = ECSCoord.GetComponent<Transform>(NodeMng.CurrentSelectedNode->entityRef);
//                        _transform.Position.x = Input.MouseScreenWorldPosition.x;
//                        _transform.Position.y = Input.MouseScreenWorldPosition.y;
                    }
                }

                if(Input.IsMouseButtonReleased(SDL_BUTTON_LEFT))
                {
                }

                if(Input.IsMouseButtonPressed(SDL_BUTTON_RIGHT))
                {
                    isDragging = true;
                }

                if(Input.IsMouseButtonHeld(SDL_BUTTON_RIGHT))
                {
                    if (isDragging)
                    {
                        auto _delta = Input.MouseDelta;
                        auto screenToWorldScale = ScreenHeight / 2 * MainCamera.OrthographicSize;
                        MainCamera.Position.x -= _delta.x * 2.0f/ screenToWorldScale;
                        MainCamera.Position.y += _delta.y * 2.0f/ screenToWorldScale;
                    }
                }

                if(Input.IsMouseButtonReleased(SDL_BUTTON_RIGHT))
                {
                    isDragging = false;
                }

                if(Input.IsKeyHeld(SDL_SCANCODE_A))
                {
                    glm::vec3 _camDir     = glm::normalize(MainCamera.Target - MainCamera.Position);
                    glm::vec3 _lateralDir = glm::cross(MainCamera.Up, _camDir);

                    MainCamera.Position += _lateralDir * 0.5f;
                    MainCamera.Target   += _lateralDir * 0.5f;
                }

                if(Input.IsKeyHeld(SDL_SCANCODE_D))
                {
                    glm::vec3 _camDir     = glm::normalize(MainCamera.Target - MainCamera.Position);
                    glm::vec3 _lateralDir = glm::cross(MainCamera.Up, _camDir);

                    MainCamera.Position -= _lateralDir * 0.5f;
                    MainCamera.Target   -= _lateralDir * 0.5f;
                }

                if(Input.IsKeyHeld(SDL_SCANCODE_W))
                {
                    MainCamera.Position += MainCamera.Up * 0.5f;
                    MainCamera.Target   += MainCamera.Up * 0.5f;
                }

                if(Input.IsKeyHeld(SDL_SCANCODE_S))
                {
                    MainCamera.Position -= MainCamera.Up * 0.5f;
                    MainCamera.Target   -= MainCamera.Up * 0.5f;
                }
                break;
            case EngineMode::PLAY_MODE:
                ECSCoord.m_SystemManager->UpdateInput();
                ECSCoord.m_SystemManager->Update();
                break;
        }
    }

    void Engine::UpdateRender()
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef M_EDITOR
        if(TargetRenderPipeline)
            TargetRenderPipeline->Render(0.0f);

        if(CurrentMode == EngineMode::PLAY_MODE)
            ECSCoord.m_SystemManager->UpdateRender();

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

    void Engine::CreateNode()
    {
        Node& _node = NodeMng.CreateNode(M_MATH::vec2<float>(0.0f));

        MELT::Entity _entity = ECSCoord.CreateEntity();

        ECSCoord.AddComponent<MELT::Transform>(_entity, {
                glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 0.0, 0.0),
        });

        ECSCoord.AddComponent<MELT::SpriteRenderer>(_entity, {

        });

        _node.entityRef = _entity;
    }

    SDL_Window* Engine::GetWindow()
    {
        return m_Window;
    }

    SDL_GLContext& Engine::GetGLContext()
    {
        return m_GLContext;
    }

    void Engine::SelectObject(glm::vec2 _mouseScreenPos, const MELT::Camera &_camera)
    {
        glm::vec3 rayDir = RayCast::ScreenToWorldRay(_mouseScreenPos, _camera);

        float _closestDistance = FLT_MAX;

        for (auto& _node : NodeMng.SceneNodes)
        {
            Transform& _transform = ECSCoord.GetComponent<Transform>(_node.entityRef);

            auto _minBounds = _transform.Position + glm::vec3(-0.5, -0.5, -0.5);
            auto _maxBounds = _transform.Position + glm::vec3( 0.5,  0.5,  0.5);

            float _ndcX = (2.0f * _mouseScreenPos.x) / _camera.WindowSize.x - 1.0f;
            float _ndcY = 1.0f - (2.0f * _mouseScreenPos.y) / _camera.WindowSize.y;

            // Define near and far clip points in clip space
            glm::vec4 _nearClip = glm::vec4(_ndcX, _ndcY, 0.0f, 1.0f); // near plane in clip space
            glm::vec4 _farClip  = glm::vec4(_ndcX, _ndcY, 1.0f, 1.0f); // far plane in clip space

            // Inverse the projection and view matrices to go from clip space back to world space
            glm::mat4 _projInv = glm::inverse(_camera.GetOrthographicProjectionMatrix());
            glm::mat4 _viewInv = glm::inverse(_camera.GetViewMatrix());

            // Transform clip space coordinates into world space
            glm::vec4 _nearPoint = _viewInv * _projInv * _nearClip; // World space near point
            glm::vec3 _rayOrigin = glm::vec3(_nearPoint.x, _nearPoint.y, _nearPoint.z);

            if (RayCast::RayIntersectsAABB(_rayOrigin, rayDir, _minBounds, _maxBounds))
            {
                float _distance = glm::distance(_rayOrigin, _transform.Position);
                if (_distance < _closestDistance)
                {
                    _closestDistance = _distance;

                    NodeMng.CurrentSelectedNode = &_node;
                    NodeMng.CurrentSelectedNode->isSelected = true;
                    break;
                }
            }
        }
    }
}
