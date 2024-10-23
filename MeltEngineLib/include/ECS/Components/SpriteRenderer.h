#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MELT
{
    struct SpriteRenderer
    {
        std::string SourceTextureFileName;
        std::string SourceTexturePath;
        std::array<glm::vec2, 4> TexCoords;
    };
}