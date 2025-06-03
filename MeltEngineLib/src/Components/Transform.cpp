#include "Transform.h"

namespace MELT
{
    glm::mat4 Transform::get_transform_matrix() const
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);

        // Create rotation matrices for each axis
        glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0));
        glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0));
        glm::mat4 rotationZMatrix = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0, 1));

        // Combine rotations into a single rotation matrix
        glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

        // Create scale matrix
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

        // Combine all transformations: Translation * Rotation * Scale
        glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        return translationMatrix;
    }
}