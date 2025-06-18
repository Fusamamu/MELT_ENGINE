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

        Transform(): position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f) {}

        [[nodiscard]] glm::mat4 get_transform_matrix() const;
    };
}

#endif