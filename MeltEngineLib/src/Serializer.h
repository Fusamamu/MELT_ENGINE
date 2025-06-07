#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Core.h"
#include "Scene.h"
#include "Transform.h"

namespace YAML
{
    template<>
    struct convert<M_VEC3>
    {
        static Node encode(const M_VEC3& _vec)
        {
            Node node;
            node.push_back(_vec.x);
            node.push_back(_vec.y);
            node.push_back(_vec.z);
            return node;
        }

        static bool decode(const Node& _node, M_VEC3& _vec)
        {
            if(!_node.IsSequence() || _node.size() != 3)
                return false;
            _vec.x = _node[0].as<float>();
            _vec.y = _node[1].as<float>();
            _vec.z = _node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<MELT::Transform>
    {
        static Node encode(const MELT::Transform& _transform)
        {
            Node node;
            node["position"] = _transform.position;
            node["rotation"] = _transform.rotation;
            node["scale"]    = _transform.scale;
            return node;
        }

        static bool decode(const Node& _node, MELT::Transform& _transform)
        {
            if (!_node["position"] || !_node["rotation"] || !_node["scale"])
                return false;

            _transform.position = _node["position"].as<M_VEC3>();
            _transform.rotation = _node["rotation"].as<M_VEC3>();
            _transform.scale    = _node["scale"]   .as<M_VEC3>();
            return true;
        }
    };
}


namespace MELT
{
    class Serializer
    {

    };

    class ISceneSerializer {
    public:
        virtual void serialize_entity(entt::entity _entity) = 0;

        virtual void Serialize(entt::registry& registry, const std::string& path) = 0;
        virtual void Deserialize(entt::registry& registry, const std::string& path) = 0;
        virtual ~ISceneSerializer() = default;
    };

    class YAMLSceneSerializer //: public ISceneSerializer
    {
    public:

        std::string serialize_scene(const Scene& _scene);

        // void Serialize  (entt::registry& registry, const std::string& path) override;
        // void Deserialize(entt::registry& registry, const std::string& path) override;
    };
}


#endif //SERIALIZER_H
