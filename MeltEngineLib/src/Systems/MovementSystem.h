#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "Core.h"
#include "Transform.h"
#include "Light.h"
#include "TileGridFixedSize.h"

namespace MELT
{
    class MovementSystem
    {
    public:
        void init()
        {
        }

        void update(entt::registry& _registry, float _deltaTime)
        {
            auto view = _registry.view<Transform>(entt::exclude<Light>);

            for (auto entity : view)
            {
                auto& transform = view.get<Transform>(entity);
                transform.position += 0.05f;
            }

            auto _ctx = _registry.ctx();
            if (_ctx.contains<MELT::Grid>())
            {
                auto& _tile_grid = _registry.ctx().get<Grid>();

                std::cout << "Yae" << std::endl;
            }
        }
    };
}

#endif
