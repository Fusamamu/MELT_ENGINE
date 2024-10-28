#include "MeltEngine.h"
#include "Coordinator.h"
#include "RenderPipeline.h"

namespace MELT
{
    RenderPipeline::RenderPipeline()
    {
    }

    void RenderPipeline::Init(MELT::Engine *_engine)
    {
        m_Engine = _engine;

        aQuad = new Quad();
        aCube = new Cube();

        m_TargetShader      = new Shader("../MeltEngineLib/res/shaders/Phong.shader");
        m_MeshOutlineShader = new Shader("../MeltEngineLib/res/shaders/MeshOutline.shader");
        m_GridShader        = new Shader("../MeltEngineLib/res/shaders/3DGrid.shader");

        glm::mat4 _model      = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 _projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 0.1f, 100.0f);

        m_TargetShader->Use();
        m_TargetShader->SetMat4UniformModel     (_model);
        m_TargetShader->SetMat4UniformView      (_view);
        m_TargetShader->SetMat4UniformProjection(_projection);
        m_TargetShader->SetVec3UniformObjectColor(glm::vec3(1.0, 0.0, 0.0));
        m_TargetShader->SetVec3UniformLightColor (glm::vec3(1.0, 1.0, 1.0));
        m_TargetShader->SetFloatUniformObjectShininess(1.0f);
        m_TargetShader->SetVec3UniformLightWorldPosition(glm::vec3(100, 100, 100));

        m_MeshOutlineShader->Use();
        m_MeshOutlineShader->SetMat4UniformModel     (_model);
        m_MeshOutlineShader->SetMat4UniformView      (_view);
        m_MeshOutlineShader->SetMat4UniformProjection(_projection);

        m_GridShader->Use();
        m_GridShader->SetMat4UniformModel     (_model);
        m_GridShader->SetMat4UniformView      (_view);
        m_GridShader->SetMat4UniformProjection(_projection);

        EditorSceneFrameBuffer = new FrameBuffer();


        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    }

    void RenderPipeline::Render(float _dt)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, EditorSceneFrameBuffer->FBO);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glm::mat4 _view  = glm::lookAt(
                m_Engine->MainCamera.Position,
                glm::vec3(0.0),
                m_Engine->MainCamera.Up
        );

        glm::mat4 _projection = glm::ortho(
                -(Engine::ScreenWidth  / 2),
                (Engine::ScreenWidth  / 2),
                -(Engine::ScreenHeight / 2),
                (Engine::ScreenHeight / 2),
                0.1f, 100.0f);


        m_GridShader->Use();
        m_GridShader->SetMat4UniformModel(glm::translate(glm::mat4(1.0f), glm::vec3 (0.0, 0.0, 0.0)));
        m_GridShader->SetMat4UniformView(_view);
        m_GridShader->SetMat4UniformProjection(_projection);
        aQuad->Draw();


        for(const Node& _node : m_Engine->NodeMng.SceneNodes)
        {
            const Transform& _transform = m_Engine->ECSCoord.GetComponent<Transform>(_node.entityRef);

            float _xPos = _transform.Position.x;
            float _yPos = _transform.Position.y;
            float _zPos = _transform.Position.z;

            glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (_xPos, _yPos, _zPos));


            if(_node.isSelected)
            {
                // 1st. render pass, draw objects as normal, writing to the stencil buffer
                glStencilFunc(GL_ALWAYS, 1, 0xFF);
                glStencilMask(0xFF);

                m_TargetShader->Use();
                m_TargetShader->SetMat4UniformModel(_model);
                m_TargetShader->SetMat4UniformView(_view);
                m_TargetShader->SetMat4UniformProjection(_projection);
                m_TargetShader->SetVec3UniformCameraWorldPosition(m_Engine->MainCamera.Position);
                aCube->Draw();

                glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                glStencilMask(0x00);
                glDisable(GL_DEPTH_TEST);

                m_MeshOutlineShader->Use();
                glm::mat4 _scaledModel = glm::scale(_model, glm::vec3(1.05f, 1.05f, 1.05f));
                m_MeshOutlineShader->SetMat4UniformModel(_scaledModel);
                m_MeshOutlineShader->SetMat4UniformView(_view);
                m_MeshOutlineShader->SetMat4UniformProjection(_projection);
                aCube->Draw();

                glStencilMask(0xFF);
                glStencilFunc(GL_ALWAYS, 0, 0xFF);
                glEnable(GL_DEPTH_TEST);
            }
            else
            {
                m_TargetShader->Use();
                m_TargetShader->SetMat4UniformModel(_model);
                m_TargetShader->SetMat4UniformView(_view);
                m_TargetShader->SetMat4UniformProjection(_projection);
                m_TargetShader->SetVec3UniformCameraWorldPosition(m_Engine->MainCamera.Position);
                aCube->Draw();

                glStencilMask(0xFF);
                glStencilFunc(GL_ALWAYS, 0, 0xFF);
                glEnable(GL_DEPTH_TEST);
            }
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}