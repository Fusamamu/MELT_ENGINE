#include "Scene.h"
#include "Node.h"

namespace MELT
{
    Node Scene::create_node(const std::string& _name)
    {
        entt::entity _entity = ecs_registry.create();
        return Node(_name, this, _entity);
    }

    void Scene::destroy_node(const Node& _node)
    {
        ecs_registry.destroy(_node.get_entity());
    }
}
