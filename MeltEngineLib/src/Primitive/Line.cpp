#include "Line.h"

namespace MELT
{
    Line::Line(const glm::vec3& start, const glm::vec3& end)
    {
        m_vertices.resize(2);
        m_vertices[0].position = start;
        m_vertices[1].position = end;

        m_indices = { 0, 1 };
    }

    Mesh Line::get_mesh() const
    {
        Mesh _mesh;

        std::cout << m_vertices.size() << std::endl;
        std::cout << sizeof(Vertex_P) << std::endl;

        _mesh.vertex_buffer.resize(m_vertices.size() * sizeof(Vertex_P));
        _mesh.index_buffer .resize(m_indices .size() * sizeof(unsigned int));

        memcpy(_mesh.vertex_buffer.data(), m_vertices.data(), _mesh.vertex_buffer.size());
        memcpy(_mesh.index_buffer .data(), m_indices .data(), _mesh.index_buffer .size());

        _mesh.layout = createLayout_P();
        return _mesh;
    }
}
