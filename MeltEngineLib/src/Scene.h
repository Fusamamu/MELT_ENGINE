#ifndef SCENE_H
#define SCENE_H

#include "Core.h"

namespace MELT
{
    class Node;

    class Scene
    {
    public:
        entt::registry ecs_registry;
        Scene()  = default;
        ~Scene() = default;

        Node create_node(const std::string& _name);
        void destroy_node(const Node& _node);
    };
}

#endif
