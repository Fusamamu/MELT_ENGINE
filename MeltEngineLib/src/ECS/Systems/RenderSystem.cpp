#include "RenderSystem.h"
#include "MeltEngine.h"

namespace MELT
{
    void RenderSystem::Init()
    {
        m_Quad = new Quad();

        m_BasicShader  = new Shader("../MeltEngineLib/res/shaders/Basic.shader");
        m_2DGridShader = new Shader("../MeltEngineLib/res/shaders/2DGrid.shader");

        glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        _model = glm::scale(_model, glm::vec3(25.0f, 25.0f, 1.0f));
        glm::mat4 _view  = glm::lookAt(
                glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 _projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 0.1f, 100.0f);

        m_2DGridShader->Use();
        m_2DGridShader->SetMat4UniformModel     (_model);
        m_2DGridShader->SetMat4UniformView      (_view);
        m_2DGridShader->SetMat4UniformProjection(_projection);
        m_2DGridShader->SetVec2UniformScreenSize(glm::vec2(800, 600));

        m_BasicShader->Use();
        m_BasicShader->SetMat4UniformModel     (_model);
        m_BasicShader->SetMat4UniformView      (_view);
        m_BasicShader->SetMat4UniformProjection(_projection);
        m_BasicShader->SetVec2UniformScreenSize(glm::vec2(800, 600));
        m_BasicShader->SetVec3UniformColor(glm::vec3(1.0f, 1.0f, 1.0f));

        mFrameBuffer = new FrameBuffer();
    }

    void RenderSystem::Update(float _dt)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer->FBO);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        m_2DGridShader->Use();
//        m_2DGridShader->SetVec2UniformScreenSize(glm::vec2(Engine::ScreenWidth, Engine::ScreenHeight));
//        m_Quad->Draw();

        m_BasicShader->Use();

        glm::mat4 _projection = glm::ortho(
                -(Engine::ScreenWidth  / 2) - Engine::CurrentOffset.x,
                (Engine::ScreenWidth  / 2) - Engine::CurrentOffset.x,
                -(Engine::ScreenHeight / 2) + Engine::CurrentOffset.y,
                (Engine::ScreenHeight / 2) + Engine::CurrentOffset.y,
                0.1f, 100.0f);

        m_BasicShader->SetMat4UniformProjection(_projection);

        for(const auto& _entity : Entities)
        {
            auto& _transform = ECSCoord->GetComponent<Transform>(_entity);

            auto _xPos = _transform.Position.x;
            auto _yPos = _transform.Position.y;

            m_BasicShader->Use();
            glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (_xPos, _yPos, 0.0f));
            _model = glm::scale(_model, glm::vec3(25.0f, 25.0f, 1.0f));
            m_BasicShader->SetMat4UniformModel(_model);
            m_Quad->Draw();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}