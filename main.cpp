#include "MeltEngineEditor.h"

#include <dlfcn.h>
#include "Project/Scripts/TestCustomSystem.h"

typedef TestCustomSystem* (*CreateMyClassFunc)();

int main()
{


    MELT::Engine _engine;
    _engine.Init();
    MELT_EDITOR::Editor _editor (&_engine);





//    void* _handle = dlopen("./Project/libCustomNativeScript.dylib", RTLD_LAZY);
//    if (!_handle) {
//        std::cerr << "Failed to load library: " << dlerror() << std::endl;
//        return 1;
//    }
//
//    CreateMyClassFunc createMyClass = (CreateMyClassFunc)dlsym(_handle, "CreateCustomSystem");
//    if (!createMyClass) {
//        std::cerr << "Failed to load function: " << dlerror() << std::endl;
//        dlclose(_handle);
//        return 1;
//    }
//
////    TestCustomSystem* obj = createMyClass();
////    obj->OnStart();
////    obj->OnInputUpdate(0.0f);
//
//
//    auto _cameraControlSystem = _engine.ECSCoord.RegisterSystem<TestCustomSystem>();
//    {
//        MELT::Signature _signature;
//        _signature.set(_engine.ECSCoord.GetComponentType<MELT::Transform>());
//        _engine.ECSCoord.SetSystemSignature<TestCustomSystem>(_signature);
//    }
//    _cameraControlSystem->OnStart();





    _engine.Update();
    _engine.Quit();

//    delete obj;
//    dlclose(_handle);

    return 0;
}
