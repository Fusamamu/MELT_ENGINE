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
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        Quad();
        ~Quad();

        void Draw();
        void SetTexCoords(std::array<glm::vec2, 4> _texCoords);

    private:
        std::array<Vertex, 4> m_Vertices;
        std::array<GLuint, 6> m_Indices;
    };
}


