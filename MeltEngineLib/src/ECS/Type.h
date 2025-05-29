#pragma once
#include <iostream>
#include <bitset>

namespace MELT
{
    // Events
    using EventId = std::uint32_t;
    using ParamId = std::uint32_t;

    using Entity        = uint32_t;
    using ComponentType = uint8_t;

    static constexpr Entity        MAX_ENTITIES   = 5000;
    static constexpr ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}