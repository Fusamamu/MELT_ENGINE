#include "Camera.h"

namespace MELT
{
    Camera::Camera():
    Position(glm::vec3(0.0f, 0.0f, 3.0f)),
    Target  (glm::vec3(0.0f, 0.0f, 0.0f)),
    Up      (glm::vec3(0.0f, 1.0f, 0.0f)),
    Zoom(1.0f)
    {

    }
}