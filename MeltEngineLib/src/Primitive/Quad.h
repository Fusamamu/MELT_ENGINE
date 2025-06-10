#pragma once
#include "Core.h"
#include "Mesh.h"
#include "Vertex.h"

namespace MELT
{
    class Quad
    {
    public:
        Quad();
        ~Quad() = default;

        Mesh get_mesh() const;
        void SetTexCoords(std::array<glm::vec2, 4> _texCoords);

    private:
        std::array<Vertex_PCT, 4> m_Vertices;
        std::array<GLuint, 6> m_Indices;
    };
}


