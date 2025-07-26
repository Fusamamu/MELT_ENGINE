#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "Core.h"
#include "Text.h"

namespace MELT
{
    class TextRenderer
    {
    public:
        TextRenderer() = default;
        ~TextRenderer() = default;

        void set_buffer_data();
        void draw(UI::Text& _text);
    private:
        unsigned int m_vao, m_vbo;
    };

}

#endif
