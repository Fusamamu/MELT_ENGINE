#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace MELT
{
    struct Transform
    {
        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale;
    };
}