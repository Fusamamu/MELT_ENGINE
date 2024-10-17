#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <GL/glew.h>

namespace MELT
{
    struct TextureData
    {
        std::string TextureFileName;
        std::string FileExtension;
        std::string TextureFileLocation;

        unsigned int TextureID;

        int Width;
        int Height;

        float TextureSizeMb;
        float DisplayScale = 1.0f;
    };

    class TextureManager
    {
    public:
        std::unordered_map<std::string, TextureData> TextureDataTable;

        TextureManager();
        void Init();
    };
}