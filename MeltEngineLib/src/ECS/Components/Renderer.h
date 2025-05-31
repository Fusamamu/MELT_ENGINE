#ifndef RENDERER_H
#define RENDERER_H

#include "Core.h"

namespace MELT
{
    struct Renderer
    {
        M_VEC3 position;
        M_VEC3 rotation;
        M_VEC3 scale;

        Renderer () = default;
        ~Renderer() = default;
    };
}

#endif
