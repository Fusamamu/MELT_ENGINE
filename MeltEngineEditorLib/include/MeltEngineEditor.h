#pragma once
#include <cstdio>
#include <iostream>
#include <functional>
#include "MeltEngine.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

namespace MELT_EDITOR
{
    class Editor
    {   
    public:
        MELT::Engine* Engine;
        explicit Editor(MELT::Engine* _engine);
        ~Editor();

        void UpdateInput(SDL_Event _event);
        void Update();
    };
}
