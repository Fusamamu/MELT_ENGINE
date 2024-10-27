#include "RenderSystem.h"
#include "MeltEngine.h"

namespace MELT
{
    void RenderSystem::Init()
    {
        aQuad      = new Quad();
        aCube      = new Cube();
        DummyLine  = new Line();
        GizmosAxis = new GizmosTransform();

        GridShader2D         = new Shader("../MeltEngineLib/res/shaders/2DGrid.shader");
        CheckerboardShader   = new Shader("../MeltEngineLib/res/shaders/CheckerboardPattern.shader");
        BasicShader          = new Shader("../MeltEngineLib/res/shaders/Basic.shader");
        TextureShader        = new Shader("../MeltEngineLib/res/shaders/Texture.shader");
        TextureOutlineShader = new Shader("../MeltEngineLib/res/shaders/TextureOutline.shader");
        LineShader           = new Shader("../MeltEngineLib/res/shaders/Line.shader");
        GizmosAxisShader     = new Shader("../MeltEngineLib/res/shaders/GizmosAxis.shader");
        PhongShader          = new Shader("../MeltEngineLib/res/shaders/Phong.shader");

        glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        //_model = glm::scale(_model, glm::vec3(25.0f, 25.0f, 1.0f));
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
        BasicShader->SetVec3UniformColor(glm::vec3(1.0f, 1.0f, 1.0f));

        TextureShader->Use();
        TextureShader->SetMat4UniformModel     (_model);
        TextureShader->SetMat4UniformView      (_view);
        TextureShader->SetMat4UniformProjection(_projection);
        TextureShader->SetVec3UniformColor(glm::vec3(1.0f, 1.0f, 1.0f));

        TextureOutlineShader->Use();
        TextureOutlineShader->SetMat4UniformModel     (_model);
        TextureOutlineShader->SetMat4UniformView      (_view);
        TextureOutlineShader->SetMat4UniformProjection(_projection);
        TextureOutlineShader->SetVec3UniformColor(glm::vec3(1.0f, 1.0f, 1.0f));

        LineShader->Use();
        LineShader->SetMat4UniformModel     (_model);
        LineShader->SetMat4UniformView      (_view);
        LineShader->SetMat4UniformProjection(_projection);
        LineShader->SetVec3UniformColor(glm::vec3(1.0f, 0.0f, 0.0f));

        _model = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));

        GizmosAxisShader->Use();
        GizmosAxisShader->SetMat4UniformModel     (_model);
        GizmosAxisShader->SetMat4UniformView      (_view);
        GizmosAxisShader->SetMat4UniformProjection(_projection);

        PhongShader->Use();
        PhongShader->SetMat4UniformModel     (_model);
        PhongShader->SetMat4UniformView      (_view);
        PhongShader->SetMat4UniformProjection(_projection);
        PhongShader->SetVec3UniformObjectColor(glm::vec3(1.0, 0.0, 0.0));
        PhongShader->SetVec3UniformLightColor (glm::vec3(1.0, 1.0, 1.0));
        PhongShader->SetFloatUniformObjectShininess(1.0f);
        PhongShader->SetVec3UniformLightWorldPosition(glm::vec3(100, 100, 100));
        //PhongShader->SetVec3UniformCameraWorldPosition(Engine->MainCamera.Position);

        EditorSceneFrameBuffer = new FrameBuffer();
        EditorGUIFrameBuffer   = new FrameBuffer();

        TargetShader = TextureShader;

        std::array<glm::vec2, 4> _texCoords { };
        _texCoords[0] = glm::vec2 (0.125, 0.0);
        _texCoords[1] = glm::vec2 (0.125, 0.166);
        _texCoords[2] = glm::vec2 (0.0  , 0.166);
        _texCoords[3] = glm::vec2 (0.0  , 0.0);
        aQuad->SetTexCoords(_texCoords);
    }

    void RenderSystem::Update(float _dt)
    {
        //Sprite sheet editor gui
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindFramebuffer(GL_FRAMEBUFFER, EditorGUIFrameBuffer->FBO);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CheckerboardShader->Use();
        aQuad->Draw();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        //-----------------------------------//
        glBindFramebuffer(GL_FRAMEBUFFER, EditorSceneFrameBuffer->FBO);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        GridShader2D->Use();
//        GridShader2D->SetVec2UniformScreenSize(glm::vec2(Engine::ScreenWidth, Engine::ScreenHeight));
//        aQuad->Draw();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Engine->TextureMng.TextureDataTable["blacknwhite"].TextureID);

//        glm::mat4 _view  = glm::lookAt(
//                Engine->MainCamera.Position,
//                glm::vec3(Engine->MainCamera.Target.x + Engine->MainCamera.Position.x,
//                          Engine->MainCamera.Target.y + Engine->MainCamera.Position.y,
//                          Engine->MainCamera.Target.z),
//                Engine->MainCamera.Up
//        );


        glm::mat4 _view  = glm::lookAt(
                Engine->MainCamera.Position,
                glm::vec3(0.0),
                Engine->MainCamera.Up
        );

        glm::mat4 _projection = glm::ortho(
                -(Engine::ScreenWidth  / 2),
                 (Engine::ScreenWidth  / 2),
                -(Engine::ScreenHeight / 2),
                 (Engine::ScreenHeight / 2),
                0.1f, 100.0f);

        TargetShader->Use();
        TargetShader->SetMat4UniformView(_view);
        TargetShader->SetMat4UniformProjection(_projection);

        TextureOutlineShader->Use();
        TextureOutlineShader->SetMat4UniformView(_view);
        TextureOutlineShader->SetMat4UniformProjection(_projection);

        for(const unsigned int& _entity : Entities)
        {
            Transform& _transform = ECSCoord->GetComponent<Transform>(_entity);

            float _xPos = _transform.Position.x;
            float _yPos = _transform.Position.y;

            glm::mat4 _model = glm::translate(glm::mat4(1.0f), glm::vec3 (_xPos, _yPos, 0.0f));

            TargetShader->Use();
            TargetShader->SetMat4UniformModel(_model);

            if(ECSCoord->SelectedEntity == _entity)
            {
                TextureOutlineShader->Use();
                TextureOutlineShader->SetMat4UniformModel(_model);
            }

            aQuad->Draw();
        }

        PhongShader->Use();
        PhongShader->SetMat4UniformView(_view);
        PhongShader->SetMat4UniformProjection(_projection);
        PhongShader->SetVec3UniformCameraWorldPosition(Engine->MainCamera.Position);
        aCube->Draw();

        glDisable(GL_DEPTH_TEST);
        LineShader->Use();
        LineShader->SetMat4UniformView(_view);
        LineShader->SetMat4UniformProjection(_projection);
        DummyLine->Draw();

        GizmosAxisShader->Use();
        GizmosAxisShader->SetMat4UniformView(_view);
        GizmosAxisShader->SetMat4UniformProjection(_projection);
        GizmosAxis->Draw();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}