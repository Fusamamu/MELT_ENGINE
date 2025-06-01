#pragma once
#include "Core.h"
#include "Shader.h"
#include "Quad.h"
#include "ShaderPreview.h"

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

        ShaderPreview shader_preview;

        glm::vec4 clear_color;
        FrameBuffer* editor_scene_frame_buffer;
        //FrameBuffer material_preview_frame_buffer;

        RenderPipeline();

        void Init(Engine* _engine);
        void Render(float _dt);

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
            glBufferSubData(GL_UNIFORM_BUFFER, 0                , sizeof(glm::mat4), glm::value_ptr(_camera.GetViewMatrix()));
            glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(_camera.GetOrthographicProjectionMatrix()));
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

        void BeginFrame() const
        {
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(m_clearBuffers);
        }

        void EndFrame()
        {
            SDL_GL_SwapWindow(mp_window);
        }

        void* shader_preview_texture()
        {
            return (void*)(intptr_t)shader_preview.preview_fbo.texture_id;
        }

        void rescale_frame_buffers(const GLsizei& _w, const GLsizei& _h)
        {
            editor_scene_frame_buffer->RescaleFrameBuffer(_w, _h);
            shader_preview.preview_fbo.RescaleFrameBuffer(_w, _h);
        }

    private:
        Quad* aQuad;
        Cube* aCube;

        Engine* m_Engine;

        Shader* m_TargetShader;
        Shader* m_MeshOutlineShader;
        Shader* m_GridShader;

        SDL_Window* mp_window;
        GLbitfield m_clearBuffers;


        unsigned int m_ubo;
    };
}
