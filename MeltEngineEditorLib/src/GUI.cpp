#include "GUI.h"

namespace MELT_GUI
{
    void check_box(const char* _label, bool* _value)
    {
        auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        std::string _id = std::string("##") + _label;

        ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
        ImGui::Text(_label);
        ImGui::PopStyleColor();
        ImGui::SameLine(120.0f);
        ImGui::Checkbox(_id.c_str(), _value);
    }
}