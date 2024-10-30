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

        float NearPlane;
        float FarPlane;

        /** @brief Screen size of a window used to calculate projection matrix*/
        glm::vec2 ScreenSize;

        float Zoom;
        float ScreenRatio;
        float OrthographicSize;

        Camera();
        ~Camera();

        float HalfScreenWidht() const;
        float HalfScreenHeight() const;

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetOrthographicProjectionMatrix() const;
        void UpdateScreenSizeWithOrthographicSize(float _screenRatio);
    };
}