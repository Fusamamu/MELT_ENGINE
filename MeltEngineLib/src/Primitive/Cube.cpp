#include "Cube.h"

namespace MELT
{
    Cube::Cube()
    {

        float vertices[] = {
                // positions           // colors           // texture coords // normals
                -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,       0.0f, 0.0f, -1.0f, // Back face
                0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,       0.0f, 0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,       0.0f, 0.0f, -1.0f,
                -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,       0.0f, 0.0f, -1.0f,

                -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,       0.0f, 0.0f, 1.0f, // Front face
                0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 0.0f,       0.0f, 0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,       0.0f, 0.0f, 1.0f,

                -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,      -1.0f, 0.0f, 0.0f, // Left face
                -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,      -1.0f, 0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f,      -1.0f, 0.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,      -1.0f, 0.0f, 0.0f,

                0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,       1.0f, 0.0f, 0.0f, // Right face
                0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,       1.0f, 0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f,       1.0f, 0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,       1.0f, 0.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,       0.0f, -1.0f, 0.0f, // Bottom face
                0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,       0.0f, -1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f,       0.0f, -1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,       0.0f, -1.0f, 0.0f,

                -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,       0.0f, 1.0f, 0.0f, // Top face
                0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,       0.0f, 1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f,       0.0f, 1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,       0.0f, 1.0f, 0.0f
        };


        m_Vertices[0] .position = glm::vec3( -0.5f, -0.5f, -0.5f);
        m_Vertices[1] .position = glm::vec3( 0.5f, -0.5f, -0.5f );
        m_Vertices[2] .position = glm::vec3( 0.5f,  0.5f, -0.5f );
        m_Vertices[3] .position = glm::vec3( -0.5f,  0.5f, -0.5f);
        m_Vertices[4] .position = glm::vec3( -0.5f, -0.5f,  0.5f);
        m_Vertices[5] .position = glm::vec3( 0.5f, -0.5f,  0.5f );
        m_Vertices[6] .position = glm::vec3( 0.5f,  0.5f,  0.5f );
        m_Vertices[7] .position = glm::vec3( -0.5f,  0.5f,  0.5f);
        m_Vertices[8] .position = glm::vec3( -0.5f, -0.5f, -0.5f);
        m_Vertices[9] .position = glm::vec3( -0.5f,  0.5f, -0.5f);
        m_Vertices[10].position = glm::vec3( -0.5f,  0.5f,  0.5f);
        m_Vertices[11].position = glm::vec3( -0.5f, -0.5f,  0.5f);
        m_Vertices[12].position = glm::vec3( 0.5f, -0.5f, -0.5f );
        m_Vertices[13].position = glm::vec3( 0.5f,  0.5f, -0.5f );
        m_Vertices[14].position = glm::vec3( 0.5f,  0.5f,  0.5f );
        m_Vertices[15].position = glm::vec3( 0.5f, -0.5f,  0.5f );
        m_Vertices[16].position = glm::vec3( -0.5f, -0.5f, -0.5f);
        m_Vertices[17].position = glm::vec3( 0.5f, -0.5f, -0.5f );
        m_Vertices[18].position = glm::vec3( 0.5f, -0.5f,  0.5f);
        m_Vertices[19].position = glm::vec3( -0.5f, -0.5f,  0.5f);
        m_Vertices[20].position = glm::vec3( -0.5f,  0.5f, -0.5f);
        m_Vertices[21].position = glm::vec3( 0.5f,  0.5f, -0.5f );
        m_Vertices[22].position = glm::vec3( 0.5f,  0.5f,  0.5f );
        m_Vertices[23].position = glm::vec3( -0.5f,  0.5f,  0.5f);

        m_Vertices[0] .color = glm::vec3( 1.0f, 0.0f, 0.0f);
        m_Vertices[1] .color = glm::vec3(0.0f, 1.0f, 0.0f);
        m_Vertices[2] .color = glm::vec3(0.0f, 0.0f, 1.0f);
        m_Vertices[3] .color = glm::vec3( 1.0f, 1.0f, 0.0f);
        m_Vertices[4] .color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_Vertices[5] .color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_Vertices[6] .color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Vertices[7] .color = glm::vec3( 0.0f, 0.0f, 0.0f);
        m_Vertices[8] .color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_Vertices[9] .color = glm::vec3( 1.0f, 1.0f, 0.0f);
        m_Vertices[10].color = glm::vec3( 0.0f, 1.0f, 1.0f);
        m_Vertices[11].color = glm::vec3( 0.0f, 0.0f, 0.0f);
        m_Vertices[12].color = glm::vec3(1.0f, 0.0f, 1.0f);
        m_Vertices[13].color = glm::vec3(1.0f, 1.0f, 0.0f);
        m_Vertices[14].color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_Vertices[15].color = glm::vec3(0.0f, 0.0f, 0.0f);
        m_Vertices[16].color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_Vertices[17].color = glm::vec3(1.0f, 1.0f, 0.0f);
        m_Vertices[18].color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_Vertices[19].color = glm::vec3( 0.0f, 0.0f, 0.0f);
        m_Vertices[20].color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_Vertices[21].color = glm::vec3(1.0f, 1.0f, 0.0f);
        m_Vertices[22].color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_Vertices[23].color = glm::vec3( 0.0f, 0.0f, 0.0f);

        m_Vertices[0] .texCoord = glm::vec2( 0.0f, 0.0f);
        m_Vertices[1] .texCoord = glm::vec2(1.0f, 0.0f);
        m_Vertices[2] .texCoord = glm::vec2(1.0f, 1.0f);
        m_Vertices[3] .texCoord = glm::vec2( 0.0f, 1.0f);
        m_Vertices[4] .texCoord = glm::vec2( 0.0f, 0.0f);
        m_Vertices[5] .texCoord = glm::vec2(1.0f, 0.0f);
        m_Vertices[6] .texCoord = glm::vec2(1.0f, 1.0f);
        m_Vertices[7] .texCoord = glm::vec2( 0.0f, 1.0f);
        m_Vertices[8] .texCoord = glm::vec2( 0.0f, 0.0f);
        m_Vertices[9] .texCoord = glm::vec2( 1.0f, 0.0f);
        m_Vertices[10].texCoord = glm::vec2( 1.0f, 1.0f);
        m_Vertices[11].texCoord = glm::vec2( 0.0f, 1.0f);
        m_Vertices[12].texCoord = glm::vec2(0.0f, 0.0f);
        m_Vertices[13].texCoord = glm::vec2(1.0f, 0.0f);
        m_Vertices[14].texCoord = glm::vec2(1.0f, 1.0f);
        m_Vertices[15].texCoord = glm::vec2(0.0f, 1.0f);
        m_Vertices[16].texCoord = glm::vec2( 0.0f, 0.0f);
        m_Vertices[17].texCoord = glm::vec2(1.0f, 0.0f);
        m_Vertices[18].texCoord = glm::vec2(1.0f, 1.0f);
        m_Vertices[19].texCoord = glm::vec2( 0.0f, 1.0f);
        m_Vertices[20].texCoord = glm::vec2( 0.0f, 0.0f);
        m_Vertices[21].texCoord = glm::vec2(1.0f, 0.0f);
        m_Vertices[22].texCoord = glm::vec2(1.0f, 1.0f);
        m_Vertices[23].texCoord = glm::vec2( 0.0f, 1.0f);

        m_Vertices[0] .normal = glm::vec3( 0.0f, 0.0f, -1.0f);
        m_Vertices[1] .normal = glm::vec3(0.0f, 0.0f, -1.0f);
        m_Vertices[2] .normal = glm::vec3(0.0f, 0.0f, -1.0f);
        m_Vertices[3] .normal = glm::vec3( 0.0f, 0.0f, -1.0f);
        m_Vertices[4] .normal = glm::vec3( 0.0f, 0.0f, 1.0f);
        m_Vertices[5] .normal = glm::vec3(0.0f, 0.0f, 1.0f);
        m_Vertices[6] .normal = glm::vec3(0.0f, 0.0f, 1.0f);
        m_Vertices[7] .normal = glm::vec3( 0.0f, 0.0f, 1.0f);
        m_Vertices[8] .normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_Vertices[9] .normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_Vertices[10].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_Vertices[11].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_Vertices[12].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_Vertices[13].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_Vertices[14].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_Vertices[15].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_Vertices[16].normal = glm::vec3( 0.0f, -1.0f, 0.0f);
        m_Vertices[17].normal = glm::vec3(0.0f, -1.0f, 0.0f);
        m_Vertices[18].normal = glm::vec3(0.0f, -1.0f, 0.0f);
        m_Vertices[19].normal = glm::vec3( 0.0f, -1.0f, 0.0f);
        m_Vertices[20].normal = glm::vec3( 0.0f, 1.0f, 0.0f);
        m_Vertices[21].normal = glm::vec3(0.0f, 1.0f, 0.0f);
        m_Vertices[22].normal = glm::vec3(0.0f, 1.0f, 0.0f);
        m_Vertices[23].normal = glm::vec3( 0.0f, 1.0f, 0.0f);


        m_Indices = {
                // Back face
                0, 1, 2,
                2, 3, 0,
                // Front face
                4, 5, 6,
                6, 7, 4,
                // Left face
                8, 9, 10,
                10, 11, 8,
                // Right face
                12, 13, 14,
                14, 15, 12,
                // Bottom face
                16, 17, 18,
                18, 19, 16,
                // Top face
                20, 21, 22,
                22, 23, 20
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)(offsetof(Vertex_1P1C1T1N, position)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)(offsetof(Vertex_1P1C1T1N, color)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)(offsetof(Vertex_1P1C1T1N, texCoord)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    Cube::~Cube()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Cube::Draw() const
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}