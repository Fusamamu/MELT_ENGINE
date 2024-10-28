#include "Core.h"

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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

        void Init();
        void Update();
        void UpdateInput();
        void UpdateLogic();
        void UpdateRender();
        void Quit();

        void CreateNode();

        SDL_Window* GetWindow();
        SDL_GLContext& GetGLContext();
    private:
        bool m_IsRunning;

        SDL_Window*   m_Window;
        SDL_GLContext m_GLContext;
        SDL_Event     m_Event;

        bool isDragging = false;
    };
}
