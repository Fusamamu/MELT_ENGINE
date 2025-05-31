#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace MELT
{
    void ResourceManager::init()
    {
        load_default_cube();
        load_texture("../MeltEngineLib/res/textures/open-file.png");
    }

    void ResourceManager::load_default_cube()
    {
        Cube _cube;
        default_cube.name = "default_cube";
        default_cube.mesh = new Mesh(_cube.get_mesh());
    }

    void ResourceManager::load_texture(std::filesystem::path _path)
    {
        Texture _texture;

        std::string _fpStr  = _path.string();
        const char* _fpCStr = _fpStr.c_str();
        _texture.p_data = stbi_load(_fpCStr, &_texture.width, &_texture.height, &_texture.nrComponents, 0);
        if(!_texture.p_data)
        {
            std::cerr << "Image failed to load at path: " << _path << std::endl;
            stbi_image_free(_texture.p_data);
        }

        assert(_texture.p_data != nullptr && "No data loaded!");

        GLenum _format;

        switch(_texture.nrComponents)
        {
            case 1: _format = GL_RED ; break;
            case 3: _format = GL_RGB ; break;
            case 4: _format = GL_RGBA; break;
            default:
                std::cerr << "Unsupported image format: " << _texture.nrComponents << " channels\n";
                stbi_image_free(_texture.p_data);
                assert(false && "Unsupported image format");
                return;
        }

        glGenTextures   (1, &_texture.texture_id);
        glBindTexture   (GL_TEXTURE_2D, _texture.texture_id);
        glTexImage2D    (GL_TEXTURE_2D, 0, _format, _texture.width, _texture.height, 0, _format, GL_UNSIGNED_BYTE, _texture.p_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S    , GL_CLAMP_TO_EDGE);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T    , GL_CLAMP_TO_EDGE);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture   (GL_TEXTURE_2D, 0);

        stbi_image_free(_texture.p_data);

        TextureData _texture_data;
        _texture_data.p_texture = new Texture(_texture);
        _texture_data.name          = _path.filename().string();
        _texture_data.file_location = _path.string();
        _texture_data.file_name     = _path.filename().string();
        _texture_data.extension     = _path.extension().string();

        texture_data_table.try_emplace(_texture_data.name, std::move(_texture_data));
    }

    TextureData* ResourceManager::get_texture_data(const std::string& _texture_name)
    {
        auto _it = texture_data_table.find(_texture_name);
        if(_it != texture_data_table.end())
            return &_it->second;
        return nullptr;
    }
}