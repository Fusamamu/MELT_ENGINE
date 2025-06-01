#include "ShaderPreview.h"

namespace MELT
{
    void ShaderPreview::init()
    {
        p_target_shader = new Shader("../MeltEngineLib/res/shaders/Basic.shader");

        glm::mat4 _model      = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 _projection = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, -100.0f, 500.0f);

        p_target_shader->Use();
        p_target_shader->SetMat4UniformModel     (_model);
        p_target_shader->SetMat4UniformView      (_view);
        p_target_shader->SetMat4UniformProjection(_projection);

        clear_color = glm::vec4(0.25f, 0.20f, 0.23f, 0.13f);
    }

    void ShaderPreview::Render() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, preview_fbo.FBO);
        glEnable(GL_DEPTH_TEST);

        glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        p_target_shader->Use();
        p_target_shader->SetVec3UniformColor(glm::vec3(1.0f, 1.0f, 1.0f));
        cube.Draw();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}