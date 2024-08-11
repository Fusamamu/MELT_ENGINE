#pragma once
#include <iostream>
#include <array>
#include <GL/glew.h>
#include "Vertex.h"

namespace MELT
{
    class Quad
    {
    public:
        GLuint TextureID;

        Quad();
        ~Quad();

        void Draw();

    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        GLuint FBO;
        GLuint RBO;

        std::array<Vertex, 4> m_Vertices;
        std::array<GLuint, 6> m_Indices;
    };
}


