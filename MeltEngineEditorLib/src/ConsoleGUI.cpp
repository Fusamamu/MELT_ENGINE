#include "ConsoleGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    ConsoleGUI::ConsoleGUI()
    {

    }

    void ConsoleGUI::DrawGUI()
    {
        ImGui::Begin("Console");

        MELT::Entity _entity = EditorOwner->Engine->ECSCoord.SelectedEntity;

        const char* _selectedEntity = std::to_string(EditorOwner->Engine->ECSCoord.SelectedEntity).c_str();
        ImGui::Text("Selected Entity : ");
        ImGui::SameLine();
        ImGui::Text("%s", _selectedEntity);
        ImGui::End();

        //Temp
//        if(_entity > 100)
//            return;
//
//        MELT::Transform& _transform = EditorOwner->Engine->ECSCoord.GetComponent<MELT::Transform>(_entity);
//        _transform.Position.x = 100.0f;
    }
}