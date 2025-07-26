#ifndef TEXT_H
#define TEXT_H

#include "Core.h"

namespace MELT::UI
{
    struct Character
    {
        unsigned int texture_id;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };

    class Text
    {
    public:
        float x, y;
        float scale;

        M_VEC4 color;

        Text() = default;
        ~Text() = default;

        void set_text(const std::string& _text){ m_text = _text; }
        std::string get_text() { return m_text; }
    private:
        std::string m_text;
    };
}

#endif //TEXT_H
