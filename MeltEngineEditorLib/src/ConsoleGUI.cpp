#include "ConsoleGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    ConsoleGUI::ConsoleGUI()
    {

    }

    void ConsoleGUI::draw_gui()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(26, 28, 27, 255));
        ImGui::Begin("Logger");

        MELT::TextureData* _caution_texture = EditorOwner->engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("caution.png");
        MELT::TextureData* _warning_texture = EditorOwner->engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("exclamation.png");

        if (ImGui::Button("CLEAR"))
        {
            EditorOwner->engine->Logger.clear();
        }

        for (const auto& _log_entry : EditorOwner->engine->Logger.log_sink().get_entries())
        {
            if (_caution_texture)
            {
                ImTextureID folderIconTex = (ImTextureID)(intptr_t)_caution_texture->p_texture->texture_id;

                ImGui::Image(folderIconTex, ImVec2(25, 25));
                ImGui::SameLine();
                ImGui::Text(_log_entry.message.c_str());
                ImGui::Separator();
            }
        }


        // if (_caution_texture)
        // {
        //     ImTextureID folderIconTex = (ImTextureID)(intptr_t)_caution_texture->p_texture->texture_id;
        //
        //     ImGui::Image(folderIconTex, ImVec2(25, 25));
        //     ImGui::SameLine();
        //     ImGui::Text("Logger : .........");
        //     ImGui::Separator();
        //
        //     ImGui::Image(folderIconTex, ImVec2(25, 25));
        //     ImGui::SameLine();
        //     ImGui::Text("Logger : .........");
        //     ImGui::Separator();
        // }
        //
        // if (_warning_texture)
        // {
        //     ImTextureID folderIconTex = (ImTextureID)(intptr_t)_warning_texture->p_texture->texture_id;
        //
        //     ImGui::Image(folderIconTex, ImVec2(25, 25));
        //     ImGui::SameLine();
        //     ImGui::Text("Logger : .........");
        //     ImGui::Separator();
        //
        //     ImGui::Image(folderIconTex, ImVec2(25, 25));
        //     ImGui::SameLine();
        //     ImGui::Text("Logger : .........");
        //     ImGui::Separator();
        // }

        ImGui::End();
        ImGui::PopStyleColor();
    }
}