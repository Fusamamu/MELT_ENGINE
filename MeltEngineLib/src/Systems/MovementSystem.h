#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "Core.h"
#include "Transform.h"
#include "Light.h"

namespace MELT
{
    class MovementSystem
    {
    public:
        void update(entt::registry& registry, float deltaTime)
        {
            auto view = registry.view<Transform>(entt::exclude<Light>);

            for (auto entity : view)
            {
                auto& transform = view.get<Transform>(entity);
                transform.position += 0.05f;
            }
        }
    };
}

#endif
