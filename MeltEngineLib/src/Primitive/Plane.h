#pragma once

#include "Core.h"
#include "Mesh.h"
#include "Vertex.h"

namespace MELT
{
    class Plane
    {
    public:
        Plane(uint32_t _x_segments = 1, uint32_t _z_segments = 1, float _width = 1.0f, float _depth = 1.0f);
        ~Plane() = default;

        Mesh get_mesh() const;

    private:
        std::vector<Vertex_PCTN> m_vertices;
        std::vector<GLuint>      m_indices;

        void generate(uint32_t _x_segments, uint32_t _z_segments, float _width, float _depth);
    };
}
