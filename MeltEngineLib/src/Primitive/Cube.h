#pragma once

#include "Core.h"
#include "Mesh.h"
#include "Vertex.h"

namespace MELT
{
    class Cube
    {
    public:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        Cube();
        ~Cube();

        void Draw() const;

        Mesh get_mesh() const;
    private:
        std::array<Vertex_1P1C1T1N, 24> m_vertices;
        std::array<GLuint, 36>          m_indices;
    };
}