#include "Serializer.h"

namespace MELT
{
    std::string YAMLSceneSerializer::serialize_scene(const Scene& _scene)
    {
        YAML::Emitter _out;

        _out << YAML::BeginMap;
        _out << YAML::Key << "scene info" << YAML::Value << YAML::BeginSeq;
            _out << YAML::BeginMap;
            _out << YAML::Key << "name" << YAML::Value << _scene.name;
            _out << YAML::Key << "uuid" << YAML::Value << _scene.uuid;
            _out << YAML::EndMap;
        _out << YAML::EndSeq;
        _out << YAML::EndMap;

        _out << YAML::BeginMap;
        _out << YAML::Key << "nodes" << YAML::Value << YAML::BeginSeq;

        for (const auto& _node : _scene.get_all_nodes())
        {
            _out << YAML::BeginSeq;

            _out << YAML::BeginMap;
            _out << YAML::Key << "name" << YAML::Value << _node.name;
            _out << YAML::EndMap;

            auto& _transform = _scene.ecs_registry.get<Transform>(_node.get_entity());
            _out << YAML::BeginMap;
            _out << YAML::Key << "transform" << YAML::Value << YAML::Node(_transform);
            _out << YAML::EndMap;

            _out << YAML::EndSeq;
        }

        _out << YAML::EndSeq;
        _out << YAML::EndMap;

        return std::string(_out.c_str());
    }
}