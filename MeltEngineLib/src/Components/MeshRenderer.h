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

            auto m_mesh = mesh_data->mesh;

            glBindBuffer(GL_ARRAY_BUFFER        , m_vbo);
            glBufferData(GL_ARRAY_BUFFER        , m_mesh->vertices.size() * sizeof(Vertex_1P1C1T1N), m_mesh->vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh->indices.size() * sizeof(unsigned int)    , m_mesh->indices.data() , GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)offsetof(Vertex_1P1C1T1N, position));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)offsetof(Vertex_1P1C1T1N, color));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)offsetof(Vertex_1P1C1T1N, texCoord));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void draw()
        {
            glBindVertexArray(m_vao);
            glDrawElements(GL_TRIANGLES, mesh_data->mesh->indices.size() * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }

        void drawsds()
        {
            glBindVertexArray(m_vao);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, mesh_data->mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            glBindVertexArray(0);
        }
    private:
        unsigned int m_vao, m_vbo, m_ebo;
    };
}

#endif
