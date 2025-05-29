#pragma once
#include "Core.h"

namespace MELT
{
    struct Camera
    {
        bool UseOrthographic;

        glm::vec3 Position;
        glm::vec3 Target;
        glm::vec3 Up;

        float NearPlane;
        float FarPlane;

        /** @brief Screen size of a window used to calculate projection matrix*/
        glm::vec2 ScreenSize;
        glm::vec2 WindowSize;

        float Zoom;
        float ScreenRatio;
        float OrthographicSize;

        Camera();
        ~Camera();

        [[nodiscard]] float HalfScreenWidth () const;
        [[nodiscard]] float HalfScreenHeight() const;

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetOrthographicProjectionMatrix() const;

        void UpdateScreenSizeWithOrthographicSize(float _screenRatio);
    };
}