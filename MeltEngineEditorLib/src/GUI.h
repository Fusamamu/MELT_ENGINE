#ifndef GUI_H
#define GUI_H

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo.h"

namespace MELT_GUI
{
    void check_box(const char* _label, bool* _value);
}

#endif //GUI_H
