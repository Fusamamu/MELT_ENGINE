#ifndef BOUNDS_H
#define BOUNDS_H

#include "Core.h"

namespace MELT
{
    struct AABB
    {
        M_VEC3 min{ 0.0f };
        M_VEC3 max{ 0.0f };

        // Create an empty AABB
        static AABB empty()
        {
            return {
                glm::vec3(std::numeric_limits<float>::max()),
                glm::vec3(std::numeric_limits<float>::lowest())
            };
        }

        M_VEC3 size        () const { return max - min; }            // Size of the box (width, height, depth)
        M_VEC3 center      () const { return (min + max) * 0.5f; }   // Center of the box
        M_VEC3 half_extents() const { return size() * 0.5f; }        // Half extents from center

        // Expand the box to include a point
        void expand_to_include(const glm::vec3& point)
        {
            min = glm::min(min, point);
            max = glm::max(max, point);
        }

        // Expand the box to include another AABB
        void expand_to_include(const AABB& other)
        {
            expand_to_include(other.min);
            expand_to_include(other.max);
        }

        // Check if a point is inside the box
        bool contains(const glm::vec3& point) const
        {
            return (point.x >= min.x && point.x <= max.x) &&
                   (point.y >= min.y && point.y <= max.y) &&
                   (point.z >= min.z && point.z <= max.z);
        }

        // Check if this AABB intersects another
        bool intersects(const AABB& other) const
        {
            return (min.x <= other.max.x && max.x >= other.min.x) &&
                   (min.y <= other.max.y && max.y >= other.min.y) &&
                   (min.z <= other.max.z && max.z >= other.min.z);
        }

        // Move the AABB by offset
        void translate(const glm::vec3& offset)
        {
            min += offset;
            max += offset;
        }

        // Scaled AABB (relative to center)
        AABB scaled(float scale) const
        {
            glm::vec3 c = center();
            glm::vec3 h = half_extents() * scale;
            return { c - h, c + h };
        }

        // Get corners (8)
        std::array<glm::vec3, 8> corners() const
        {
            return
            {
                glm::vec3{min.x, min.y, min.z},
                glm::vec3{max.x, min.y, min.z},
                glm::vec3{min.x, max.y, min.z},
                glm::vec3{max.x, max.y, min.z},
                glm::vec3{min.x, min.y, max.z},
                glm::vec3{max.x, min.y, max.z},
                glm::vec3{min.x, max.y, max.z},
                glm::vec3{max.x, max.y, max.z}
            };
        }
    };
}

#endif //BOUNDS_H
