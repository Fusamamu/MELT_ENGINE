#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace MELT
{
    TextureManager::TextureManager()
    {
    }

    void TextureManager::Init()
    {
        TextureData _textureData;

        _textureData.TextureFileName     = "blacknwhite";
        _textureData.FileExtension       = ".png";
        _textureData.TextureFileLocation = "../Project/Resources/Textures/";
        _textureData.SpriteSheetPath     = _textureData.TextureFileLocation + _textureData.TextureFileName + ".yaml";


        YAML::Node _root = YAML::LoadFile(_textureData.SpriteSheetPath);

        const YAML::Node _spriteNode = _root["Sprites"];

        for(std::size_t _i = 0; _i < _spriteNode.size(); ++_i)
        {
            SpriteData _spriteData;

            YAML::Node _spriteChild = _spriteNode[_i];

            _spriteData.Name = _spriteChild["Name"].as<std::string>();

            std::cout << _spriteData.Name << std::endl;

            _textureData.SpriteDataMap.emplace(_spriteData.Name, _spriteData);
        }



        glGenTextures(1, &_textureData.TextureID);
        glBindTexture(GL_TEXTURE_2D, _textureData.TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S    , GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T    , GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int _nrChannels;
        stbi_set_flip_vertically_on_load(true);

        unsigned char* data = stbi_load(
                "../Project/Resources/Textures/blacknwhite.png",
                &_textureData.Width,
                &_textureData.Height,
                &_nrChannels, 0);

        if (data)
        {
            // Assuming 8 bits (1 byte) per channel
            int bitDepth = 8;

            // Calculate the size in bytes
            int _sizeInBytes = _textureData.Width * _textureData.Height * _nrChannels * (bitDepth / 8);
            float sizeInMB = (float)_sizeInBytes / 1024.0f / 1024.0f;

            _textureData.TextureSizeMb = sizeInMB;

            std::cout << "Image dimensions: " << _textureData.Width << "x" << _textureData.Height << std::endl;
            std::cout << "Channels: " << _nrChannels << std::endl;
            std::cout << "Size in MB: " << sizeInMB << " MB" << std::endl;

//            GLint format = GL_RGB;
//            if (_nrChannels == 4)
            GLint   format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, _textureData.Width, _textureData.Height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            TextureDataTable.emplace("blacknwhite", _textureData);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }
}