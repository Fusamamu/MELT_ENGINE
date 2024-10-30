#include "RayCast.h"

namespace MELT
{
    glm::vec3 RayCast::ScreenToWorldRay(int _cursorX, int _cursorY, const Camera& _camera)
    {
        return ScreenToWorldRay(_cursorX, _cursorY, _camera.ScreenSize.x, _camera.ScreenSize.y, _camera.GetViewMatrix(), _camera.GetOrthographicProjectionMatrix());
    }

    glm::vec3 RayCast::ScreenToWorldRay(int cursorX, int cursorY, int screenWidth, int screenHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
    {
        // Convert mouse position to NDC
        float ndcX = (2.0f * cursorX) / screenWidth - 1.0f;
        float ndcY = 1.0f - (2.0f * cursorY) / screenHeight;

        // Convert NDC to clip space
        glm::vec4 rayClip = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);

        // Convert clip space to eye space
        glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

        // Convert eye space to world space
        glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(viewMatrix) * rayEye));

        return rayWorld;
    }

    bool RayCast::RayIntersectsSphere(const glm::vec3& rayOrigin, const glm::vec3& rayDir,
                                      const glm::vec3& sphereCenter, float radius) {
        glm::vec3 L = sphereCenter - rayOrigin;
        float tca = glm::dot(L, rayDir);
        float d2 = glm::dot(L, L) - tca * tca;
        if (d2 > radius * radius) return false;
        float thc = std::sqrt(radius * radius - d2);
        float t0 = tca - thc;
        float t1 = tca + thc;
        return t0 >= 0 || t1 >= 0;
    }

    bool RayCast::RayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& minBounds, const glm::vec3& maxBounds)
    {
        float tMin = (minBounds.x - rayOrigin.x) / rayDir.x;
        float tMax = (maxBounds.x - rayOrigin.x) / rayDir.x;
        if (tMin > tMax) std::swap(tMin, tMax);

        float tyMin = (minBounds.y - rayOrigin.y) / rayDir.y;
        float tyMax = (maxBounds.y - rayOrigin.y) / rayDir.y;
        if (tyMin > tyMax) std::swap(tyMin, tyMax);

        if ((tMin > tyMax) || (tyMin > tMax)) return false;
        if (tyMin > tMin) tMin = tyMin;
        if (tyMax < tMax) tMax = tyMax;

        float tzMin = (minBounds.z - rayOrigin.z) / rayDir.z;
        float tzMax = (maxBounds.z - rayOrigin.z) / rayDir.z;

        if (tzMin > tzMax)
            std::swap(tzMin, tzMax);

        if ((tMin > tzMax) || (tzMin > tMax))
            return false;

        return true;
    }
}