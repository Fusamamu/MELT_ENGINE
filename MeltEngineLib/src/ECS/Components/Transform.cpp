#include "ECS/Components/Transform.h"

namespace MELT
{
    glm::mat4 Transform::GetTransformMatrix() const
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);

        // Create rotation matrices for each axis
        glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.0f), Rotation.x, glm::vec3(1, 0, 0));
        glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.0f), Rotation.y, glm::vec3(0, 1, 0));
        glm::mat4 rotationZMatrix = glm::rotate(glm::mat4(1.0f), Rotation.z, glm::vec3(0, 0, 1));

        // Combine rotations into a single rotation matrix
        glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

        // Create scale matrix
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

        // Combine all transformations: Translation * Rotation * Scale
        glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        return translationMatrix;
    }
}