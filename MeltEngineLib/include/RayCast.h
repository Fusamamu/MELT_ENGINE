#pragma once
#include "Core.h"
#include "Camera.h"
#include "Vector.h"

namespace MELT
{
    class RayCast
    {
    public:
        static glm::vec3 ScreenToWorldRay(int cursorX, int cursorY, const Camera& _camera);
        static glm::vec3 ScreenToWorldRay(glm::vec2 _mouseScreenPos, const Camera& _camera);


        static glm::vec3 ScreenToWorldRay(int cursorX, int cursorY, int screenWidth, int screenHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

        static bool RayIntersectsSphere(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& sphereCenter, float radius);
        static bool RayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir,const glm::vec3& minBounds, const glm::vec3& maxBounds);

    };
}