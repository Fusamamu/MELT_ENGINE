#pragma once
#include "Core.h"
#include "Shader.h"
#include "Quad.h"
#include "ShaderPreview.h"
#include "GizmosRenderer.h"
#include "LineRenderer.h"
#include "DepthPass.h"
#include "RenderPass.h"
#include "RenderCommand.h"

namespace MELT
{
    class Engine;

    class RenderPipeline
    {
    public:
        enum class RenderStateAction
        {
            ENABLE,
            DISABLE
        };

        GRAPHIC::RenderPass geometry_pass;
        GRAPHIC::RenderPass outline_pass;

        ShaderPreview shader_preview;
        DepthPass     depth_pass;

        GizmosRenderer aabb_gizmos_renderer;
        GizmosRenderer camera_frustum_renderer;
        LineRenderer   line_renderer;

        glm::vec4   clear_color;
        FrameBuffer editor_scene_frame_buffer;
        FrameBuffer depth_buffer;

        RenderPipeline();

        void Init(Engine* _engine);
        void BeginFrame() const;
        void Render(float _dt);
        void EndFrame  () const;

        void SetUpUBO()
        {
            glGenBuffers(1, &m_ubo);

            glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
            glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo, 0, 2 * sizeof(glm::mat4));
        }

        void UpdateCameraData(const Camera& _camera) const
        {
            constexpr auto _m4Size = sizeof(glm::mat4);

            glBindBuffer   (GL_UNIFORM_BUFFER, m_ubo);
            glBufferSubData(GL_UNIFORM_BUFFER, 0                , sizeof(glm::mat4), glm::value_ptr(_camera.get_view_matrix()));
            glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(_camera.get_orthographic_projection_matrix()));
            glBindBuffer   (GL_UNIFORM_BUFFER, 0);
        }

        void SetRenderStates(RenderStateAction _action, std::initializer_list<GLenum> _states) const
        {
            for(GLenum _state : _states)
            {
                switch(_action)
                {
                    case RenderStateAction::ENABLE:
                        glEnable(_state);
                    break;
                    case RenderStateAction::DISABLE:
                        glDisable(_state);
                    break;
                }
            }
        }

        void* shader_preview_texture()
        {
            return (void*)(intptr_t)shader_preview.preview_fbo.texture_id;
        }

        void rescale_frame_buffers(const GLsizei& _w, const GLsizei& _h)
        {
            editor_scene_frame_buffer .resize(_w, _h);
            shader_preview.preview_fbo.resize(_w, _h);

            //geometry_pass.render_target.resize(_w, _h);
        }

    private:
        Engine* m_engine;

        Quad* aQuad;
        Cube* aCube;

        MeshRenderer* m_grid_renderer;
        MeshRenderer* m_quad_renderer;

        Shader* m_TargetShader;
        Shader* m_phong_shader;
        Shader* m_MeshOutlineShader;
        Shader* m_GridShader;
        Shader* m_gizmos_shader;
        Shader* m_debug_line;
        Shader* m_camera_frustum;
        Shader* m_depth_shader;
        Shader* m_screen_quad_shader;

        SDL_Window* mp_window;
        GLbitfield m_clearBuffers;

        unsigned int m_ubo;
    };
}
