#pragma once
#include<functional>

namespace MELT
{
    template<typename EventType>
    using EventHandler = std::function<void(const EventType& e)>;
}