#pragma once
#include "SystemManager.h"
#include "Shader.h"
#include "Quad.h"
#include "Line.h"
#include "FrameBuffer.h"

namespace MELT
{
    class Engine;
    class Coordinator;

    class RenderSystem : public System
    {
    public:

        Quad* m_Quad;
        Line* DummyLine;

        FrameBuffer* EditorSceneFrameBuffer;
        FrameBuffer* EditorGUIFrameBuffer;

        Shader* TargetShader;

        Shader* GridShader2D;
        Shader* CheckerboardShader;
        Shader* BasicShader;
        Shader* TextureShader;
        Shader* LineShader;

        Engine* Engine;
        Coordinator* ECSCoord;

        void Init();
        void Update(float _dt);
    };
}