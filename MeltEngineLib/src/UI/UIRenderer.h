#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include "Core.h"

namespace MELT::UI
{
    class UIRenderer
    {
    public:
        UIRenderer () = default;
        ~UIRenderer()
        {
            glDeleteVertexArrays(1, &m_vao);
            glDeleteBuffers(1, &m_vbo);
            glDeleteBuffers(1, &m_ebo);
        }

        void init()
        {
            // pos      // uv      // color
            float quadVertices[] = {
                // x     y     u     v     r     g     b     a
                0.0f, 0.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, // bottom-left
                1.0f, 0.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // bottom-right
                1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f, // top-right
                0.0f, 1.0f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f  // top-left
            };

            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };

            glGenVertexArrays(1, &m_vao);
            glGenBuffers     (1, &m_vbo);
            glGenBuffers     (1, &m_ebo);

            glBindVertexArray(m_vao);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
        }

        void draw() const
        {
            glBindVertexArray(m_vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    private:
        unsigned int m_vao = 0, m_vbo = 0, m_ebo = 0;
    };
}

#endif
