#include "Plane.h"

namespace MELT
{
    Plane::Plane(uint32_t _x_segments, uint32_t _z_segments, float _width, float _depth)
    {
        generate(_x_segments, _z_segments, _width, _depth);
    }

    void Plane::generate(uint32_t _x_segments, uint32_t _z_segments, float _width, float _depth)
    {
        m_vertices.clear();
        m_indices .clear();

        float halfWidth = _width * 0.5f;
        float halfDepth = _depth * 0.5f;

        for (uint32_t z = 0; z <= _z_segments; ++z)
        {
            float _z_pos = ((float)z / _z_segments) * _depth - halfDepth;
            float _t     = 1.0f - ((float)z / _z_segments);

            for (uint32_t x = 0; x <= _x_segments; ++x)
            {
                float xPos = (float)x / _x_segments * _width - halfWidth;
                float _s   = (float)x / _x_segments;

                Vertex_PCTN _vertex;
                _vertex.position = glm::vec3(xPos, 0.0f, _z_pos);
                _vertex.color    = glm::vec3(1.0f, 1.0f, 1.0f);
                _vertex.texCoord = glm::vec2(_s, _t);
                _vertex.normal   = glm::vec3(0.0f, 1.0f, 0.0f);

                m_vertices.push_back(_vertex);
            }
        }

        for (uint32_t z = 0; z < _z_segments; ++z)
        {
            for (uint32_t x = 0; x < _x_segments; ++x)
            {
                uint32_t start = z * (_x_segments + 1) + x;

                uint32_t topLeft     = start;
                uint32_t topRight    = start + 1;
                uint32_t bottomLeft  = start + (_x_segments + 1);
                uint32_t bottomRight = bottomLeft + 1;

                m_indices.push_back(topLeft    );
                m_indices.push_back(bottomLeft );
                m_indices.push_back(bottomRight);
                m_indices.push_back(bottomRight);
                m_indices.push_back(topRight   );
                m_indices.push_back(topLeft    );
            }
        }
    }

    Mesh Plane::get_mesh() const
    {
        Mesh _mesh;

        _mesh.vertex_buffer.resize(m_vertices.size() * sizeof(Vertex_PCTN));
        _mesh.index_buffer .resize(m_indices .size() * sizeof(unsigned int));

        memcpy(_mesh.vertex_buffer.data(), m_vertices.data(), _mesh.vertex_buffer.size());
        memcpy(_mesh.index_buffer .data(), m_indices .data(), _mesh.index_buffer .size());

        _mesh.layout = createLayout_PCTN();

        return _mesh;
    }
}
