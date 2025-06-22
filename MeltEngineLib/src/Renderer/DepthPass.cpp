#include "DepthPass.h"

namespace MELT
{
    void DepthPass::init()
    {
        p_target_shader = new Shader("../MeltEngineLib/res/shaders/depth.shader");

        glm::mat4 _model      = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 _projection = glm::ortho(-0.7f, 0.7f, -0.7f, 0.7f, -100.0f, 500.0f);

        p_target_shader->use();
        p_target_shader->set_mat4_uniform_model     (_model);
        p_target_shader->set_mat4_uniform_view      (_view);
        p_target_shader->set_mat4_uniform_projection(_projection);

        clear_color = glm::vec4(0.25f, 0.20f, 0.23f, 0.13f);
    }

    void DepthPass::Render(const Scene& _scene)
    {
        float SHADOW_WIDTH  = 2048;
        float SHADOW_HEIGHT = 2048;

        //glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

        frame_buffer.bind();

            glClear(GL_DEPTH_BUFFER_BIT);

            p_target_shader->use();

            auto _object_view = _scene.ecs_registry.view<Transform, MeshRenderer, NodeEditor>();

            for (auto _entity : _object_view)
            {
                auto& _transform     = _object_view.get<Transform>   (_entity);
                auto& _mesh_renderer = _object_view.get<MeshRenderer>(_entity);

                glm::mat4 _model = _transform.get_transform_matrix();

                _mesh_renderer.draw();
            }

        frame_buffer.unbind();
    }
}