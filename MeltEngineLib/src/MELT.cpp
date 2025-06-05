#include "MELT.h"
#include "MELT.inl"
#include <entt/entt.hpp>

namespace MELT
{
    void MeltHello()
    {
        std::cout << "Hello from MELT!" << std::endl;
    }

    void reflect_CustomComponent() {
        using namespace entt::literals;
        entt::meta_factory<CustomComponent>{}.type("reflected_type"_hs);
    }
}