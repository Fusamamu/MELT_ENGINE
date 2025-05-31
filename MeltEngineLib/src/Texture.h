#ifndef TEXTURE_H
#define TEXTURE_H

namespace MELT
{
    struct Texture
    {
        GLuint texture_id;
        int width, height, nrComponents;
        unsigned char* p_data;
    };

    struct TextureData
    {
        std::string name;
        UUID uuid;
        Texture* p_texture;

        std::string file_location;
        std::string file_name;
        std::string extension;

        TextureData()
        {
            uuid = GenerateUUID(reinterpret_cast<uintptr_t>(this));
        }
    };
}
#endif //TEXTURE_H
