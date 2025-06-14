#include "Core.h"
#include "Logger.h"
#include "ManagerRegistry.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#include "NodeManager.h"
#include "TextureManager.h"

#include "Shader.h"
#include "Quad.h"
#include "Type.h"

#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Renderer.h"
#include "BoxCollider.h"

#include "SpriteRenderer.h"
#include "Coordinator.h"
#include "CameraControlSystem.h"
#include "RenderSystem.h"
#include "RenderPipeline.h"
#include "EventManager.h"
#include "InputSystem.h"
#include "RayCast.h"
#include "yaml-cpp/yaml.h"

#include "Serializer.h"

namespace MELT
{
    class Engine
    {
    public:
        SDL_Window*   sdl_window;
        SDL_GLContext gl_context;

        static float ScreenWidth;
        static float ScreenHeight;

        const int WINDOW_WIDTH  = 1600;
        const int WINDOW_HEIGHT = 800;

        ManagerRegistry manager_registry;

        Camera         MainCamera;//will remove //move to scene??
        TextureManager TextureMng;//will remove

        Logger Logger;

        std::function<void(void)>      UpdateEngine;
        std::function<void(SDL_Event)> UpdateEditorInput;
        std::function<void(void)>      UpdateEditor;

        Engine();
        Engine(const Engine& _other) = delete;
        Engine& operator=(const Engine& _other) = delete;
        ~Engine();

        void init();
        void update();
        void update_input();
        void update_render();
        void update_logic();

        void begin_frame();
        void render_frame();
        void end_frame();

        void quit();

        void create_node();
        void create_plane_node();
        void create_camera_node();
        void deselect_all_nodes();
        void SelectObject(glm::vec2 _mouseScreenPos, const Camera& _camera);

    private:
        bool m_is_running;
        bool m_is_dragging = false;

        SDL_Event m_event;
    };
}
