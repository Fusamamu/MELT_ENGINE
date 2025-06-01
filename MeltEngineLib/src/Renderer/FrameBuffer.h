#pragma once
#include "Core.h"

namespace MELT
{
    class FrameBuffer
    {
    public:
        GLuint FBO;
        GLuint RBO;
        GLuint texture_id;

        FrameBuffer();
        ~FrameBuffer() = default;

        void RescaleFrameBuffer(const GLsizei& _w, const GLsizei& _h);
    };
}