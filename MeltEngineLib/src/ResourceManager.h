#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "Core.h"
#include "Texture.h"
#include "Cube.h"
#include "Mesh.h"

namespace MELT
{
    class ResourceManager
    {
    public:
        MeshData default_cube;
        ResourceManager () = default;
        ~ResourceManager() = default;
        void init();
        void load_default_cube();
        void load_texture(std::filesystem::path _path);

        TextureData* get_texture_data(const std::string& _texture_name);
    private:
        std::unordered_map<std::string, TextureData> texture_data_table;
    };
}

#endif
