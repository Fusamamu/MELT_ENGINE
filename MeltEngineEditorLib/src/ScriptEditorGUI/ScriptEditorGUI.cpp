#include "ScriptEditorGUI.h"

namespace MELT_EDITOR
{
    ScriptEditorGUI::ScriptEditorGUI()
    {
        textBuffer = std::vector<char>(1024 * 16);
    }

    void ScriptEditorGUI::DrawGUI()
    {
        ImGui::Begin("Text Editor", &IsOpen, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Save")) {
                }
                if (ImGui::MenuItem("Load")) {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::PushStyleColor(ImGuiCol_Text          , ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBg       , ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive , ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_Border        , ImVec4(0, 0, 0, 0));

        ImVec2 editor_pos = ImGui::GetCursorScreenPos();
        ImGui::InputTextMultiline("##text", textBuffer.data(), textBuffer.size(), ImVec2(editor_pos.x, ImGui::GetTextLineHeight() * 20), ImGuiInputTextFlags_AllowTabInput);

        ImGui::PopStyleColor(5);

        RenderSyntaxHighlightedText(textBuffer.data(), editor_pos, ImGui::GetItemRectSize());

        ImGui::End();
    }

    void ScriptEditorGUI::RenderSyntaxHighlightedText(const char* code, const ImVec2& start_pos, const ImVec2& size)
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 cursor = start_pos;

        // Example regexes for tokens
        std::regex keyword_regex(R"(\b(local|function|end|if|then|else|elseif|for|while|do|return|break)\b)");
        std::regex string_regex("\"(.*?)\"|\'(.*?)\'");
        std::regex number_regex(R"(\b[0-9]+(\.[0-9]+)?\b)");
        std::regex comment_regex(R"(--.*)");

        // Tokenize and render each _line
        std::istringstream _stream(code);
        std::string _line;

        while (std::getline(_stream, _line))
        {
            size_t last_pos = 0;

            for (const auto& regex_pair : {std::make_pair(keyword_regex, color_keyword),
                                           std::make_pair(string_regex, color_string),
                                           std::make_pair(number_regex, color_number),
                                           std::make_pair(comment_regex, color_comment)})
            {
                std::sregex_iterator _iter(_line.begin(), _line.end(), regex_pair.first);
                std::sregex_iterator _end;

                while (_iter != _end)
                {
                    // Draw text before the match
                    if (last_pos < _iter->position())
                    {
                        draw_list->AddText(cursor, ImGui::ColorConvertFloat4ToU32(color_default), _line.substr(last_pos, _iter->position() - last_pos).c_str());
                        cursor.x += ImGui::CalcTextSize(_line.substr(last_pos, _iter->position() - last_pos).c_str()).x;
                    }

                    // Draw the match with its color
                    draw_list->AddText(cursor, ImGui::ColorConvertFloat4ToU32(regex_pair.second), _iter->str().c_str());
                    cursor.x += ImGui::CalcTextSize(_iter->str().c_str()).x;

                    last_pos = _iter->position() + _iter->length();

                    ++_iter;
                }
            }

            // Draw remaining text on the _line
            if (last_pos < _line.size())
            {
                draw_list->AddText(cursor, ImGui::ColorConvertFloat4ToU32(color_default), _line.substr(last_pos).c_str());
                cursor.x += ImGui::CalcTextSize(_line.substr(last_pos).c_str()).x;
            }

            cursor.x = start_pos.x;
            cursor.y += ImGui::GetTextLineHeight();
        }
    }
}