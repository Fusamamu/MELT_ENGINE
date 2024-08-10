#include "MeltEngineEditor.h"

int main()
{


    MELT::Engine _engine;
    MELT_EDITOR::Editor _editor (&_engine);

    _engine.Init();
    _engine.Update();
    _engine.Quit();

    //MELT::Shader _s("../MeltEngineLib/res/shaders/Basic.shader");

    //std::cout << _s << std::endl;

    return 0;
}
