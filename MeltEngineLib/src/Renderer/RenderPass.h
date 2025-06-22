#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include "CommandBuffer.h"
#include "Core.h"
#include "FrameBuffer.h"
#include "Shader.h"

namespace MELT::GRAPHIC
{
    class RenderPass
    {
    public:
        std::string name;

        CommandBuffer command_buffer;

        RenderPass(std::string _name):
            name(_name),
            m_clear_color(M_VEC4(0.0f, 0.0f, 0.0f, 1.0f)),
            m_clear_buffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
        {

        }
        RenderPass():
            name("render pass"),
            m_clear_color(M_VEC4(0.0f, 0.0f, 0.0f, 1.0f)),
            m_clear_buffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) {}

        ~RenderPass() = default;

        void begin()
        {
            glClearColor(m_clear_color.x, m_clear_color.y, m_clear_color.z, m_clear_color.w);
            glClear     (m_clear_buffers);
        }

        void execute()
        {
            command_buffer.execute();
        }

        void end()
        {
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            glEnable     (GL_DEPTH_TEST);
        }

    private:
        M_VEC4     m_clear_color;
        GLbitfield m_clear_buffers;
    };
}

#endif
