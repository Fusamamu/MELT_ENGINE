#include "MeltEngineEditor.h"

int main()
{
    MELT::Engine _engine;
    _engine.Init();

    MELT_EDITOR::Editor _editor (&_engine);

    _engine.Update();
    _engine.Quit();

    return 0;
}
