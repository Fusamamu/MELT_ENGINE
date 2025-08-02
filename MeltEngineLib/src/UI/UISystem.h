#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Core.h"
#include "UI.h"
#include "Text.h"

namespace MELT
{
    class UISystem
    {
    public:

        std::map<GLchar, UI::Character> character_map; //should move to resource??

        std::vector<UI::Widget_variant_up>  m_widgets;

        UISystem() = default;
        ~UISystem() = default;

        void init();

        template<UI::Widget T>
        T* add_widget(const std::string& _name)
        {
            auto _widget = std::make_unique<T>();
            _widget->name = _name;
            T* ptr = _widget.get();
            m_widgets.push_back(std::move(_widget));
            return ptr;
        }

        void remove_widget(const std::string& _name)
        {
            m_widgets.erase(std::remove_if(m_widgets.begin(), m_widgets.end(),
            [&_name](const UI::Widget_variant_up& widget_variant)
            {
                return std::visit([&_name](auto const& _uptr)
                {
                    return _uptr->name == _name;
                }, widget_variant);
            }), m_widgets.end());
        }

        void draw_uis()
        {
            for (const UI::Widget_variant_up& _widget : m_widgets)
                std::visit([](auto const& _wp) { UI::draw(_wp.get()); }, _widget);
        }
    private:
        UI::Canvas m_canvas;

    };

    struct UIMockUp
    {
        void init(UISystem* _ui_system)
        {

        }
    };
}

#endif
