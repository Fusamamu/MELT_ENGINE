#include "Light.h"

namespace MELT
{
    glm::mat4 Light::get_view()
    {
        return glm::lookAt(position, position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 Light::get_view(M_VEC3 _light_pos)
    {
        M_VEC3 _dir = target - _light_pos;
        _dir = glm::normalize(_dir);
        return glm::lookAt(_light_pos, _light_pos + glm::normalize(_dir), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 Light::get_projection()
    {
        return glm::ortho(-ortho_size, ortho_size, -ortho_size, ortho_size, near_plane, far_plane);
    }
}
