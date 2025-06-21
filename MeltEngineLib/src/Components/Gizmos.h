#ifndef GIZMOS_H
#define GIZMOS_H

namespace MELT
{
    struct Gizmos
    {
        enum class Type
        {
            NONE,
            LIGHT,
            CAMERA,
        };

        Gizmos::Type type = Gizmos::Type::NONE;

        Gizmos(const Gizmos::Type& _type): type(_type) {}
        Gizmos () = default;
        ~Gizmos() = default;
    };

}

#endif //GIZMOS_H
