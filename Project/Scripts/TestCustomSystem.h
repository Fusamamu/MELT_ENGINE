#pragma once
#include "SystemManager.h"

class TestCustomSystem : public MELT::INativeSystem
{
public:
    NATIVE_SYSTEM_OVERRIDE;
};

extern "C" TestCustomSystem* CreateCustomSystem();
