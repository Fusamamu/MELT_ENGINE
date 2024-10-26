#pragma onec
#include "Core.h"
#include <GL/glew.h>
#include "Vertex.h"

namespace MELT
{
    class Cube
    {
    public:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        Cube();
        ~Cube();

        void Draw() const;
    private:
        std::array<Vertex_1P1C1T1N, 24> m_Vertices;
        std::array<GLuint, 36> m_Indices;
    };
}