#ifndef INSPECTORGUI_H
#define INSPECTORGUI_H

#include "GUI.h"

namespace MELT_EDITOR
{
    class Editor;

    class InspectorGUI
    {
    public:
        InspectorGUI();
        void init(Editor* _editor);
        void draw_gui();
    private:
        Editor*       m_editor;
        MELT::Engine* m_engine;

        void draw_transform_component_panel      (MELT::Transform     & _transform     );
        void draw_renderer_component_panel       (MELT::MeshRenderer  & _renderer      );
        void draw_box_collider_component_panel   (MELT::BoxCollider   & _box_collider  );
        void draw_sprite_renderer_component_panel(MELT::SpriteRenderer& _spriteRenderer);
        void draw_camera_component_panel         (MELT::Camera        & _camera        );
        void draw_light_component_panel          (MELT::Light         & _light         );
    };
}

#endif //INSPECTORGUI_H
