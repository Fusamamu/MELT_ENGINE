#include "Serializer.h"

namespace MELT
{
    std::string YAMLSceneSerializer::serialize_scene(const Scene& _scene)
    {
        YAML::Emitter _out;

        _out << YAML::BeginMap;

        // Scene Info
        _out << YAML::Key << "scene info" << YAML::Value << YAML::BeginSeq;
        _out << YAML::BeginMap;
        _out << YAML::Key << "name" << YAML::Value << _scene.name;
        _out << YAML::Key << "uuid" << YAML::Value << _scene.uuid;
        _out << YAML::EndMap;
        _out << YAML::EndSeq;

        // Nodes
        _out << YAML::Key << "nodes" << YAML::Value << YAML::BeginSeq;

        for (const auto& _node : _scene.get_all_nodes())
        {
            _out << YAML::BeginMap;

            _out << YAML::Key << "name" << YAML::Value << _node.name;
            _out << YAML::Key << "uuid" << YAML::Value << _node.id;

            auto& _transform = _scene.ecs_registry.get<Transform>(_node.get_entity());
            _out << YAML::Key << TRANSFORM_NODE << YAML::Value << YAML::convert<Transform>::encode(_transform);

            auto& _mesh_renderer = _scene.ecs_registry.get<MeshRenderer>(_node.get_entity());
            _out << YAML::Key << MESH_RENDERER_NODE << YAML::Value << YAML::convert<MeshRenderer>::encode(_mesh_renderer);

            _out << YAML::EndMap;
        }

        _out << YAML::EndSeq;

        _out << YAML::EndMap;

        return std::string(_out.c_str());
    }

    void YAMLSceneSerializer::deserialize_scene(Scene& _scene, const std::string& _save_file)
    {
        YAML::Node _data = YAML::Load(_save_file);

        if (_data["scene info"])
        {
            const YAML::Node& _info = _data["scene info"][0];
            _scene.name = _info["name"].as<std::string>();
            _scene.uuid = _info["uuid"].as<std::string>(); // or uint64_t if needed
        }

        if (_data["nodes"])
        {
            for (const auto& _node : _data["nodes"])
            {
                std::string _name = _node["name"].as<std::string>();
                std::string _uuid = _node["uuid"].as<std::string>();

                // Create node (you might have a function like this)
                Node& _new_node = _scene.create_node(_name);
                _new_node.id = _uuid;

                // Get entity from node and attach Transform
                auto _entity = _new_node.get_entity();
                if (_node[TRANSFORM_NODE])
                {
                    Transform _transform = _node[TRANSFORM_NODE].as<Transform>();
                    _scene.ecs_registry.emplace<Transform>(_entity, _transform);
                }

                if (_node[MESH_RENDERER_NODE])
                {
                    // MeshRenderer _mesh_renderer = _node[MESH_RENDERER_NODE].as<MeshRenderer>();
                    // _scene.ecs_registry.emplace<MeshRenderer>(_entity, _mesh_renderer);
                }
            }
        }
    }
}