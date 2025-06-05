#ifndef HELLOWORLD_H
#define HELLOWORLD_H
#include <iostream>

#include "MELT.h"

struct Foo
{
    float x;
};

REFLECT(Foo,
    FIELD(x)
)

extern "C" void hello_from_dylib();

#endif
