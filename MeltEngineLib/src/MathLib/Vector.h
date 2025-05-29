#pragma once

namespace M_MATH
{
    template<typename T>
    struct vec2
    {
        T x, y, z;

        vec2();
        explicit vec2(T _x);
        explicit vec2(T _x, T _y);
        explicit vec2(T _x, T _y, T _z);
    };

    template<typename T>
    vec2<T>::vec2(): x(0), y(0), z(0)
    {

    }

    template<typename T>
    vec2<T>::vec2(T _x): x(_x), y(_x), z(_x)
    {

    }

    template<typename T>
    vec2<T>::vec2(T _x, T _y): x(_x), y(_y), z(0)
    {

    }

    template<typename T>
    vec2<T>::vec2(T _x, T _y, T _z): x(_x), y(_y), z(_z)
    {

    }


    template<typename T>
    struct vec3
    {
        T x, y, z;

        vec3();
        explicit vec3(T _x);
        explicit vec3(T _x, T _y);
        explicit vec3(T _x, T _y, T _z);
    };

    template<typename T>
    vec3<T>::vec3(): x(0), y(0), z(0)
    {

    }

    template<typename T>
    vec3<T>::vec3(T _x): x(_x), y(_x), z(_x)
    {

    }

    template<typename T>
    vec3<T>::vec3(T _x, T _y): x(_x), y(_y), z(0)
    {

    }

    template<typename T>
    vec3<T>::vec3(T _x, T _y, T _z): x(_x), y(_y), z(_z)
    {

    }
}