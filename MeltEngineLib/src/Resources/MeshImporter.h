#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Core.h"
#include "Mesh.h"

namespace MELT
{
    class MeshImporter
    {
        std::vector<Mesh> Meshes;

        MeshImporter();
        ~MeshImporter();

        void LoadModel(const std::string& _path);
        void ProcessNode(aiNode* _node, const aiScene* _scene);
        Mesh ProcessMesh(aiMesh* _mesh, const aiScene* _scene);
    };
}