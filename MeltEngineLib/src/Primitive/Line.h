#ifndef LINE_H
#define LINE_H

#include "Core.h"
#include "Mesh.h"
#include "Vertex.h"

namespace MELT
{
    class Line
    {
    public:
        Line(const glm::vec3& start, const glm::vec3& end);
        ~Line() = default;

        Mesh get_mesh() const;

    private:
        std::vector<Vertex_P> m_vertices;
        std::vector<GLuint>   m_indices;
    };
}

#endif // LINE_H
