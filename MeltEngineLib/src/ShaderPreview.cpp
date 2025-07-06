#include "ShaderPreview.h"

namespace MELT
{
    void ShaderPreview::init()
    {
        p_target_shader = new Shader("../MeltEngineLib/res/shaders/Basic.shader");

        glm::mat4 _model      = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 _projection = glm::ortho(-0.7f, 0.7f, -0.7f, 0.7f, -100.0f, 500.0f);

        p_target_shader->use();
        p_target_shader->set_mat4_uniform_model     (_model);
        p_target_shader->set_mat4_uniform_view      (_view);
        p_target_shader->set_mat4_uniform_projection(_projection);

        clear_color = glm::vec4(0.25f, 0.20f, 0.23f, 0.13f);

        preview_fbo.create(1600, 1200);
    }

    void ShaderPreview::render()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, preview_fbo.fbo);
        glEnable(GL_DEPTH_TEST);

        glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glm::mat4 _model      = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 _projection = glm::ortho(-0.7f, 0.7f, -0.7f, 0.7f, -100.0f, 500.0f);

        p_target_shader->use();
        p_target_shader->set_mat4_uniform_model     (_model);
        p_target_shader->set_mat4_uniform_view      (_view);
        p_target_shader->set_mat4_uniform_projection(_projection);
        p_target_shader->set_vec3_uniform_color(glm::vec3(1.0f, 1.0f, 1.0f));
        preview_renderer.draw();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GRAPHIC::Material& ShaderPreview::get_preview_material()
    {
        return *mp_target_material;
    }

    void ShaderPreview::set_preview_target_material(GRAPHIC::Material* _material)
    {
        mp_target_material = _material;
        mp_target_material->validate();

        p_target_shader = mp_target_material->get_cached_shader();

        glm::vec3 _color = mp_target_material->vec4_uniforms["color"];

        glm::mat4 _model      = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 _projection = glm::ortho(-0.7f, 0.7f, -0.7f, 0.7f, -100.0f, 500.0f);

        p_target_shader->use();
        p_target_shader->set_mat4_uniform_model     (_model);
        p_target_shader->set_mat4_uniform_view      (_view);
        p_target_shader->set_mat4_uniform_projection(_projection);

        p_target_shader->set_vec3_uniform_object_color(_color);
        p_target_shader->set_vec3_uniform_light_color (glm::vec3(1.0, 1.0, 1.0));
        p_target_shader->set_float_uniform_object_shininess(1.0f);
        p_target_shader->set_vec3_uniform_light_world_position(glm::vec3(100, 100, 0));
        p_target_shader->set_vec3_uniform_light_world_target(glm::vec3(0, 0, 0));
    }
}
