#include "Camera.h"

namespace MELT
{
    Camera::Camera():
    UseOrthographic(true),
    Position(glm::vec3(0.0f, 0.0f, 3.0f)),
    Target  (glm::vec3(0.0f, 0.0f, 0.0f)),
    Up      (glm::vec3(0.0f, 1.0f, 0.0f)),
    NearPlane(0.1f),
    FarPlane(100.0f),
    OrthographicSize(20.0f)
    {

    }

    Camera::~Camera()
    {

    }

    float Camera::HalfScreenWidht() const
    {
        return ScreenSize.x / 2.0f;
    }

    float Camera::HalfScreenHeight() const
    {
        return ScreenSize.y / 2.0f;
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(Position, Target, Up);
    }

    glm::mat4 Camera::GetOrthographicProjectionMatrix() const
    {
        return glm::ortho(-ScreenSize.x/2, ScreenSize.x/2, -ScreenSize.y/2, ScreenSize.y/2, NearPlane, FarPlane);
    }

    void Camera::UpdateScreenSizeWithOrthographicSize(float _screenRatio)
    {
        ScreenRatio = _screenRatio;
        ScreenSize.y = OrthographicSize * 2;
        ScreenSize.x = _screenRatio * ScreenSize.y;
    }
}