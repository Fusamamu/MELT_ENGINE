#include "MeltEngineEditor.h"
//#include <dlfcn.h>

//#include "Project/Scripts/TestCustomSystem.h"
//
//typedef TestCustomSystem* (*CreateMyClassFunc)();

int main()
{


    MELT::Engine _engine;
    _engine.Init();
    MELT_EDITOR::Editor _editor (&_engine);



//    std::cout << "Hello, World!" << std::endl;
//
//    void* _handle = dlopen("./Project/libCustomNativeScript.dylib", RTLD_LAZY);
//
//    if (!_handle) {
//        std::cerr << "Failed to load library: " << dlerror() << std::endl;
//        return 1;
//    }
//
//
//
//    CreateMyClassFunc createMyClass = (CreateMyClassFunc)dlsym(_handle, "CreateCustomSystem");
//    if (!createMyClass) {
//        std::cerr << "Failed to load function: " << dlerror() << std::endl;
//        dlclose(_handle);
//        return 1;
//    }
//
//    // Create the object
//    TestCustomSystem* obj = createMyClass();
//    obj->OnStart();
//    obj->OnInputUpdate(0.0f);



    // Clean up
//    delete obj;
//
//    dlclose(_handle);







    _engine.Update();
    _engine.Quit();
    return 0;
}
