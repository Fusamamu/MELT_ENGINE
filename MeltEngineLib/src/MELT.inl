#pragma once

#include <entt/entt.hpp>

namespace MELT
{
    template<typename T>
    void reflect_type(const char* name)
    {
        using namespace entt::literals;
        entt::meta_factory<T>{}.type("reflected_type"_hs);
    }
}