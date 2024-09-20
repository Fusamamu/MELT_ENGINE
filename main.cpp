#include "MeltEngineEditor.h"

#include <fstream>


int main()
{


    MELT::Engine _engine;
    MELT_EDITOR::Editor _editor (&_engine);

    std::ifstream _inputFile("CMakeCache.txt");

    if(_inputFile.good())
    {
        std::cout << "good" << std::endl;
    }else
    {
        std::cout << "bad" << std::endl;
    }

    _inputFile.close();

    //MELT::Quad _a;

    _engine.Init();
    _engine.Update();
    _engine.Quit();

    //MELT::Shader _s("../MeltEngineLib/res/shaders/Basic.shader");
    //std::cout << _s << std::endl;

    return 0;
}
