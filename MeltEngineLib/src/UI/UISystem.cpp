#include "UISystem.h"

namespace MELT
{
    void UISystem::init()
    {
        FT_Library ft;

        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return;
        }

        std::string font_name = "../MeltEngineLib/res/fonts/QuartzoBold-W9lv.ttf";

        FT_Face _face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &_face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(_face, 0, 48);                // set size to load glyphs as
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);           // disable byte-alignment restriction

        for (unsigned char _c = 0; _c < 128; _c++)       // load first 128 characters of ASCII set
        {
            if (FT_Load_Char(_face, _c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            unsigned int _texture;
            glGenTextures(1, &_texture);
            glBindTexture(GL_TEXTURE_2D, _texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                _face->glyph->bitmap.width,
                _face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                _face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            UI::Character character =
            {
                _texture,
                glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                static_cast<unsigned int>(_face->glyph->advance.x)
            };
            character_map.insert(std::pair<char, UI::Character>(_c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face    (_face);
        FT_Done_FreeType(ft);
    }
}