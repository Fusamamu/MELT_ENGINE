#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Core.h"
#include "AssetRegistry.h"
#include "Texture.h"
#include "Cube.h"
#include "Quad.h"
#include "Plane.h"
#include "Line.h"
#include "Mesh.h"
#include "Material.h"

namespace MELT
{
    class AssimpGLMHelpers
    {
    public:

        static inline glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
        {
            glm::mat4 to;
            //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
            to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
            to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
            to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
            to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
            return to;
        }

        static inline glm::vec3 GetGLMVec(const aiVector3D& vec)
        {
            return glm::vec3(vec.x, vec.y, vec.z);
        }

        static inline glm::quat GetGLMQuat(const aiQuaternion& pOrientation)
        {
            return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
        }
    };

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
        void load_texture (std::filesystem::path _path);
        void load_model   (std::filesystem::path _path);
        void load_shader  (std::filesystem::path _path);
        void load_material(std::filesystem::path _path);
        void process_node(aiNode* _node, const aiScene* _scene);
        Mesh process_mesh(aiMesh* _mesh, const aiScene* _scene);

        std::vector<Vertex_PCTN>       build_vertices_PCTN      (aiMesh* _mesh, const aiScene* _scene);
        std::vector<Vertex_PCTN_TB_BW> build_vertices_PCTN_TB_BW(aiMesh* _mesh, const aiScene* _scene);

        TextureData* get_texture_data(const std::string& _texture_name);
        MeshData*    get_mesh_data   (const std::string& _mesh_name);
    private:
        std::unordered_map<std::string, TextureData> texture_data_table;
        std::unordered_map<std::string, MeshData   > mesh_data_table;
    };
}

#endif
