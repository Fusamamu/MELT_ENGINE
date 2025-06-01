#ifndef GIZMOSRENDERER_H
#define GIZMOSRENDERER_H

#include "Core.h"

namespace MELT
{
    class GizmosRenderer
    {
    public:
        void init()
        {
            glGenVertexArrays(1, &m_vao);
            glGenBuffers(1, &m_vbo);
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
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);

            glBindVertexArray(0);
        }

        void draw(float _thickness = 2.0f)
        {
            glLineWidth(_thickness);
            glBindVertexArray(m_vao);
            glDrawArrays(GL_LINES, 0, 24);
            glBindVertexArray(0);
            glLineWidth(1.0f);
        }
    private:
        GLuint m_vao = 0;
        GLuint m_vbo = 0;
    };

}

#endif //GIZMOSRENDERER_H
