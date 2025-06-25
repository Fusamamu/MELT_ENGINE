#include "LineRenderer.h"


namespace MELT
{
    LineRenderer::~LineRenderer()
    {
        if (m_vao) glDeleteVertexArrays(1, &m_vao);
        if (m_vbo) glDeleteBuffers     (1, &m_vbo);
        if (m_ebo) glDeleteBuffers     (1, &m_ebo);
    }

    void LineRenderer::set_mesh_data(MeshData* _mesh_data)
    {
        mesh_data = _mesh_data;
    }

    void LineRenderer::set_line_positions(M_VEC3 _origin, M_VEC3 _target)
    {
        m_line_positions[0] = _origin;
        m_line_positions[1] = _target;
    }

    void LineRenderer::set_buffer_data()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        auto _mesh = mesh_data->mesh;

        glBindBuffer(GL_ARRAY_BUFFER        , m_vbo);
        glBufferData(GL_ARRAY_BUFFER        , _mesh->get_vertex_buffer_size(), _mesh->vertex_buffer.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _mesh->get_index_buffer_size() , _mesh->index_buffer.data() , GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_P), (void*)offsetof(Vertex_P, position));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void LineRenderer::set_line_buffer_data()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_line_positions), nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, M_VEC3_SIZE, (void*)nullptr);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void LineRenderer::draw()
    {
        glBindVertexArray(m_vao);
        glDrawElements(GL_LINES, (GLsizei)mesh_data->mesh->index_buffer.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void LineRenderer::draw_dynamic()
    {
        glBindBuffer   (GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_line_positions), &m_line_positions);

        glBindVertexArray(m_vao);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    }
}

