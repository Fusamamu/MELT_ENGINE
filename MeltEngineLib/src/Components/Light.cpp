#include "Light.h"

namespace MELT
{
    glm::mat4 Light::get_projection()
    {
        return glm::ortho(-ortho_size, ortho_size, -ortho_size, ortho_size, near_plane, far_plane);
    }

    glm::mat4 Light::get_view()
    {
        return glm::lookAt(position, position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f)); 
    }
}
