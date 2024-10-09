#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Shader.h"
#include "Quad.h"

#include "Type.h"

#include "Camera.h"
#include "Transform.h"

#include "Coordinator.h"
#include "CameraControlSystem.h"

#include "yaml-cpp/yaml.h"

namespace MELT
{
    class Engine
    {
    public:
        Coordinator ECSCoord;

        Quad* m_Quad;

        float ScreenWidth;
        float ScreenHeight;
        glm::vec2 CurrentOffset;
        glm::vec2 MouseWorldPosition;

        std::function<void(void)>      UpdateEngine;
        std::function<void(SDL_Event)> UpdateEditorInput;
        std::function<void(void)>      UpdateEditor;

        Engine();
        ~Engine();

        void Init();
        void Update();
        void Quit();

        SDL_Window* GetWindow();
        SDL_GLContext& GetGLContext();
    private:
        bool m_IsRunning;

        SDL_Window*   m_Window;
        SDL_GLContext m_GLContext;
        SDL_Event     m_Event;

        Shader* m_2DGridShader;
        Shader* m_BasicShader;

    };
}
