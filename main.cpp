#include "MeltEngineEditor.h"

int main()
{
    MELT::Engine _engine;
    MELT_EDITOR::Editor _editor (&_engine);

    _engine.Init();
    _engine.Update();
    _engine.Quit();

    return 0;
}
