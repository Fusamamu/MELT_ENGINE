#ifndef MELT_H
#define MELT_H

#include "Reflection.h"

namespace MELT
{
    struct CustomComponent
    {
        float x;
    };
    void MeltHello();

    void reflect_CustomComponent();

    template<typename T>
    void reflect_type(const char* name);
}

#endif
