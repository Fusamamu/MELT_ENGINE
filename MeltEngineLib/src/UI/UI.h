#ifndef UI_H
#define UI_H

namespace MELT
{
    class I_UIElement
    {
    public:
        ~I_UIElement() = default;
        virtual void init();
        virtual void draw() const = 0;
        virtual void destroy();

        virtual void set_size(float _w, float _h);
        virtual float get_width () const = 0;
        virtual float get_height() const = 0;
    };

    class Panel : public I_UIElement
    {
    public:
        Panel() = default;

        void init() override
        {
        }

        void draw() const override
        {

        }

        void destroy() override
        {

        }

        void set_size(float _w, float _h)
        {
            m_w = _w;
            m_h = _h;
        }

        float get_width () const override
        {
            return m_w;
        }

        float get_height() const override
        {
            return m_h;
        }

    protected:
        float m_w;
        float m_h;
    };
}

#endif
