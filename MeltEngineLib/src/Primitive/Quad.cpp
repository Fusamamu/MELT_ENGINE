#include "Quad.h"

namespace MELT
{
    Quad::Quad()
    {
        m_Vertices[0].position = glm::vec3( 1.0f,  1.0f, 0.0f);
        m_Vertices[1].position = glm::vec3( 1.0f, -1.0f, 0.0f);
        m_Vertices[2].position = glm::vec3(-1.0f, -1.0f, 0.0f);
        m_Vertices[3].position = glm::vec3(-1.0f,  1.0f, 0.0f);

        m_Vertices[0].color    = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Vertices[1].color    = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Vertices[2].color    = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Vertices[3].color    = glm::vec3(1.0f, 1.0f, 1.0f);

        m_Vertices[0].texCoord = glm::vec2(1.0f, 1.0f);
        m_Vertices[1].texCoord = glm::vec2(1.0f, 0.0f);
        m_Vertices[2].texCoord = glm::vec2(0.0f, 0.0f);
        m_Vertices[3].texCoord = glm::vec2(0.0f, 1.0f);

        m_Indices =
        {
            1, 3, 0,
            1, 2, 3
        };
    }

    Mesh Quad::get_mesh() const
    {
        Mesh _mesh;

        _mesh.vertex_buffer.resize(m_Vertices.size() * sizeof(Vertex_PCT));
        _mesh.index_buffer .resize(m_Indices .size() * sizeof(unsigned int));

        memcpy(_mesh.vertex_buffer.data(), m_Vertices.data(), _mesh.vertex_buffer.size());
        memcpy(_mesh.index_buffer .data(), m_Indices .data(), _mesh.index_buffer .size());

        _mesh.layout = createLayout_PCT();

        return _mesh;
    }

    void Quad::SetTexCoords(std::array<glm::vec2, 4> _texCoords)
    {
        m_Vertices[0].texCoord = _texCoords[0];
        m_Vertices[1].texCoord = _texCoords[1];
        m_Vertices[2].texCoord = _texCoords[2];
        m_Vertices[3].texCoord = _texCoords[3];
    }
}