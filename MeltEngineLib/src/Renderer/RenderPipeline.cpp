#include "MeltEngine.h"
#include "RenderPipeline.h"

namespace MELT
{
    RenderPipeline::RenderPipeline():
        mp_window(nullptr),
        clear_color(222.0f/255.0f, 217.0f/255.0f, 226.0f/255.0f, 33.0f/255.0f),
        m_clearBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT),
        m_ubo(0)
    {
    }

    void RenderPipeline::Init(MELT::Engine *_engine)
    {
        m_engine = _engine;
        mp_window = m_engine->sdl_window;

        aQuad = new Quad();
        aCube = new Cube();

        m_TargetShader      = new Shader("../MeltEngineLib/res/shaders/Phong.shader");
        m_MeshOutlineShader = new Shader("../MeltEngineLib/res/shaders/MeshOutline.shader");
        m_GridShader        = new Shader("../MeltEngineLib/res/shaders/3DGrid.shader");
        m_gizmos_shader     = new Shader("../MeltEngineLib/res/shaders/Gizmos.shader");
        m_debug_line        = new Shader("../MeltEngineLib/res/shaders/CylinderLine.shader");
        m_camera_frustum    = new Shader("../MeltEngineLib/res/shaders/camera_frustum.shader");

        glm::mat4 _model      = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
        glm::mat4 _view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 _projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 0.1f, 100.0f);

        m_TargetShader->Use();
        m_TargetShader->SetMat4UniformModel     (_model);
        m_TargetShader->SetMat4UniformView      (_view);
        m_TargetShader->SetMat4UniformProjection(_projection);
        m_TargetShader->SetVec3UniformObjectColor(glm::vec3(0.8, 0.0, 0.0));
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

        m_gizmos_shader->Use();
        m_gizmos_shader->SetMat4UniformModel     (_model);
        m_gizmos_shader->SetMat4UniformView      (_view);
        m_gizmos_shader->SetMat4UniformProjection(_projection);
        m_gizmos_shader->SetVec3UniformColor(glm::vec3(1.0, 1.0, 1.0));

        m_debug_line->Use();
        m_debug_line->SetMat4UniformView      (_view);
        m_debug_line->SetMat4UniformProjection(_projection);
        m_debug_line->SetVec3UniformColor(glm::vec3(1.0, 1.0, 1.0));

        m_camera_frustum->Use();
        m_camera_frustum->SetMat4UniformView      (_view);
        m_camera_frustum->SetMat4UniformProjection(_projection);

        editor_scene_frame_buffer = new FrameBuffer();

        glEnable     (GL_DEPTH_TEST);
        glDepthFunc  (GL_LESS);

        glEnable     (GL_BLEND);
        glBlendFunc  (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable     (GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp  (GL_KEEP, GL_KEEP, GL_REPLACE);

        MeshData* _sphere_mesh_data = _engine->manager_registry.get<ResourceManager>()->get_mesh_data("Sphere");
        shader_preview.init();
        shader_preview.preview_renderer.set_mesh_data(_sphere_mesh_data);
        shader_preview.preview_renderer.set_buffer_data();

        aabb_gizmos_renderer.init(GizmosRenderType::CUBE);
        aabb_gizmos_renderer.set_bounds
                (
                    {
                    M_VEC3(-0.6f, -0.6f, -0.6f),
                    M_VEC3( 0.6f,  0.6f,  0.6f)
                    }
                );

        camera_frustum_renderer.init(GizmosRenderType::CAMERA_FRUSTUM);
        camera_frustum_renderer.set_bounds();

        line_renderer.set_mesh_data(&_engine->manager_registry.get<ResourceManager>()->debug_line);
        line_renderer.set_buffer_data();

        MeshData* _quad_mesh_data = _engine->manager_registry.get<ResourceManager>()->get_mesh_data("default_quad");
        m_grid_renderer = new MeshRenderer();
        m_grid_renderer->set_mesh_data(_quad_mesh_data);
        m_grid_renderer->set_buffer_data();
    }

    void RenderPipeline::Render(float _dt)
    {
        Scene* _working_scene = m_engine->manager_registry.get<SceneManager>()->working_scene;

        shader_preview.Render();

        glBindFramebuffer(GL_FRAMEBUFFER, editor_scene_frame_buffer->FBO);

        BeginFrame();

        glm::mat4 _view       = m_engine->main_camera.get_view_matrix();
        glm::mat4 _projection = m_engine->main_camera.get_orthographic_projection_matrix();

        m_GridShader->Use();
        m_GridShader->SetMat4UniformModel(glm::translate(glm::mat4(1.0f), glm::vec3 (0.0, 0.0, 0.0)));
        m_GridShader->SetMat4UniformView(_view);
        m_GridShader->SetMat4UniformProjection(_projection);
        m_grid_renderer->draw();

        auto _light_view = _working_scene->ecs_registry.view<Transform, Light>();

        for (auto _entity : _light_view)
        {
            auto& _transform = _light_view.get<Transform>(_entity);

            m_TargetShader->Use();
            m_TargetShader->SetVec3UniformLightWorldPosition(_transform.position);
        }

        auto _object_view = _working_scene->ecs_registry.view<Transform, MeshRenderer, NodeEditor>();

        for (auto _entity : _object_view)
        {
            auto& _transform     = _object_view.get<Transform>   (_entity);
            auto& _mesh_renderer = _object_view.get<MeshRenderer>(_entity);
            auto& _node_editor   = _object_view.get<NodeEditor>  (_entity);

            glm::mat4 _model = _transform.get_transform_matrix();

             if(_node_editor.is_selected)
             {
                 // 1st. render pass, draw objects as normal, writing to the stencil buffer
                 glStencilFunc(GL_ALWAYS, 1, 0xFF);
                 glStencilMask(0xFF);

                 m_TargetShader->Use();
                 m_TargetShader->SetMat4UniformModel     (_model);
                 m_TargetShader->SetMat4UniformView      (_view);
                 m_TargetShader->SetMat4UniformProjection(_projection);
                 _mesh_renderer.draw();

                 glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                 glStencilMask(0x00);
                 glDisable(GL_DEPTH_TEST);

                 m_MeshOutlineShader->Use();
                 glm::mat4 _scaledModel = glm::scale(_model, glm::vec3(1.05f, 1.05f, 1.05f));
                 m_MeshOutlineShader->SetMat4UniformModel     (_scaledModel);
                 m_MeshOutlineShader->SetMat4UniformView      (_view);
                 m_MeshOutlineShader->SetMat4UniformProjection(_projection);
                 _mesh_renderer.draw();

                 glStencilMask(0xFF);
                 glStencilFunc(GL_ALWAYS, 0, 0xFF);
                 glEnable(GL_DEPTH_TEST);
             }
             else
             {
                 m_TargetShader->Use();
                 m_TargetShader->SetMat4UniformModel     (_model);
                 m_TargetShader->SetMat4UniformView      (_view);
                 m_TargetShader->SetMat4UniformProjection(_projection);
                 _mesh_renderer.draw();

                 glStencilMask(0xFF);
                 glStencilFunc(GL_ALWAYS, 0, 0xFF);
                 glEnable(GL_DEPTH_TEST);
             }

            m_gizmos_shader->Use();
            m_gizmos_shader->SetMat4UniformModel(_model);
            m_gizmos_shader->SetMat4UniformView(_view);
            m_gizmos_shader->SetMat4UniformProjection(_projection);
            aabb_gizmos_renderer.draw();
        }

        m_debug_line->Use();
        m_debug_line->SetMat4UniformView(_view);
        m_debug_line->SetMat4UniformProjection(_projection);
        line_renderer.draw();

        auto _camera_view = _working_scene->ecs_registry.view<Camera>();
        for (auto _entity : _camera_view)
        {
            auto& _camera = _camera_view.get<Camera>(_entity);

            std::array<M_VEC3, 8> _corners = _camera.get_orthographic_frustum_corners();

            m_camera_frustum->Use();
            glUniform3fv(glGetUniformLocation(m_camera_frustum->ID, "corners"), 8, glm::value_ptr(_corners[0]));
            m_camera_frustum->SetMat4UniformView(_view);
            m_camera_frustum->SetMat4UniformProjection(_projection);
            camera_frustum_renderer.draw_camera_frustum();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}