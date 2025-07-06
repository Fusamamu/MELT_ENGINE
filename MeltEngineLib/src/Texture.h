#ifndef TEXTURE_H
#define TEXTURE_H

namespace MELT
{
    struct Texture
    {
        GLuint texture_id;
        GLenum texture_target = GL_TEXTURE_2D;
        int width, height, nrComponents;
        unsigned char* p_data;

        void bind(int _slot = 0) const
        {
            glActiveTexture(GL_TEXTURE0 + _slot);
            glBindTexture(texture_target, texture_id);
        }
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
            uuid = generate_uuid(reinterpret_cast<uintptr_t>(this));
            std::cout << "Texture UUID : " << uuid << std::endl;
        }
    };
}

#endif //TEXTURE_H
