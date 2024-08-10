#pragma once
#include <GL/glew.h>

namespace MELT
{
    class Quad
    {
    public:
        Quad();
        ~Quad();

    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;


    };
}


