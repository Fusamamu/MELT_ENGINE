#include "RayCast.h"

namespace MELT
{
    glm::vec3 RayCast::ScreenToWorldRay(int _cursorX, int _cursorY, const Camera& _camera)
    {
        return ScreenToWorldRay(_cursorX, _cursorY, static_cast<int>(_camera.ScreenSize.x), static_cast<int>(_camera.ScreenSize.y), _camera.GetViewMatrix(), _camera.GetOrthographicProjectionMatrix());
    }

    glm::vec3 RayCast::ScreenToWorldRay(glm::vec2 _mouseScreenPos, const Camera& _camera)
    {
//        float _ndcX =        (2.0f * _mouseScreenPos.x) / _camera.WindowSize.x - 1.0f;
//        float _ndcY = 1.0f - (2.0f * _mouseScreenPos.y) / _camera.WindowSize.y;
//
//        std::cout << "NDC : " << _ndcX << ", " << _ndcY << std::endl;
//
//        glm::vec4 _nearClip = glm::vec4(_ndcX, _ndcY, 0.0f, 1.0f);
//        glm::vec4 _farClip  = glm::vec4(_ndcX, _ndcY, 1.0f, 1.0f);
//
//        glm::mat4 _projInv = glm::inverse(_camera.GetOrthographicProjectionMatrix());
//        glm::mat4 _viewInv = glm::inverse(_camera.GetViewMatrix());
//
//        glm::vec4 _nearPoint = _viewInv * _projInv * _nearClip;
//        glm::vec4 _farPoint  = _viewInv * _projInv * _farClip;
//
//        glm::vec4 _ray = _farPoint - _nearPoint;
//
//        glm::vec3 _normalizedRay = glm::normalize(glm::vec3(_ray.x, _ray.y, _ray.z));


        // Convert screen space to NDC (Normalized Device Coordinates)
        float _ndcX = (2.0f * _mouseScreenPos.x) / _camera.WindowSize.x - 1.0f;
        float _ndcY = 1.0f - (2.0f * _mouseScreenPos.y) / _camera.WindowSize.y;

        std::cout << "NDC : " << _ndcX << ", " << _ndcY << std::endl;

        // Define near and far clip points in clip space
        glm::vec4 _nearClip = glm::vec4(_ndcX, _ndcY, 0.0f, 1.0f); // near plane in clip space
        glm::vec4 _farClip  = glm::vec4(_ndcX, _ndcY, 1.0f, 1.0f); // far plane in clip space

        // Inverse the projection and view matrices to go from clip space back to world space
        glm::mat4 _projInv = glm::inverse(_camera.GetOrthographicProjectionMatrix());
        glm::mat4 _viewInv = glm::inverse(_camera.GetViewMatrix());

        // Transform clip space coordinates into world space
        glm::vec4 _nearPoint = _viewInv * _projInv * _nearClip; // World space near point
        glm::vec4 _farPoint  = _viewInv * _projInv * _farClip;  // World space far point

        // Convert homogeneous coordinates to 3D by dividing by w
        _nearPoint /= _nearPoint.w;
        _farPoint /= _farPoint.w;

        // Compute the ray direction (from near to far point)
        glm::vec3 _rayDirection = glm::normalize(glm::vec3(_farPoint - _nearPoint));

        return _rayDirection;
    }


    static glm::vec3 ScreenToWorldRay(
            int cursorX, int cursorY,
            int screenWidth, int screenHeight,
            const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
            bool isOrthographic)
    {
        // Convert mouse position to Normalized Device Coordinates (NDC)
        float ndcX = (2.0f * cursorX) / screenWidth - 1.0f;
        float ndcY = 1.0f - (2.0f * cursorY) / screenHeight;

        // Convert NDC to clip space
        glm::vec4 rayClip = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);

        // Convert clip space to eye (camera) space
        glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, isOrthographic ? -1.0f : rayEye.z, 0.0f);

        // Convert eye space to world space
        glm::vec3 rayWorld = glm::vec3(glm::inverse(viewMatrix) * rayEye);

        if (!isOrthographic) {
            // Normalize for perspective projection
            rayWorld = glm::normalize(rayWorld);
        } else {
            // In orthographic, ray direction is straight along the z-axis in view space
            rayWorld = glm::normalize(glm::vec3(viewMatrix[2])); // Z-axis direction from the view matrix
        }

        return rayWorld;
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

        if (tMin > tMax)
            std::swap(tMin, tMax);

        float tyMin = (minBounds.y - rayOrigin.y) / rayDir.y;
        float tyMax = (maxBounds.y - rayOrigin.y) / rayDir.y;

        if (tyMin > tyMax)
            std::swap(tyMin, tyMax);

        if ((tMin > tyMax) || (tyMin > tMax))
            return false;

        if (tyMin > tMin)
            tMin = tyMin;

        if (tyMax < tMax)
            tMax = tyMax;

        float tzMin = (minBounds.z - rayOrigin.z) / rayDir.z;
        float tzMax = (maxBounds.z - rayOrigin.z) / rayDir.z;

        if (tzMin > tzMax)
            std::swap(tzMin, tzMax);

        if ((tMin > tzMax) || (tzMin > tMax))
        {
            std::cout << "Ray cast missed" << std::endl;
            return false;
        }

        std::cout << "Ray cast hit" << std::endl;
        return true;
    }
}