#pragma once

#include "Core.h"
#include "Mesh.h"
#include "Vertex.h"

namespace MELT
{
    class Cube
    {
    public:
        Cube();
        ~Cube() = default;

        Mesh get_mesh() const;

    private:
        std::array<Vertex_PCTN, 24> m_vertices;
        std::array<GLuint, 36>      m_indices;
    };
}