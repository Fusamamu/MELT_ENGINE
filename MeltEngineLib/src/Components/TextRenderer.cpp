#include "TextRenderer.h"

namespace MELT
{
    void TextRenderer::set_buffer_data()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers     (1, &m_vbo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(uintptr_t)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void TextRenderer::draw(UI::Text& _text, std::map<GLchar, UI::Character> _characters)
    {
        float x          = _text.x;
        float y          = _text.y;
        float scale      = _text.scale;
        std::string text = _text.get_text();

        glBindVertexArray(m_vao);

        std::string::const_iterator _c;

        for (_c = text.begin(); _c != text.end(); _c++)
        {
            UI::Character _character = _characters[*_c];

            float xpos = x + _character.bearing.x                       * scale;
            float ypos = y + (_character.size.y - _character.bearing.y) * scale;

            float _w = _character.size.x * scale;
            float _h = _character.size.y * scale;

            float vertices[6][4] = {
                { xpos,      ypos - _h, 0.0f, 0.0f },
                { xpos,      ypos,      0.0f, 1.0f },
                { xpos + _w, ypos,      1.0f, 1.0f },
                { xpos,      ypos - _h, 0.0f, 0.0f },
                { xpos + _w, ypos,      1.0f, 1.0f },
                { xpos + _w, ypos - _h, 1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, _character.texture_id);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (_character.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }

        glBindVertexArray(0);
    }
}
