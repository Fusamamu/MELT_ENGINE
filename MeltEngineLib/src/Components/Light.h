#ifndef LIGHT_H
#define LIGHT_H

#include "Core.h"

namespace MELT
{
    enum class LightType
    {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    class Light
    {
    public:
        LightType type = LightType::DIRECTIONAL;

        M_VEC3 color = M_VEC3(1.0f);
        float intensity = 1.0f;

        // For point/spot lights
        glm::vec3 position = glm::vec3(0.0f);
        float range = 10.0f;

        // For directional/spot lights
        M_VEC3 direction = M_VEC3(0.0f, -1.0f, 0.0f);

        // Spot light specific
        float innerConeAngle = glm::radians(12.5f);
        float outerConeAngle = glm::radians(17.5f);

        bool castShadows = true;

        Light() = default;
        Light(LightType _type): type(_type) {}

        glm::vec3 get_forward() const
        {
            return glm::normalize(direction);
        }

        glm::vec3 get_position() const
        {
            return position;
        }

        glm::vec3 get_color() const
        {
            return color * intensity;
        }

        // Light-space matrix for shadow mapping (only for directional light)
        glm::mat4 get_light_space_matrix(float orthoSize = 10.0f, float nearPlane = 1.0f, float farPlane = 50.0f) const
        {
            if (type != LightType::DIRECTIONAL)
                return glm::mat4(1.0f); // Identity for unsupported types

            glm::mat4 lightProjection = glm::ortho(
                -orthoSize, orthoSize,
                -orthoSize, orthoSize,
                nearPlane, farPlane
            );

            glm::mat4 lightView = glm::lookAt
            (
                position,                             // eye
                position + glm::normalize(direction), // target
                glm::vec3(0.0f, 1.0f, 0.0f)           // up
            );

            return lightProjection * lightView;
        }
    };
}

#endif // LIGHT_H
