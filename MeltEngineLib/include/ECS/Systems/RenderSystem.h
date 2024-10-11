#pragma once
#include "SystemManager.h"
#include "Shader.h"
#include "Quad.h"
#include "FrameBuffer.h"

namespace MELT
{
    class Coordinator;

    class RenderSystem : public System
    {
    public:
        Quad* m_Quad;
        FrameBuffer* mFrameBuffer;

        Shader* m_2DGridShader;
        Shader* m_BasicShader;

        Coordinator* ECSCoord;

        void Init();
        void Update(float _dt);
    };
}