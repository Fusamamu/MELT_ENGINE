#ifndef UI_H
#define UI_H

#include "Core.h"

namespace MELT::UI
{
    class Canvas;
    class Panel;
    class Button;

    using WidgetType_V = std::variant<Panel, Button>;

    using Widget_Variant_RP = std::variant
    <
        Canvas *,
        Panel  *,
        Button *
    >;

    using Widget_variant_up = std::variant
    <
        std::unique_ptr<Canvas>,
        std::unique_ptr<Panel> ,
        std::unique_ptr<Button>
    >;

    struct Rect
    {
        float x, y;
        float w, h;

        bool contains(float px, float py) const {
            return px >= x && px <= x + w && py >= y && py <= y + h;
        }
    };

    struct Color
    {
        float r = 1, g = 1, b = 1, a = 1;
    };

    template<typename T>
    concept Widget = requires(T _widget)
    {
        { _widget.draw() } -> std::same_as<void>;
        _widget.bounds;
    };

    struct WidgetBase
    {
        std::string name;

        Rect  bounds;
        Color color;

        uint32_t order;

        bool is_focused;

        std::size_t parent_idx = -1;
        std::vector<std::size_t> children_idx;

        void add_child(std::size_t _idx)
        {
            if (std::find(children_idx.begin(), children_idx.end(), _idx) == children_idx.end())
                children_idx.push_back(_idx);
        }

        void remove_child(std::size_t _idx)
        {
            children_idx.erase(
                std::remove_if(
                    children_idx.begin(), children_idx.end(),
                    [_idx](std::size_t child_idx) -> bool
                    {
                        return child_idx == _idx;
                    }),
                    children_idx.end());
        }
    };

    class Canvas : public WidgetBase
    {
    public:
        Canvas() = default;
        ~Canvas() = default;

        void draw()
        {

        }
    };

    class Button : public WidgetBase
    {
    public:
        Button() = default;
        ~Button() = default;

        void draw()
        {

        }
    private:
    };

    class Panel : public WidgetBase
    {
    public:
        Panel()  = default;
        ~Panel() = default;

        void draw()
        {

        }
    private:
    };

    template<Widget T>
    inline void draw(T _widget)
    {
        _widget.draw();
    }

    inline void draw(Widget_Variant_RP _widget)
    {
        std::visit([](auto& w)
        {
            w->draw();
        }, _widget);
    }
}

#endif
