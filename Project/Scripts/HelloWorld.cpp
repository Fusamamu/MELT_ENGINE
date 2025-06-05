#include "HelloWorld.h"

void hello_from_dylib()
{
    std::cout << "Hello from dynamic library! again" << std::endl;
    MELT::MeltHello();

    // const auto& info = MELT::TypeRegistry::get("Foo");
    //
    // for (const MELT::FieldInfo& field : info.fields) {
    //     std::cout << "Field: " << field.name
    //               << ", offset: " << field.offset
    //               << ", type: " << field.type.name() << "\n";
    // }
}