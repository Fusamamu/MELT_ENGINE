#include "MeltEngineEditor.h"
#include "Project/Scripts/TestCustomSystem.h"

typedef TestCustomSystem* (*CreateMyClassFunc)();

int main()
{
    MELT_EDITOR::Editor _editor;
    _editor.init();
    _editor.update();
    _editor.quit();
    return 0;
}
