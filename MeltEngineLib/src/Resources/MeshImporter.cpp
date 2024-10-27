#include "MeshImporter.h"

namespace MELT
{
    void MeshImporter::LoadModel(const std::string &_path)
    {
        Assimp::Importer _import;

        const aiScene* _scene = _import.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!_scene || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << _import.GetErrorString() << std::endl;
            return;
        }
       // directory = _path.substr(0, _path.find_last_of('/'));

        ProcessNode(_scene->mRootNode, _scene);
    }

    void MeshImporter::ProcessNode(aiNode* _node, const aiScene* _scene)
    {
        for(unsigned int i = 0; i < _node->mNumMeshes; i++)
        {
            aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[i]];
            Meshes.push_back(ProcessMesh(_mesh, _scene));
        }

        for(unsigned int i = 0; i < _node->mNumChildren; i++)
        {
            ProcessNode(_node->mChildren[i], _scene);
        }
    }

    Mesh MeshImporter::ProcessMesh(aiMesh* _mesh, const aiScene* _scene)
    {
        std::vector<Vertex_1P1C1T1N> _vertices;
        std::vector<unsigned int> _indices;

        for(unsigned int i = 0; i < _mesh->mNumVertices; i++)
        {
            Vertex_1P1C1T1N _vertex;

            _vertex.position.x = _mesh->mVertices[i].x;
            _vertex.position.y = _mesh->mVertices[i].y;
            _vertex.position.z = _mesh->mVertices[i].z;

            if (_mesh->HasNormals())
            {
                _vertex.normal.x = _mesh->mNormals[i].x;
                _vertex.normal.y = _mesh->mNormals[i].y;
                _vertex.normal.z = _mesh->mNormals[i].z;
            }

            if(_mesh->mTextureCoords[0])
            {
                _vertex.texCoord.x = _mesh->mTextureCoords[0][i].x;
                _vertex.texCoord.y = _mesh->mTextureCoords[0][i].y;
            }
            else
                _vertex.texCoord = glm::vec2(0.0f, 0.0f);

            _vertices.push_back(_vertex);
        }

        for(unsigned int i = 0; i < _mesh->mNumFaces; i++)
        {
            aiFace _face = _mesh->mFaces[i];
            for(unsigned int j = 0; j < _face.mNumIndices; j++)
                _indices.push_back(_face.mIndices[j]);
        }

        return { _vertices, _indices };
    }
}