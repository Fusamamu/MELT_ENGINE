#include <iostream>
#include "MeltEngine.h"

int main()
{
    MELT::Engine _engine;
    _engine.Init();
    _engine.Update();
    _engine.Quit();

    return 0;
}
