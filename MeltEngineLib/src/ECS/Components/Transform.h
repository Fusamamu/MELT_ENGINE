#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Core.h"

namespace MELT
{
    struct Transform
    {
        M_VEC3 position;
        M_VEC3 rotation;
        M_VEC3 scale;

        [[nodiscard]] glm::mat4 get_transform_matrix() const;
    };
}

#endif