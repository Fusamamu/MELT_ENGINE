#include "Camera.h"

namespace MELT
{
    Camera::Camera():
    use_orthographic(true),
    position(glm::vec3(3.0f, 3.0f, 3.0f)),
    Target  (glm::vec3(0.0f, 0.0f, 0.0f)),
    Up      (glm::vec3(0.0f, 1.0f, 0.0f)),
    near_plane(-100.0f),
    far_plane(1000.0f),
    orthographic_size(10.0f)
    {

    }

    Camera::~Camera()
    {

    }

    float Camera::HalfScreenWidth() const
    {
        return ScreenSize.x / 2.0f;
    }

    float Camera::HalfScreenHeight() const
    {
        return ScreenSize.y / 2.0f;
    }

    glm::mat4 Camera::get_view_matrix() const
    {
        return glm::lookAt(position, Target, Up);
    }

    glm::mat4 Camera::get_orthographic_projection_matrix() const
    {
        return glm::ortho(-ScreenSize.x/2, ScreenSize.x/2, -ScreenSize.y/2, ScreenSize.y/2, near_plane, far_plane);
    }

    void Camera::update_screen_size_with_orthographic_size(float _screenRatio)
    {
        screen_ratio = _screenRatio;
        ScreenSize.y = orthographic_size * 2;
        ScreenSize.x = _screenRatio * ScreenSize.y;
    }

    std::array<glm::vec3, 8> Camera::get_frustum_corners(
        const glm::vec3& _eye,
        const glm::vec3& _forward,
        const glm::vec3& _up,
        const glm::vec3& _right,
        float _fov_y_rad,
        float _aspect,
        float _near_dist,
        float _far_dist)
    {
        std::array<glm::vec3, 8> _corners;

        float nearHeight = 2.0f * tan(_fov_y_rad / 2.0f) * _near_dist;
        float nearWidth  = nearHeight * _aspect;
        float farHeight  = 2.0f * tan(_fov_y_rad / 2.0f) * _far_dist;
        float farWidth   = farHeight * _aspect;

        glm::vec3 nearCenter = _eye + _forward * _near_dist;
        glm::vec3 farCenter  = _eye + _forward * _far_dist;

        // Near plane corners
        _corners[0] = nearCenter + (_up * (nearHeight / 2.0f)) - (_right * (nearWidth / 2.0f)); // top-left
        _corners[1] = nearCenter + (_up * (nearHeight / 2.0f)) + (_right * (nearWidth / 2.0f)); // top-right
        _corners[2] = nearCenter - (_up * (nearHeight / 2.0f)) - (_right * (nearWidth / 2.0f)); // bottom-left
        _corners[3] = nearCenter - (_up * (nearHeight / 2.0f)) + (_right * (nearWidth / 2.0f)); // bottom-right

        // Far plane corners
        _corners[4] = farCenter + (_up * (farHeight / 2.0f)) - (_right * (farWidth / 2.0f)); // top-left
        _corners[5] = farCenter + (_up * (farHeight / 2.0f)) + (_right * (farWidth / 2.0f)); // top-right
        _corners[6] = farCenter - (_up * (farHeight / 2.0f)) - (_right * (farWidth / 2.0f)); // bottom-left
        _corners[7] = farCenter - (_up * (farHeight / 2.0f)) + (_right * (farWidth / 2.0f)); // bottom-right

        return _corners;
    }

    std::array<glm::vec3, 8> Camera::get_orthographic_frustum_corners() const
    {
        std::array<glm::vec3, 8> corners;

        float halfHeight = orthographic_size * 0.5f;
        float halfWidth  = halfHeight * screen_ratio;

        // halfHeight = 10.0f;
        // halfWidth  = 20.0f;

        float nearZ = -near_plane;
        float farZ  = -far_plane;

        // Frustum corners in camera/view space
        glm::vec3 viewSpaceCorners[8] = {
            { -halfWidth, -halfHeight, nearZ }, // 0
            {  halfWidth, -halfHeight, nearZ }, // 1
            {  halfWidth,  halfHeight, nearZ }, // 2
            { -halfWidth,  halfHeight, nearZ }, // 3

            { -halfWidth, -halfHeight, farZ },  // 4
            {  halfWidth, -halfHeight, farZ },  // 5
            {  halfWidth,  halfHeight, farZ },  // 6
            { -halfWidth,  halfHeight, farZ },  // 7
        };

        // Inverse view matrix to convert to world space
        glm::mat4 invView = glm::inverse(get_view_matrix());

        for (int i = 0; i < 8; ++i) {
            glm::vec4 world = invView * glm::vec4(viewSpaceCorners[i], 1.0f);
            corners[i] = glm::vec3(world);
        }

        return corners;
    }

}