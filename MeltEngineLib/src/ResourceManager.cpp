#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Primitive/Line.h"

namespace MELT
{
    void ResourceManager::init()
    {
        load_default_cube();

        load_texture("../MeltEngineLib/res/textures/open-file.png"      );
        load_texture("../MeltEngineLib/res/textures/material_icon.png"  );
        load_texture("../MeltEngineLib/res/textures/camera_icon.png"    );
        load_texture("../MeltEngineLib/res/textures/light_icon.png"     );
        load_texture("../MeltEngineLib/res/textures/scene_icon.png"     );
        load_texture("../MeltEngineLib/res/textures/exclamation.png"    );
        load_texture("../MeltEngineLib/res/textures/caution.png"        );

        load_model  ("../MeltEngineLib/res/models/sphere.fbx"           );
        load_model  ("../MeltEngineLib/res/models/teapot/teapot.fbx"    );

        load_shader("../MeltEngineLib/res/shaders/phong.glsl"           );
        load_shader("../MeltEngineLib/res/shaders/MeshOutline.shader"   );
        load_shader("../MeltEngineLib/res/shaders/3DGrid.shader"        );
        load_shader("../MeltEngineLib/res/shaders/Gizmos.shader"        );
        load_shader("../MeltEngineLib/res/shaders/CylinderLine.shader"  );
        load_shader("../MeltEngineLib/res/shaders/camera_frustum.shader");
        load_shader("../MeltEngineLib/res/shaders/depth.shader"         );
        load_shader("../MeltEngineLib/res/shaders/screen_quad.shader"   );

        load_material("../Project/Assets/Materials/new_default_material.mat");
    }

    void ResourceManager::load_default_cube()
    {
        Cube _cube;
        default_cube.name = "default_cube";
        default_cube.mesh = new Mesh(_cube.get_mesh());
        mesh_data_table.try_emplace(default_cube.name, default_cube);

        Quad _quad;
        default_quad.name = "default_quad";
        default_quad.mesh = new Mesh(_quad.get_mesh());
        mesh_data_table.try_emplace(default_quad.name, default_quad);

        Plane _plane (4, 4, 4, 4);
        default_plane.name = "default_plane";
        default_plane.mesh = new Mesh(_plane.get_mesh());
        mesh_data_table.try_emplace(default_plane.name, default_plane);

        Line _line (M_VEC3(0.0f, 0.0f, 0.0f), M_VEC3(10.0f, 10.0f, 10.0f));
        debug_line.name = "debug_line";
        debug_line.mesh = new Mesh(_line.get_mesh());
        mesh_data_table.try_emplace(debug_line.name, debug_line);
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

    void ResourceManager::load_model(std::filesystem::path _path)
    {
        Assimp::Importer _import;

        const aiScene* _scene = _import.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!_scene || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << _import.GetErrorString() << std::endl;
            return;
        }
        process_node(_scene->mRootNode, _scene);
    }

    void ResourceManager::load_shader(std::filesystem::path _path)
    {
        Shader* _loaded_shader = new Shader(_path);

        AssetMetadata _asset_metadata;
        _asset_metadata.name = _path.filename().string();
        _asset_metadata.path = _path.string();
        _asset_metadata.uuid = generate_deterministic_uuid(_path);

        std::cout << _path.filename().string() << std::endl;

        AssetRegistry::instance().register_asset<Shader>(_asset_metadata, _loaded_shader);
    }

    void ResourceManager::load_material(std::filesystem::path _path)
    {
        YAML::Node _root = YAML::LoadFile(_path.string());

        auto material_node = _root["Material"];

        if (!material_node)
            throw std::runtime_error("Invalid material file: 'Material' root not found.");

        GRAPHIC::Material* _material = new GRAPHIC::Material();
        _material->name               = material_node["name"         ].as<std::string>();
        _material->uuid               = material_node["uuid"         ].as<std::string>();
        _material->shader_handle.uuid = material_node["shader_handle"].as<std::string>();

        auto props = material_node["properties"];
        if (props)
        {
            if (props["color"] && props["color"].IsSequence() && props["color"].size() == 4)
            {
                glm::vec4 _color = glm::vec4(
                    props["color"][0].as<float>(),
                    props["color"][1].as<float>(),
                    props["color"][2].as<float>(),
                    props["color"][3].as<float>()
                );

                _material->vec4_uniforms["color"] = _color;
            }

            // if (props["texture"]) {
            //     _material.texture = props["texture"].as<std::string>();
            // }
        }

        _material->validate();

        AssetMetadata _asset_metadata;
        _asset_metadata.name = _material->name;
        _asset_metadata.path = _path.string();
        _asset_metadata.uuid = _material->uuid;

        AssetRegistry::instance().register_asset<GRAPHIC::Material>(_asset_metadata, _material);
    }

    void ResourceManager::process_node(aiNode* _node, const aiScene* _scene)
    {
        for(unsigned int i = 0; i < _node->mNumMeshes; i++)
        {
            aiMesh* _ai_mesh = _scene->mMeshes[_node->mMeshes[i]];
            std::string _name = _ai_mesh->mName.C_Str();

            Mesh _mesh = process_mesh(_scene->mMeshes[_node->mMeshes[i]], _scene);

            Mesh* _new_mesh = new Mesh(_mesh);

            MeshData _mesh_data;
            _mesh_data.name = _name;
            _mesh_data.mesh = new Mesh(_mesh);

            mesh_data_table.try_emplace(_name, std::move(_mesh_data));


            AssetMetadata _asset_metadata;
            _asset_metadata.name = _name;
            _asset_metadata.path = "";
            _asset_metadata.uuid = _new_mesh->gen_uuid();

            AssetRegistry::instance().register_asset<Mesh>(_asset_metadata, _new_mesh);


            std::cout << "loading mesh : " << _name << "\n";
        }

        for(unsigned int i = 0; i < _node->mNumChildren; i++)
            process_node(_node->mChildren[i], _scene);
    }

    Mesh ResourceManager::process_mesh(aiMesh* _mesh, const aiScene* _scene)
    {
        std::vector<Vertex_PCTN> _vertices;
        std::vector<unsigned int> _indices;

        for(unsigned int i = 0; i < _mesh->mNumVertices; i++)
        {
            Vertex_PCTN _vertex;

            _vertex.position.x = _mesh->mVertices[i].x;
            _vertex.position.y = _mesh->mVertices[i].y;
            _vertex.position.z = _mesh->mVertices[i].z;

            _vertex.color.r = 0.0f;
            _vertex.color.g = 0.0f;
            _vertex.color.b = 0.0f;

            if(_mesh->mTextureCoords[0])
            {
                _vertex.texCoord.x = _mesh->mTextureCoords[0][i].x;
                _vertex.texCoord.y = _mesh->mTextureCoords[0][i].y;
            }
            else
                _vertex.texCoord = glm::vec2(0.0f, 0.0f);

            if (_mesh->HasNormals())
            {
                _vertex.normal.x = _mesh->mNormals[i].x;
                _vertex.normal.y = _mesh->mNormals[i].y;
                _vertex.normal.z = _mesh->mNormals[i].z;
            }

            _vertices.push_back(_vertex);
        }

        for(unsigned int i = 0; i < _mesh->mNumFaces; i++)
        {
            aiFace _face = _mesh->mFaces[i];
            for(unsigned int j = 0; j < _face.mNumIndices; j++)
                _indices.push_back(_face.mIndices[j]);
        }

        std::vector<uint8_t> _vertex_buffer;
        _vertex_buffer.resize(_vertices.size() * sizeof(Vertex_PCTN));
        memcpy(_vertex_buffer.data(), _vertices.data(), _vertex_buffer.size());

        Mesh _result_mesh { _vertex_buffer, _indices };
        _result_mesh.layout = createLayout_PCTN();

        return _result_mesh;
    }

    TextureData* ResourceManager::get_texture_data(const std::string& _texture_name)
    {
        auto _it = texture_data_table.find(_texture_name);
        if(_it != texture_data_table.end())
            return &_it->second;
        return nullptr;
    }

    MeshData* ResourceManager::get_mesh_data(const std::string& _mesh_name)
    {
        auto _it = mesh_data_table.find(_mesh_name);
        if(_it != mesh_data_table.end())
            return &_it->second;
        return nullptr;
    }
}
