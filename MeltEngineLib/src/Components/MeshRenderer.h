#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

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

        void set_mesh_data(MeshData* _mesh_data);
        void set_buffer_data();

        void draw() const;
        void draw_polygon();

        void destroy();
    private:
        unsigned int m_vao, m_vbo, m_ebo;
    };
}

#endif
