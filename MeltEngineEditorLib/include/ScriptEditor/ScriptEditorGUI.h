#pragma once
#include <vector>
#include <memory>
#include <regex>
#include <string>
#include <sstream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

namespace MELT_EDITOR
{
    class ScriptEditorGUI
    {
    public:
        bool IsOpen;

        std::vector<char> textBuffer;

        std::vector<std::string> lua_keywords = { "local", "function", "end", "if", "then", "else", "elseif", "for", "while", "do", "return", "break" };

        ImVec4 color_keyword = ImVec4(0.8f, 0.3f, 0.6f, 1.0f);
        ImVec4 color_string  = ImVec4(0.6f, 0.6f, 0.2f, 1.0f);
        ImVec4 color_comment = ImVec4(0.3f, 0.8f, 0.3f, 1.0f);
        ImVec4 color_number  = ImVec4(0.8f, 0.5f, 0.2f, 1.0f);
        ImVec4 color_default = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        ScriptEditorGUI();
        void DrawGUI();

        void RenderSyntaxHighlightedText(const char* code, const ImVec2& start_pos, const ImVec2& size);
    };
}