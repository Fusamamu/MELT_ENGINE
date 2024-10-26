#include "Quad.h"

namespace MELT
{
    Quad::Quad()
    {
        m_Vertices[0].position = glm::vec3( 1.0f,  1.0f, 0.0f);
        m_Vertices[1].position = glm::vec3( 1.0f, -1.0f, 0.0f);
        m_Vertices[2].position = glm::vec3(-1.0f, -1.0f, 0.0f);
        m_Vertices[3].position = glm::vec3(-1.0f,  1.0f, 0.0f);

        m_Vertices[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Vertices[1].color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Vertices[2].color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Vertices[3].color = glm::vec3(1.0f, 1.0f, 1.0f);

        m_Vertices[0].texCoord = glm::vec2(1.0f, 1.0f);
        m_Vertices[1].texCoord = glm::vec2(1.0f, 0.0f);
        m_Vertices[2].texCoord = glm::vec2(0.0f, 0.0f);
        m_Vertices[3].texCoord = glm::vec2(0.0f, 1.0f);

        m_Indices = {
                1, 3, 0,
                1, 2, 3
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoord)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    Quad::~Quad()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Quad::Draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void Quad::SetTexCoords(std::array<glm::vec2, 4> _texCoords)
    {
        m_Vertices[0].texCoord = _texCoords[0];
        m_Vertices[1].texCoord = _texCoords[1];
        m_Vertices[2].texCoord = _texCoords[2];
        m_Vertices[3].texCoord = _texCoords[3];

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices.data(), GL_STATIC_DRAW);
        glBindVertexArray(0);
    }
}