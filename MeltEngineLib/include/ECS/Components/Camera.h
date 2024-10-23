#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace MELT
{
    struct Camera
    {
        glm::vec3 Position;
        glm::vec3 Target;
        glm::vec3 Up;

        float Zoom;

        float OrthographicSize;

        Camera();
    };
}