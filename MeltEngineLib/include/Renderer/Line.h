#include <iostream>
#include <array>
#include <GL/glew.h>
#include "Vertex.h"

namespace MELT
{
    class Line
    {
    public:
        GLuint VAO;
        GLuint VBO;

        Line();
        ~Line();

        void Draw();

    private:
        std::array<glm::vec2, 2> m_Vertices;
    };
}