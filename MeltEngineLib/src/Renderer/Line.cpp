#include "Line.h"

namespace MELT
{
    Line::Line()
    {
        m_Vertices[0].x = 0.0f;
        m_Vertices[0].y = 0.0f;
        m_Vertices[1].x = 10.0f;
        m_Vertices[1].y = 10.0f;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)nullptr);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    Line::~Line()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers     (1, &VBO);
    }

    void Line::Draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    }
}