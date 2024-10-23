#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "yaml-cpp/yaml.h"

namespace MELT
{
    struct SpriteData
    {
        std::string Name;
        glm::vec2 Position;
        glm::vec2 Size;
        std::array<glm::vec2, 4> TexCoords;
    };

    struct TextureData
    {
        std::string TextureFileName;
        std::string FileExtension;
        std::string TextureFileLocation;
        std::filesystem::path SpriteSheetPath;

        unsigned int TextureID;

        int Width;
        int Height;

        float TextureSizeMb;
        float DisplayScale = 1.0f;

        std::unordered_map<std::string, SpriteData> SpriteDataMap;
    };

    class TextureManager
    {
    public:
        std::unordered_map<std::string, TextureData> TextureDataTable;

        TextureManager();
        void Init();
    };
}