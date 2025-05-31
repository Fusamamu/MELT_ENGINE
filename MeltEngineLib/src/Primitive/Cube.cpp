#include "Cube.h"

namespace MELT
{
    Cube::Cube()
    {
        m_vertices[0] .position = glm::vec3( -0.5f, -0.5f, -0.5f);
        m_vertices[1] .position = glm::vec3( 0.5f, -0.5f, -0.5f );
        m_vertices[2] .position = glm::vec3( 0.5f,  0.5f, -0.5f );
        m_vertices[3] .position = glm::vec3( -0.5f,  0.5f, -0.5f);
        m_vertices[4] .position = glm::vec3( -0.5f, -0.5f,  0.5f);
        m_vertices[5] .position = glm::vec3( 0.5f, -0.5f,  0.5f );
        m_vertices[6] .position = glm::vec3( 0.5f,  0.5f,  0.5f );
        m_vertices[7] .position = glm::vec3( -0.5f,  0.5f,  0.5f);
        m_vertices[8] .position = glm::vec3( -0.5f, -0.5f, -0.5f);
        m_vertices[9] .position = glm::vec3( -0.5f,  0.5f, -0.5f);
        m_vertices[10].position = glm::vec3( -0.5f,  0.5f,  0.5f);
        m_vertices[11].position = glm::vec3( -0.5f, -0.5f,  0.5f);
        m_vertices[12].position = glm::vec3( 0.5f, -0.5f, -0.5f );
        m_vertices[13].position = glm::vec3( 0.5f,  0.5f, -0.5f );
        m_vertices[14].position = glm::vec3( 0.5f,  0.5f,  0.5f );
        m_vertices[15].position = glm::vec3( 0.5f, -0.5f,  0.5f );
        m_vertices[16].position = glm::vec3( -0.5f, -0.5f, -0.5f);
        m_vertices[17].position = glm::vec3( 0.5f, -0.5f, -0.5f );
        m_vertices[18].position = glm::vec3( 0.5f, -0.5f,  0.5f);
        m_vertices[19].position = glm::vec3( -0.5f, -0.5f,  0.5f);
        m_vertices[20].position = glm::vec3( -0.5f,  0.5f, -0.5f);
        m_vertices[21].position = glm::vec3( 0.5f,  0.5f, -0.5f );
        m_vertices[22].position = glm::vec3( 0.5f,  0.5f,  0.5f );
        m_vertices[23].position = glm::vec3( -0.5f,  0.5f,  0.5f);

        m_vertices[0] .color = glm::vec3( 1.0f, 0.0f, 0.0f);
        m_vertices[1] .color = glm::vec3(0.0f, 1.0f, 0.0f);
        m_vertices[2] .color = glm::vec3(0.0f, 0.0f, 1.0f);
        m_vertices[3] .color = glm::vec3( 1.0f, 1.0f, 0.0f);
        m_vertices[4] .color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_vertices[5] .color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_vertices[6] .color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_vertices[7] .color = glm::vec3( 0.0f, 0.0f, 0.0f);
        m_vertices[8] .color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_vertices[9] .color = glm::vec3( 1.0f, 1.0f, 0.0f);
        m_vertices[10].color = glm::vec3( 0.0f, 1.0f, 1.0f);
        m_vertices[11].color = glm::vec3( 0.0f, 0.0f, 0.0f);
        m_vertices[12].color = glm::vec3(1.0f, 0.0f, 1.0f);
        m_vertices[13].color = glm::vec3(1.0f, 1.0f, 0.0f);
        m_vertices[14].color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_vertices[15].color = glm::vec3(0.0f, 0.0f, 0.0f);
        m_vertices[16].color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_vertices[17].color = glm::vec3(1.0f, 1.0f, 0.0f);
        m_vertices[18].color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_vertices[19].color = glm::vec3( 0.0f, 0.0f, 0.0f);
        m_vertices[20].color = glm::vec3( 1.0f, 0.0f, 1.0f);
        m_vertices[21].color = glm::vec3(1.0f, 1.0f, 0.0f);
        m_vertices[22].color = glm::vec3(0.0f, 1.0f, 1.0f);
        m_vertices[23].color = glm::vec3( 0.0f, 0.0f, 0.0f);

        m_vertices[0] .texCoord = glm::vec2( 0.0f, 0.0f);
        m_vertices[1] .texCoord = glm::vec2(1.0f, 0.0f);
        m_vertices[2] .texCoord = glm::vec2(1.0f, 1.0f);
        m_vertices[3] .texCoord = glm::vec2( 0.0f, 1.0f);
        m_vertices[4] .texCoord = glm::vec2( 0.0f, 0.0f);
        m_vertices[5] .texCoord = glm::vec2(1.0f, 0.0f);
        m_vertices[6] .texCoord = glm::vec2(1.0f, 1.0f);
        m_vertices[7] .texCoord = glm::vec2( 0.0f, 1.0f);
        m_vertices[8] .texCoord = glm::vec2( 0.0f, 0.0f);
        m_vertices[9] .texCoord = glm::vec2( 1.0f, 0.0f);
        m_vertices[10].texCoord = glm::vec2( 1.0f, 1.0f);
        m_vertices[11].texCoord = glm::vec2( 0.0f, 1.0f);
        m_vertices[12].texCoord = glm::vec2(0.0f, 0.0f);
        m_vertices[13].texCoord = glm::vec2(1.0f, 0.0f);
        m_vertices[14].texCoord = glm::vec2(1.0f, 1.0f);
        m_vertices[15].texCoord = glm::vec2(0.0f, 1.0f);
        m_vertices[16].texCoord = glm::vec2( 0.0f, 0.0f);
        m_vertices[17].texCoord = glm::vec2(1.0f, 0.0f);
        m_vertices[18].texCoord = glm::vec2(1.0f, 1.0f);
        m_vertices[19].texCoord = glm::vec2( 0.0f, 1.0f);
        m_vertices[20].texCoord = glm::vec2( 0.0f, 0.0f);
        m_vertices[21].texCoord = glm::vec2(1.0f, 0.0f);
        m_vertices[22].texCoord = glm::vec2(1.0f, 1.0f);
        m_vertices[23].texCoord = glm::vec2( 0.0f, 1.0f);

        m_vertices[0] .normal = glm::vec3( 0.0f, 0.0f, -1.0f);
        m_vertices[1] .normal = glm::vec3(0.0f, 0.0f, -1.0f);
        m_vertices[2] .normal = glm::vec3(0.0f, 0.0f, -1.0f);
        m_vertices[3] .normal = glm::vec3( 0.0f, 0.0f, -1.0f);
        m_vertices[4] .normal = glm::vec3( 0.0f, 0.0f, 1.0f);
        m_vertices[5] .normal = glm::vec3(0.0f, 0.0f, 1.0f);
        m_vertices[6] .normal = glm::vec3(0.0f, 0.0f, 1.0f);
        m_vertices[7] .normal = glm::vec3( 0.0f, 0.0f, 1.0f);
        m_vertices[8] .normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_vertices[9] .normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_vertices[10].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_vertices[11].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        m_vertices[12].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_vertices[13].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_vertices[14].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_vertices[15].normal = glm::vec3(1.0f, 0.0f, 0.0f);
        m_vertices[16].normal = glm::vec3( 0.0f, -1.0f, 0.0f);
        m_vertices[17].normal = glm::vec3(0.0f, -1.0f, 0.0f);
        m_vertices[18].normal = glm::vec3(0.0f, -1.0f, 0.0f);
        m_vertices[19].normal = glm::vec3( 0.0f, -1.0f, 0.0f);
        m_vertices[20].normal = glm::vec3( 0.0f, 1.0f, 0.0f);
        m_vertices[21].normal = glm::vec3(0.0f, 1.0f, 0.0f);
        m_vertices[22].normal = glm::vec3(0.0f, 1.0f, 0.0f);
        m_vertices[23].normal = glm::vec3( 0.0f, 1.0f, 0.0f);

        m_indices = {
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)(offsetof(Vertex_1P1C1T1N, position)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)(offsetof(Vertex_1P1C1T1N, color)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_1P1C1T1N), (void*)(offsetof(Vertex_1P1C1T1N, texCoord)));

        glBindVertexArray(0);
    }

    Cube::~Cube()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    Mesh Cube::get_mesh() const
    {
        std::vector<Vertex_1P1C1T1N> _vertices(m_vertices.begin(), m_vertices.end());
        std::vector<unsigned int>    _indices (m_indices .begin(), m_indices .end());
        Mesh _mesh;
        _mesh.vertices = _vertices;
        _mesh.indices  = _indices;

        return _mesh;
    }

    void Cube::Draw() const
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}