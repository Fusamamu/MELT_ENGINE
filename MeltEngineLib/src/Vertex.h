#pragma once
#include "Core.h"

namespace MELT
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;

        Vertex();
        ~Vertex();
    };

    struct Vertex_1P1C1T1N
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;
        glm::vec3 normal;

        Vertex_1P1C1T1N(){ }
        ~Vertex_1P1C1T1N(){ }
    };
}