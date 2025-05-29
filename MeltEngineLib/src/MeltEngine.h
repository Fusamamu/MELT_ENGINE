#include "Core.h"

// #include <GL/glew.h>
//
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_opengl.h>

#include "NodeManager.h"
#include "TextureManager.h"

#include "Shader.h"
#include "Quad.h"

#include "Type.h"

#include "Camera.h"
#include "Transform.h"
#include "Renderer.h"
#include "SpriteRenderer.h"

#include "Coordinator.h"
#include "CameraControlSystem.h"
#include "RenderSystem.h"
#include "RenderPipeline.h"

#include "EventManager.h"
#include "InputSystem.h"
#include "RayCast.h"

#include "yaml-cpp/yaml.h"

namespace MELT
{
    enum class EngineMode
    {
        EDIT_MODE,
        PLAY_MODE
    };

    class Engine
    {
    public:
        SDL_Window*   sdl_window;
        SDL_GLContext gl_context;

        EngineMode CurrentMode = EngineMode::EDIT_MODE;

        static float ScreenWidth;
        static float ScreenHeight;

        const int WINDOW_WIDTH  = 1600;
        const int WINDOW_HEIGHT = 800;

        Camera         MainCamera;
        Coordinator    ECSCoord;
        NodeManager    NodeMng;
        TextureManager TextureMng;

        RenderPipeline* TargetRenderPipeline;
        std::shared_ptr<RenderSystem> m_RenderSystem;

        std::function<void(void)>      UpdateEngine;
        std::function<void(SDL_Event)> UpdateEditorInput;
        std::function<void(void)>      UpdateEditor;

        Engine();
        Engine(const Engine& _other) = delete;
        Engine& operator=(const Engine& _other) = delete;
        ~Engine();

        void init();
        void Update();
        void UpdateInput();
        void UpdateLogic();
        void UpdateRender();
        void Quit();

        void CreateNode();
        void SelectObject(glm::vec2 _mouseScreenPos, const Camera& _camera);

    private:
        bool m_is_running;
        bool m_is_dragging = false;

        SDL_Event m_event;
    };
}
