#pragma once
#include "Core.h"
#include "Camera.h"
#include "Vector.h"
#include "Bounds.h"

namespace MELT
{
    struct Ray
    {
        M_VEC3 origin;
        M_VEC3 direction;

        Ray() = default;

        Ray(const M_VEC3& _origin, const M_VEC3& _direction)
            : origin(_origin), direction(glm::normalize(_direction)) {}

        // Get a point on the ray at distance 't'
        M_VEC3 at(float t) const{
            return origin + t * direction;
        }
    };

    class RayCast
    {
    public:
        static glm::vec3 ScreenToWorldRay(int cursorX, int cursorY, const Camera& _camera);
        static glm::vec3 ScreenToWorldRay(glm::vec2 _mouseScreenPos, const Camera& _camera);
        static glm::vec3 ScreenToWorldRay(int cursorX, int cursorY, int screenWidth, int screenHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

        static Ray screen_to_world_ray(glm::vec2 _mouse_screen_pos, const Camera& _camera);

        static bool RayIntersectsSphere(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& sphereCenter, float radius);
        static bool RayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir,const glm::vec3& minBounds, const glm::vec3& maxBounds);
        static bool RayIntersectsAABB(const AABB& _aabb);
        static bool ray_intersect_plane(const glm::vec3& _ray_origin, const glm::vec3& _ray_dir, const glm::vec3& _plane_point, const glm::vec3& _plane_normal, glm::vec3& _out_intersection, glm::vec3& _out_normal);
    };
}
