#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Core.h"
#include "Mesh.h"
#include "Vertex.h"

namespace MELT
{
    class MeshRenderer
    {
    public:
        MeshData* mesh_data;

        MeshRenderer () = default;
        ~MeshRenderer() = default;

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

        void draw() const
        {
            glBindVertexArray(m_vao);
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh_data->mesh->index_buffer.size(), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }

        void drawsds()
        {
            glBindVertexArray(m_vao);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh_data->mesh->index_buffer.size(), GL_UNSIGNED_INT, nullptr);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            glBindVertexArray(0);
        }
    private:
        unsigned int m_vao, m_vbo, m_ebo;
    };
}

#endif
