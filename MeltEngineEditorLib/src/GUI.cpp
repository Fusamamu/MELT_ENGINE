#include "GUI.h"

namespace MELT_GUI
{
    void check_box(const char* _label, bool& _value)
    {
        auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        std::string _id = std::string("##") + _label;

        ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
        ImGui::Text(_label);
        ImGui::PopStyleColor();
        ImGui::SameLine(120.0f);
        ImGui::Checkbox(_id.c_str(), &_value);
    }

    void input_float(const char* _label, float& _value)
    {
        auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        std::string _id = std::string("##") + _label;

        ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
        ImGui::Text(_label);
        ImGui::PopStyleColor();
        ImGui::SameLine(120.0f);
        ImGui::InputFloat(_id.c_str(), &_value);
    }

    void input_float_3(const char* _label, glm::vec3& _value)
    {
        auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        std::string _id = std::string("##") + _label;

        ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
        ImGui::Text("%s", _label);
        ImGui::PopStyleColor();
        ImGui::SameLine(120.0f);
        ImGui::InputFloat3(_id.c_str(), glm::value_ptr(_value));
    }

    void input_int_3(const char* _label, uint32_t& _x, uint32_t& _y, uint32_t& _z)
    {
        auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        std::string _id = std::string("##") + _label;

        ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
        ImGui::Text("%s", _label);
        ImGui::PopStyleColor();
        ImGui::SameLine(120.0f);

        int _temp[3] = {
            static_cast<int>(_x),
            static_cast<int>(_y),
            static_cast<int>(_z)
        };

        if (ImGui::InputInt3(_id.c_str(), _temp)) {
            _x = static_cast<uint32_t>(std::max(_temp[0], 0));
            _y = static_cast<uint32_t>(std::max(_temp[1], 0));
            _z = static_cast<uint32_t>(std::max(_temp[2], 0));
        }
    }
}