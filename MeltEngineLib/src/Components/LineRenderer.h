#ifndef LINE_RENDERER_H
#define LINE_RENDERER_H

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
        ~LineRenderer();

        void set_mesh_data(MeshData* _mesh_data);
        void set_line_positions(M_VEC3 _origin, M_VEC3 _target);

        void set_buffer_data();
        void set_line_buffer_data();

        void draw();
        void draw_dynamic();
    private:
        unsigned int m_vao, m_vbo, m_ebo;

        std::array<M_VEC3, 2> m_line_positions;
    };
}

#endif //LINERENDERER_H
