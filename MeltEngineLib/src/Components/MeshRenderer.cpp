#include "MeshRenderer.h"

namespace MELT
{
    void MeshRenderer::set_mesh_data(MeshData* _mesh_data)
    {
        if (_mesh_data == mesh_data) return;
        destroy();
        mesh_data = _mesh_data;
    }

    void MeshRenderer::set_mesh(Mesh* _mesh)
    {
        if (_mesh == mesh) return;
        destroy();
        mesh = _mesh;
    }

    void MeshRenderer::set_buffer_data(Mesh* _mesh)
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER        , m_vbo);
        glBufferData(GL_ARRAY_BUFFER        , _mesh->get_vertex_buffer_size(), _mesh->vertex_buffer.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _mesh->get_index_buffer_size() , _mesh->index_buffer.data() , GL_STATIC_DRAW);

        uint32_t _attribIndex = 0;
        for (const auto& _element : _mesh->layout.elements)
        {
            glEnableVertexAttribArray(_attribIndex);
            glVertexAttribPointer
            (
                _attribIndex,
                _element.components,
                _element.glType,
                _element.normalized ? GL_TRUE : GL_FALSE,
                _mesh->layout.stride,
                (void*)(uintptr_t)_element.offset
            );
            _attribIndex++;
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void MeshRenderer::set_buffer_data()
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

        // Setup vertex attributes from layout
        uint32_t _attribIndex = 0;
        for (const auto& _element : _mesh->layout.elements)
        {
            glEnableVertexAttribArray(_attribIndex);
            glVertexAttribPointer
            (
                _attribIndex,
                _element.components,
                _element.glType,
                _element.normalized ? GL_TRUE : GL_FALSE,
                _mesh->layout.stride,
                (void*)(uintptr_t)_element.offset
            );
            _attribIndex++;
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void MeshRenderer::draw() const
    {
        glBindVertexArray(m_vao);
        if (mesh_data)
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh_data->mesh->index_buffer.size(), GL_UNSIGNED_INT, nullptr);
        if (mesh)
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh->index_buffer.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void MeshRenderer::draw_polygon()
    {
        glBindVertexArray(m_vao);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh_data->mesh->index_buffer.size(), GL_UNSIGNED_INT, nullptr);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glBindVertexArray(0);
    }

    void MeshRenderer::destroy()
    {
        if (m_vao) glDeleteVertexArrays(1, &m_vao); m_vao = 0;
        if (m_vbo) glDeleteBuffers     (1, &m_vbo); m_vbo = 0;
        if (m_ebo) glDeleteBuffers     (1, &m_ebo); m_ebo = 0;
    }
}
