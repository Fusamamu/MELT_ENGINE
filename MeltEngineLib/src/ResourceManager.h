#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "Core.h"
#include "Texture.h"
#include "Cube.h"
#include "Quad.h"
#include "Plane.h"
#include "Line.h"
#include "Mesh.h"

namespace MELT
{
    class ResourceManager
    {
    public:
        MeshData default_cube;
        MeshData default_quad;
        MeshData default_plane;
        MeshData debug_line;

        ResourceManager () = default;
        ~ResourceManager() = default;

        void init();
        void load_default_cube();
        void load_texture(std::filesystem::path _path);
        void load_model  (std::filesystem::path _path);
        void process_node(aiNode* _node, const aiScene* _scene);
        Mesh process_mesh(aiMesh* _mesh, const aiScene* _scene);

        TextureData* get_texture_data(const std::string& _texture_name);
        MeshData*    get_mesh_data   (const std::string& _mesh_name);
    private:
        std::unordered_map<std::string, TextureData> texture_data_table;
        std::unordered_map<std::string, MeshData   > mesh_data_table;
    };
}

#endif
