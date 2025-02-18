#pragma once
#include "Core.h"
#include "Shader.h"
#include "Quad.h"

namespace MELT
{
    class Engine;

    class RenderPipeline
    {
    public:
        FrameBuffer* EditorSceneFrameBuffer;

        RenderPipeline();
        void Init(Engine* _engine);
        void Render(float _dt);
    private:
        Quad* aQuad;
        Cube* aCube;
        Engine* m_Engine;
        Shader* m_TargetShader;

        Shader* m_MeshOutlineShader;
        Shader* m_GridShader;
    };
}


//    public:
//        void OnInit() override;
//        void OnRender(float dt) override;
//
//    private:
//        SharedPtr<Shader> m_shader { nullptr };
//        SharedPtr<Shader> m_lightShader { nullptr };
//
//        // debug mesh for light
//        SharedPtr<Mesh> m_debugLightMesh { nullptr };
