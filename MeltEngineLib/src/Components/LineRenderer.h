#ifndef LINERENDERER_H
#define LINERENDERER_H

#include "Core.h"
#include "Mesh.h"
#include "Vertex.h"

namespace MELT
{
    class LineRenderer
    {
    public:
        MeshData* mesh_data;

        LineRenderer () = default;
        ~LineRenderer()
        {
            if (m_vao) glDeleteVertexArrays(1, &m_vao);
            if (m_vbo) glDeleteBuffers     (1, &m_vbo);
            if (m_ebo) glDeleteBuffers     (1, &m_ebo);
        }

        void set_mesh_data(MeshData* _mesh_data){
           mesh_data = _mesh_data;
        }

        void set_buffer_data()
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

        void draw()
        {
            glBindVertexArray(m_vao);
            glDrawElements(GL_LINES, (GLsizei)mesh_data->mesh->index_buffer.size(), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
    private:
        unsigned int m_vao, m_vbo, m_ebo;
    };
}

#endif //LINERENDERER_H
