#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Core.h"
#include "Text.h"

namespace MELT::UI
{
    class UISystem
    {
	public:
          UISystem() = default;
          ~UISystem() = default;

          void init();
    private:
          std::map<GLchar, Character> m_characters;
    };
}

#endif
