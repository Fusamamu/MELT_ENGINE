#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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

#include "yaml-cpp/yaml.h"

namespace MELT
{
    class Engine
    {
    public:
        static float ScreenWidth;
        static float ScreenHeight;
        //static glm::vec2 CurrentOffset;
        static glm::vec2 MouseWorldPosition;

        const int WINDOW_WIDTH  = 900;
        const int WINDOW_HEIGHT = 600;

        Camera MainCamera;

        Coordinator ECSCoord;

        TextureManager TextureMng;

        std::shared_ptr<RenderSystem> m_RenderSystem;

        std::function<void(void)>      UpdateEngine;
        std::function<void(SDL_Event)> UpdateEditorInput;
        std::function<void(void)>      UpdateEditor;

        Engine();
        ~Engine();

        void Init();
        void Update();
        void UpdateInput();
        void UpdateLogic();
        void UpdateRender();
        void Quit();

        SDL_Window* GetWindow();
        SDL_GLContext& GetGLContext();
    private:
        bool m_IsRunning;

        SDL_Window*   m_Window;
        SDL_GLContext m_GLContext;
        SDL_Event     m_Event;

        bool isDragging = false;
        bool m_LeftMouseDrag = false;
        int initialMouseX, initialMouseY;
        int currentMouseX, currentMouseY;

    };
}
