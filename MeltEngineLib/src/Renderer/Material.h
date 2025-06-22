#ifndef MATERIAL_H
#define MATERIAL_H

#include "Core.h"
#include "Shader.h"

namespace MELT::GRAPHIC
{
    class Material
    {
    public:
        std::string name;
        Shader* p_shader;
        Material() = default;
        ~Material() = default;
    };
}

#endif //MATERIAL_H
