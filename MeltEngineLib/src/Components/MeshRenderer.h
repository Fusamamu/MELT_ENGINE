#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Core.h"
#include "AssetRegistry.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Material.h"

namespace MELT
{
    class MeshRenderer
    {
    public:
        AssetHandle<Mesh>              mesh_handle;
        AssetHandle<GRAPHIC::Material> mesh_material;

        Mesh*     mesh;
        MeshData* mesh_data;

        MeshRenderer () = default;
        ~MeshRenderer() = default;

        void set_mesh(Mesh* _mesh);
        void set_mesh_data(MeshData* _mesh_data);
        void set_buffer_data();
        void set_buffer_data(Mesh* _mesh);

        void draw() const;
        void draw_polygon();

        void destroy();
    private:
        unsigned int m_vao, m_vbo, m_ebo;
    };
}

#endif
