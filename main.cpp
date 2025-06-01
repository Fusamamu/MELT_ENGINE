#include "MeltEngineEditor.h"

#include "Project/Scripts/TestCustomSystem.h"

typedef TestCustomSystem* (*CreateMyClassFunc)();

int main()
{
    MELT::Engine _engine;
    _engine.init();
    MELT_EDITOR::Editor _editor (&_engine);
    _engine.Update();
    _engine.Quit();
    return 0;
}
