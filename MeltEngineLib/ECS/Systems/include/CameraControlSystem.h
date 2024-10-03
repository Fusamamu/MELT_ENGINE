#pragma once
#include "SystemManager.h"

namespace MELT
{
    class CameraControlSystem : public System
    {
    public:
        void Init();
        void Update(float _dt);
    };
}