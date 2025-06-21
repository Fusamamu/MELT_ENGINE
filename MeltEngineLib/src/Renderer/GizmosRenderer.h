#ifndef GIZMOSRENDERER_H
#define GIZMOSRENDERER_H

#include <Bounds.h>

#include "Core.h"

namespace MELT
{
    enum class GizmosRenderType
    {
        NONE,
        LINE,
        SPHERE,
        CUBE,
        CAMERA_FRUSTUM
    };

    class GizmosRenderer
    {
    public:
        GizmosRenderType gizmos_type = GizmosRenderType::NONE;

        GizmosRenderer () = default;
        ~GizmosRenderer()
        {
            if (m_vao) glDeleteVertexArrays(1, &m_vao);
            if (m_vbo) glDeleteBuffers     (1, &m_vbo);
        }

        void init(const GizmosRenderType& _type)
        {
            gizmos_type = _type;
            glGenVertexArrays(1, &m_vao);
            glGenBuffers     (1, &m_vbo);
        }

        void set_bounds()
        {
            glm::vec3 _dummy(0.0f);

            glBindVertexArray(m_vao);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(_dummy), &_dummy, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, M_VEC3_SIZE, (void*)nullptr);

            glBindVertexArray(0);
        }

        void set_bounds(const AABB& _aabb)
        {
            std::array<glm::vec3, 24> _vertices = _aabb.get_mesh();

            glBindVertexArray(m_vao);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices.data(), GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, M_VEC3_SIZE, (void*)nullptr);

            glBindVertexArray(0);
        }

        void set_bounds(const glm::vec3& min, const glm::vec3& max)
        {
            glm::vec3 _vertices[] = {
                // bottom face
                {min.x, min.y, min.z}, {max.x, min.y, min.z},
                {max.x, min.y, min.z}, {max.x, min.y, max.z},
                {max.x, min.y, max.z}, {min.x, min.y, max.z},
                {min.x, min.y, max.z}, {min.x, min.y, min.z},

                // top face
                {min.x, max.y, min.z}, {max.x, max.y, min.z},
                {max.x, max.y, min.z}, {max.x, max.y, max.z},
                {max.x, max.y, max.z}, {min.x, max.y, max.z},
                {min.x, max.y, max.z}, {min.x, max.y, min.z},

                // vertical lines
                {min.x, min.y, min.z}, {min.x, max.y, min.z},
                {max.x, min.y, min.z}, {max.x, max.y, min.z},
                {max.x, min.y, max.z}, {max.x, max.y, max.z},
                {min.x, min.y, max.z}, {min.x, max.y, max.z},
            };

            glBindVertexArray(m_vao);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, M_VEC3_SIZE, (void*)nullptr);

            glBindVertexArray(0);
        }

        void draw()
        {
            glBindVertexArray(m_vao);
            glDrawArrays(GL_LINES, 0, 24);
            glBindVertexArray(0);
        }

        void draw_camera_frustum()
        {
            glBindVertexArray(m_vao);
            glDrawArrays(GL_POINTS, 0, 1); // Trigger geometry shader
            glBindVertexArray(0);
        }
    private:
        GLuint m_vao = 0;
        GLuint m_vbo = 0;
    };

}

#endif //GIZMOSRENDERER_H
