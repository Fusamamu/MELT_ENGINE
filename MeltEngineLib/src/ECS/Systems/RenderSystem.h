#pragma once
#include "SystemManager.h"
#include "Shader.h"
#include "Quad.h"
#include "Cube.h"
#include "Line.h"
#include "GizmosTransform.h"
#include "FrameBuffer.h"

namespace MELT
{
    class Engine;
    class Coordinator;

    class RenderSystem : public INativeSystem
    {
    public:

        //Geometry
        Quad* aQuad;
        Cube* aCube;
        Line* DummyLine;
        GizmosTransform* GizmosAxis;

        //Render target
        FrameBuffer* EditorSceneFrameBuffer;
        FrameBuffer* EditorGUIFrameBuffer;

        //Shader
        Shader* TargetShader;

        Shader* GridShader2D;
        Shader* CheckerboardShader;
        Shader* BasicShader;
        Shader* TextureShader;
        Shader* TextureOutlineShader;
        Shader* LineShader;
        Shader* GizmosAxisShader;
        Shader* PhongShader;

        //Dependencies
        Engine* Engine;
        Coordinator* ECSCoord;

//        void Init();
//        void Update(float _dt);

        NATIVE_SYSTEM_OVERRIDE;

//        void OnStart() override;
//        void OnInputUpdate(float _dt) override;
//        void OnUpdate(float _dt) override;
//        void OnRender(float _dt) override;
//        void OnEnd() override;
    };
}