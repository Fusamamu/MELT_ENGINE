#pragma once
#include "Core.h"

namespace MELT
{
    struct Camera
    {
        bool use_orthographic;

        glm::vec3 position;
        glm::vec3 Target;
        glm::vec3 Up;

        float near_plane;
        float far_plane;

        /** @brief Screen size of a window used to calculate projection matrix*/
        glm::vec2 ScreenSize;
        glm::vec2 WindowSize;

        float Zoom;
        float screen_ratio;
        float orthographic_size;

        Camera();
        ~Camera();

        [[nodiscard]] float HalfScreenWidth () const;
        [[nodiscard]] float HalfScreenHeight() const;

        [[nodiscard]] glm::mat4 get_view_matrix() const;
        [[nodiscard]] glm::mat4 get_orthographic_projection_matrix() const;

        void update_screen_size_with_orthographic_size(float _screenRatio);

        std::array<glm::vec3, 8> get_frustum_corners(const glm::vec3& eye, const glm::vec3& forward, const glm::vec3& up, const glm::vec3& right, float fovY_rad, float aspect, float nearDist, float farDist);

        [[nodiscard]] std::array<glm::vec3, 8> get_orthographic_frustum_corners() const;
    };
}