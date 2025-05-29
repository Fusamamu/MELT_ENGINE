#pragma once
#include <iostream>
#include <array>
#include <GL/glew.h>
#include "FrameBuffer.h"

namespace MELT
{
    class FrameBuffer
    {
    public:

        GLuint FBO;
        GLuint RBO;
        GLuint TextureID;

        FrameBuffer();
        ~FrameBuffer();

        void RescaleFrameBuffer(const GLsizei& _w, const GLsizei& _h);
    };
}