#include "RenderSystem.h"
#include "MeltEngine.h"

namespace MELT
{
    void RenderSystem::Init()
    {
        m_Quad    = new Quad();
        DummyLine = new Line();

        GridShader2D       = new Shader("../MeltEngineLib/res/shaders/2DGrid.shader");
        CheckerboardShader = new Shader("../MeltEngineLib/res/shaders/CheckerboardPattern.shader");
        BasicShader        = new Shader("../MeltEngineLib/res/shaders/Basic.shader");
        TextureShader      = new Shader("../MeltEngineLib/res/shaders/Texture.shader");
        LineShader         = new Shader("../MeltEngineLib/res/shaders/Line.shader");

        glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        _model = glm::scale(_model, glm::vec3(25.0f, 25.0f, 1.0f));
        glm::mat4 _view  = glm::lookAt(
                glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 _projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 0.1f, 100.0f);

        GridShader2D->Use();
        GridShader2D->SetMat4UniformModel     (_model);
        GridShader2D->SetMat4UniformView      (_view);
        GridShader2D->SetMat4UniformProjection(_projection);
        GridShader2D->SetVec2UniformScreenSize(glm::vec2(800, 600));

        CheckerboardShader->Use();

        BasicShader->Use();
        BasicShader->SetMat4UniformModel     (_model);
        BasicShader->SetMat4UniformView      (_view);
        BasicShader->SetMat4UniformProjection(_projection);
        BasicShader->SetVec2UniformScreenSize(glm::vec2(800, 600));
        BasicShader->SetVec3UniformColor(glm::vec3(1.0f, 1.0f, 1.0f));

        TextureShader->Use();
        TextureShader->SetMat4UniformModel     (_model);
        TextureShader->SetMat4UniformView      (_view);
        TextureShader->SetMat4UniformProjection(_projection);
        TextureShader->SetVec2UniformScreenSize(glm::vec2(800, 600));
        TextureShader->SetVec3UniformColor(glm::vec3(1.0f, 1.0f, 1.0f));

        LineShader->Use();
        LineShader->SetMat4UniformModel     (_model);
        LineShader->SetMat4UniformView      (_view);
        LineShader->SetMat4UniformProjection(_projection);
        LineShader->SetVec3UniformColor(glm::vec3(1.0f, 0.0f, 0.0f));

        EditorSceneFrameBuffer = new FrameBuffer();
        EditorGUIFrameBuffer   = new FrameBuffer();

        TargetShader = BasicShader;
    }


    void drawLine(float x1, float y1, float x2, float y2) {
        glColor3f(1.0f, 0.0f, 0.0f);  // Set the color to red
        glBegin(GL_LINES);             // Start drawing lines
        glVertex2f(x1, y1);        // First point of the line
        glVertex2f(x2, y2);        // Second point of the line
        glEnd();                       // End drawing lines
    }

    void RenderSystem::Update(float _dt)
    {
        ///Temp
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //Render Checkerboard
        glBindFramebuffer(GL_FRAMEBUFFER, EditorGUIFrameBuffer->FBO);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //glActiveTexture(GL_TEXTURE0);
        CheckerboardShader->Use();
        m_Quad->Draw();


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Engine->TextureMng.TextureDataTable["blacknwhite"].TextureID);
        BasicShader->Use();
        m_Quad->Draw();
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //-----------------------------------------


        glBindFramebuffer(GL_FRAMEBUFFER, EditorSceneFrameBuffer->FBO);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        GridShader2D->Use();
//        GridShader2D->SetVec2UniformScreenSize(glm::vec2(Engine::ScreenWidth, Engine::ScreenHeight));
//        m_Quad->Draw();

//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, Engine->TextureMng.TextureDataTable["blacknwhite"].TextureID);

        TargetShader->Use();

        glm::mat4 _projection = glm::ortho(
                -(Engine::ScreenWidth  / 2) - Engine::CurrentOffset.x,
                (Engine::ScreenWidth  / 2) - Engine::CurrentOffset.x,
                -(Engine::ScreenHeight / 2) + Engine::CurrentOffset.y,
                (Engine::ScreenHeight / 2) + Engine::CurrentOffset.y,
                0.1f, 100.0f);

        TargetShader->SetMat4UniformProjection(_projection);

        for(const auto& _entity : Entities)
        {
            auto& _transform = ECSCoord->GetComponent<Transform>(_entity);

            auto _xPos = _transform.Position.x;
            auto _yPos = _transform.Position.y;

            TargetShader->Use();
            glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (_xPos, _yPos, 0.0f));
            _model = glm::scale(_model, glm::vec3(25.0f, 25.0f, 1.0f));
            TargetShader->SetMat4UniformModel(_model);
            m_Quad->Draw();
        }

        LineShader->Use();
        DummyLine->Draw();


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}