#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Core.h"
#include "Text.h"

namespace MELT
{
    class UISystem
    {
	public:
          std::map<GLchar, UI::Character> character_map;

          UISystem() = default;
          ~UISystem() = default;

          void init();
    private:
    };
}

#endif
