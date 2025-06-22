#include "MeltEngine.h"

namespace MELT
{
    float Engine::ScreenWidth  = 30.0f;
    float Engine::ScreenHeight = 30.0f;

    Engine::Engine():
        m_is_running(true),
        sdl_window(nullptr)
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
        sdl_window = SDL_CreateWindow(
                "MELT (V1.1)",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                window_flags);

        if(!sdl_window)
        {
            SDL_Quit();
            return;
        }

        gl_context = SDL_GL_CreateContext(sdl_window);

        if (!gl_context)
        {
            std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(sdl_window);
            SDL_Quit();
            return;
        }

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            SDL_GL_DeleteContext(gl_context);
            SDL_DestroyWindow(sdl_window);
            SDL_Quit();
            return;
        }
    }

    Engine::~Engine() = default;

    typedef void (*HelloFunc)();

    void Engine::init()
    {
        Logger.init();

        spdlog::info("Hello, ImGui!");
        spdlog::warn("This is a warning!");
        spdlog::error("Something went wrong!");

        manager_registry.Register<ResourceManager>(std::make_shared<ResourceManager>());
        manager_registry.Register<SceneManager>   (std::make_shared<SceneManager>   ());
        manager_registry.Register<RenderPipeline> (std::make_shared<RenderPipeline> ());

        manager_registry.get<ResourceManager>()->init();
        manager_registry.get<SceneManager>   ()->init();
        manager_registry.get<RenderPipeline> ()->Init(this);

        texture_manager.Init();

        void* _handle = dlopen("../Project/build/libCustomNativeScript.dylib", RTLD_LAZY);
        if (!_handle)
        {
            std::cerr << "Failed to load dylib: " << dlerror() << std::endl;
            return;
        }
        dlerror();
        HelloFunc _hello = (HelloFunc)dlsym(_handle, "hello_from_dylib");

        if (const char* error = dlerror())
        {
            std::cerr << "Failed to load symbol: " << error << std::endl;
            dlclose(_handle);
            return;
        }

        _hello();
        dlclose(_handle);
    }

    void Engine::update()
    {
        // glEnable(GL_DEPTH_TEST);//Will remove this
        // while(m_is_running)
        // {
        //     update_input ();
        //     update_logic ();
        //     update_render();
        //     gEventManager.DispatchEvents();
        //     SDL_Delay(16);
        // }
    }

    void Engine::update_input()
    {
        // Input.ClearInput();
        // while(SDL_PollEvent(&m_event))
        // {
        //     Input.Update(m_event);
        //     switch(m_event.type)
        //     {
        //         case SDL_QUIT:
        //             m_is_running = false;
        //             break;
        //     }
        // }
        // Input.CheckMouseHoldStates();
    }

    void Engine::update_editor_logic()
    {
        if(Input.IsKeyPressed(SDL_SCANCODE_ESCAPE))
            m_is_running = false;

        if(Input.IsMouseButtonPressed(SDL_BUTTON_RIGHT))
            m_is_dragging = true;

        if(Input.IsMouseButtonHeld(SDL_BUTTON_RIGHT))
        {
            if (m_is_dragging)
            {
                auto _delta = Input.MouseDelta;
                auto screenToWorldScale = ScreenHeight / 2 * main_camera.orthographic_size;
                main_camera.position.x -= _delta.x * 2.0f/ screenToWorldScale;
                main_camera.position.y += _delta.y * 2.0f/ screenToWorldScale;
            }
        }

        if(Input.IsMouseButtonReleased(SDL_BUTTON_RIGHT))
        {
            m_is_dragging = false;
        }

        if(Input.IsKeyHeld(SDL_SCANCODE_A))
        {
            glm::vec3 _camDir     = glm::normalize(main_camera.Target - main_camera.position);
            glm::vec3 _lateralDir = glm::cross(main_camera.Up, _camDir);

            main_camera.position += _lateralDir * 0.5f;
            main_camera.Target   += _lateralDir * 0.5f;
        }

        if(Input.IsKeyHeld(SDL_SCANCODE_D))
        {
            glm::vec3 _camDir     = glm::normalize(main_camera.Target - main_camera.position);
            glm::vec3 _lateralDir = glm::cross(main_camera.Up, _camDir);

            main_camera.position -= _lateralDir * 0.5f;
            main_camera.Target   -= _lateralDir * 0.5f;
        }

        if(Input.IsKeyHeld(SDL_SCANCODE_W))
        {
            main_camera.position += main_camera.Up * 0.5f;
            main_camera.Target   += main_camera.Up * 0.5f;
        }

        if(Input.IsKeyHeld(SDL_SCANCODE_S))
        {
            main_camera.position -= main_camera.Up * 0.5f;
            main_camera.Target   -= main_camera.Up * 0.5f;
        }
    }

    void Engine::update_logic()
    {
        manager_registry.get<SceneManager>()->working_scene->update();
    }

    void Engine::update_render()
    {
        // std::shared_ptr<RenderPipeline> _render_pipeline = manager_registry.get<RenderPipeline>();;
        // _render_pipeline->BeginFrame();
        // _render_pipeline->Render(0.0f);
        // _render_pipeline->EndFrame();
    }

    void Engine::begin_frame()
    {
        std::shared_ptr<RenderPipeline> _render_pipeline = manager_registry.get<RenderPipeline>();;
        _render_pipeline->BeginFrame();
    }

    void Engine::render_frame()
    {
        std::shared_ptr<RenderPipeline> _render_pipeline = manager_registry.get<RenderPipeline>();
        _render_pipeline->Render(0.0f);
    }

    void Engine::end_frame()
    {
        std::shared_ptr<RenderPipeline> _render_pipeline = manager_registry.get<RenderPipeline>();;
        _render_pipeline->EndFrame();
    }

    void Engine::quit()
    {
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }

    void Engine::create_cube_node()
    {
        std::shared_ptr<ResourceManager> _resource_manager = manager_registry.get<ResourceManager>();

        Scene* _working_scene = manager_registry.get<SceneManager>()->working_scene;

        Node& _node = _working_scene->create_node("Entity");
        _node.add_component<Transform>  ();
        _node.add_component<MeshRenderer>();
        _node.add_component<BoxCollider> ();
        _node.add_component<NodeEditor>  ();

        MeshRenderer& _mesh_renderer = _node.get_component<MeshRenderer>();
        _mesh_renderer.set_mesh_data(&_resource_manager->default_cube);
        _mesh_renderer.set_buffer_data();

        NodeEditor& _node_editor = _node.get_component<NodeEditor>();
        _node_editor.id = _node.id;

        Logger.log("Create cube node");
    }

    void Engine::create_plane_node()
    {
        std::shared_ptr<ResourceManager> _resource_manager = manager_registry.get<ResourceManager>();

        Scene* _working_scene = manager_registry.get<SceneManager>()->working_scene;

        Node& _node = _working_scene->create_node("Entity");
        _node.add_component<Transform>();
        _node.add_component<MeshRenderer>();
        _node.add_component<BoxCollider>();
        _node.add_component<NodeEditor>  ();

        MeshRenderer& _mesh_renderer = _node.get_component<MeshRenderer>();
        _mesh_renderer.set_mesh_data(&_resource_manager->default_plane);
        _mesh_renderer.set_buffer_data();

        NodeEditor& _node_editor = _node.get_component<NodeEditor>();
        _node_editor.id = _node.id;

        Logger.log("Create plane node");
    }

    void Engine::create_camera_node()
    {
        std::shared_ptr<ResourceManager> _resource_manager = manager_registry.get<ResourceManager>();

        Scene* _working_scene = manager_registry.get<SceneManager>()->working_scene;

        Node& _node = _working_scene->create_node("Camera");
        _node.add_component<Transform>();
        _node.add_component<Camera>();
        _node.add_component<Gizmos>(Gizmos::Type::CAMERA);
        _node.add_component<NodeEditor>  ();

        NodeEditor& _node_editor = _node.get_component<NodeEditor>();
        _node_editor.id = _node.id;

        Logger.log("Create camera node");
    }

    void Engine::create_light_node()
    {
        std::shared_ptr<ResourceManager> _resource_manager = manager_registry.get<ResourceManager>();

        Scene* _working_scene = manager_registry.get<SceneManager>()->working_scene;

        Node& _node = _working_scene->create_node("Light");
        _node.add_component<Transform>();
        _node.add_component<Light>();
        _node.add_component<Gizmos>(Gizmos::Type::LIGHT);
        _node.add_component<NodeEditor>  ();

        NodeEditor& _node_editor = _node.get_component<NodeEditor>();
        _node_editor.id = _node.id;

        Logger.log("Create light node");
    }

    void Engine::deselect_all_nodes()
    {
        Scene* _working_scene = manager_registry.get<SceneManager>()->working_scene;
        _working_scene->deselect_all_nodes();
    }

    void Engine::select_object(glm::vec2 _mouseScreenPos, const MELT::Camera &_camera)
    {
        Scene* _working_scene = manager_registry.get<SceneManager>()->working_scene;

        glm::vec3 rayDir = RayCast::ScreenToWorldRay(_mouseScreenPos, _camera);

        float _closestDistance = FLT_MAX;

        auto _view = _working_scene->ecs_registry.view<Transform, NodeEditor>();
        for (auto _entity : _view)
        {
            auto& _transform = _working_scene->ecs_registry.get<Transform>(_entity);
            auto& _node      = _working_scene->ecs_registry.get<NodeEditor>(_entity);

            auto _minBounds = _transform.position + glm::vec3(-0.5, -0.5, -0.5);
            auto _maxBounds = _transform.position + glm::vec3( 0.5,  0.5,  0.5);

            float _ndcX = (2.0f * _mouseScreenPos.x) / _camera.WindowSize.x - 1.0f;
            float _ndcY = 1.0f - (2.0f * _mouseScreenPos.y) / _camera.WindowSize.y;

            // Define near and far clip points in clip space
            glm::vec4 _nearClip = glm::vec4(_ndcX, _ndcY, 0.0f, 1.0f); // near plane in clip space
            glm::vec4 _farClip  = glm::vec4(_ndcX, _ndcY, 1.0f, 1.0f); // far plane in clip space

            // Inverse the projection and view matrices to go from clip space back to world space
            glm::mat4 _projInv = glm::inverse(_camera.get_orthographic_projection_matrix());
            glm::mat4 _viewInv = glm::inverse(_camera.get_view_matrix());

            // Transform clip space coordinates into world space
            glm::vec4 _nearPoint = _viewInv * _projInv * _nearClip; // World space near point
            glm::vec3 _rayOrigin = glm::vec3(_nearPoint.x, _nearPoint.y, _nearPoint.z);

            if (RayCast::RayIntersectsAABB(_rayOrigin, rayDir, _minBounds, _maxBounds))
            {
                float _distance = glm::distance(_rayOrigin, _transform.position);
                if (_distance < _closestDistance)
                {
                    _closestDistance = _distance;

                    _node.is_selected = true;
                    _working_scene->select_node_id(_node.id);
                    break;
                }
            }
        }
    }
}
