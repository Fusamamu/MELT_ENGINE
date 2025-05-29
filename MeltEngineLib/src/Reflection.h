#pragma once
#include "Core.h"

namespace MELT
{
    struct TypeDescriptor
    {
        const char* name;
        std::size_t size;

        TypeDescriptor(const char* _name, std::size_t _size): name(_name), size(_size) { }
        virtual ~TypeDescriptor() { }
        virtual std::string GetFullName() { return name; }
        virtual void Dump(const void* _object, int _indentLevel) = 0;
    };

    template<typename T>
    TypeDescriptor* GetPrimitiveDescriptor();

    struct DefaultResolver
    {
        template<typename T>
        static char Func(decltype(&T::Reflection));

        template<typename T>
        static int Func(...);
    };
}
