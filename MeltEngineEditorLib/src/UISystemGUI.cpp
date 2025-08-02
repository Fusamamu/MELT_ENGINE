#include "UISystemGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    UISystemGUI::UISystemGUI()
    {

    }

    void UISystemGUI::init(Editor* _editor)
    {
        m_editor = _editor;
        m_engine = _editor->engine;
    }

    void UISystemGUI::draw_gui()
    {
        unsigned int ChildBackground_Color = IM_COL32(26, 28, 27, 255);

        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
        if (ImGui::Begin("UI System"))
        {
            if (ImGui::Button("Create widget"))
            {
                MELT::UI::Panel* _widget = _working_scene->ui_system.add_widget<MELT::UI::Panel>("some panel");
                _widget->bounds = { 100, 100, 100, 100 };
            }
        }
        ImGui::End();
        ImGui::PopStyleColor();
    }
}
