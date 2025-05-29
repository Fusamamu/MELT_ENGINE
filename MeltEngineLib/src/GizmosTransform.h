#pragma once
#include <iostream>
#include <array>
#include <GL/glew.h>
#include "Vertex.h"

namespace MELT
{
    class GizmosTransform
    {
    public:
        GLuint VAO;
        GLuint VBO;

        GizmosTransform();
        ~GizmosTransform();

        void Draw();

    private:
        GLfloat m_Vertices[24] =
                {
                    // X axis (red)
                     0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Start
                     1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // End
                    // Y axis (green)
                     0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Start
                     0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f  // End
                };
    };
}