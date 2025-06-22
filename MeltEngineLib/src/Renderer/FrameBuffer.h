#pragma once
#include "Core.h"

namespace MELT
{
    class FrameBuffer
    {
    public:
        GLuint fbo;
        GLuint rbo;
        GLuint texture_id;

        FrameBuffer();
        ~FrameBuffer() = default;

        void create(GLsizei _w, GLsizei _h);
        void bind();
        void unbind();
        void resize(const GLsizei& _w, const GLsizei& _h);
    };
}