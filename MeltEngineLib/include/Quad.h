#pragma once
#include <iostream>
#include <array>
#include <GL/glew.h>
#include "Vertex.h"

namespace MELT
{
    class Quad
    {
    public:
        //Test
        bool IsSelected = false;
        glm::vec2 WorldPosition = { 0.0f, 0.0f };
        glm::vec2 Size          = { 25.0f, 25.0f };


        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        GLuint FBO;
        GLuint RBO;

        GLuint TextureID;

        Quad();
        ~Quad();

        void Draw();
        void DrawFrameBuffer();
        void RescaleFrameBuffer(const GLsizei& _w, const GLsizei& _h);

    private:

        std::array<Vertex, 4> m_Vertices;
        std::array<GLuint, 6> m_Indices;
    };
}


