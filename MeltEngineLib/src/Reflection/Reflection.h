#ifndef REFLECTION_H
#define REFLECTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <typeindex>

#define FIELD(name) MELT::FieldInfo{#name, offsetof(T, name), typeid(decltype(T::name))}

#define REFLECT(Type, ...)                                          \
    namespace {                                                     \
        struct Type##ReflectionRegistrar                            \
        {                                                           \
            Type##ReflectionRegistrar()                             \
            {                                                       \
                MELT::TypeInfo info;                                \
                info.name = #Type;                                  \
                using T = Type;                                     \
                info.fields = { __VA_ARGS__ };                      \
                MELT::TypeRegistry::register_type(#Type, info);     \
            }                                                       \
        };                                                          \
        static Type##ReflectionRegistrar global_##Type##_registrar; \
    }

namespace MELT
{
    struct FieldInfo
    {
        std::string name;
        size_t offset;
        std::type_index type;
    };

    struct TypeInfo
    {
        std::string name;
        std::vector<FieldInfo> fields;
    };

    class TypeRegistry {
    public:
        static void register_type(const std::string& name, const TypeInfo& info) {
            registry()[name] = info;
        }

        static const TypeInfo& get(const std::string& name) {
            return registry().at(name);
        }

        static const std::unordered_map<std::string, TypeInfo>& get_all() {
            return registry();
        }

    private:
        static std::unordered_map<std::string, TypeInfo>& registry()
        {
            static std::unordered_map<std::string, TypeInfo> instance;
            return instance;
        }
    };
}

#endif //REFLECTION_H



// #ifndef REFLECTION_H
// #define REFLECTION_H
//
// #include <string>
// #include <vector>
// #include <unordered_map>
// #include <cstddef>
// #include <typeindex>
// #include <functional>
// #include <iostream>
//
// #define FIELD(name) MELT::FieldInfo{#name, offsetof(T, name), typeid(decltype(T::name))}
//
// #define REFLECT(Type, ...)                                          \
//     namespace {                                                     \
//         struct Type##ReflectionRegistrar                            \
//         {                                                           \
//             Type##ReflectionRegistrar()                             \
//             {                                                       \
//                 MELT::TypeInfo info;                                \
//                 info.name = #Type;                                  \
//                 using T = Type;                                     \
//                 info.fields = { __VA_ARGS__ };                      \
//                 info.create_instance = []() -> void* { return new T(); }; \
//                 info.destroy_instance = [](void* ptr) { delete static_cast<T*>(ptr); }; \
//                 MELT::TypeRegistry::register_type(#Type, info);     \
//             }                                                       \
//         };                                                          \
//         static Type##ReflectionRegistrar global_##Type##_registrar; \
//     }
//
// namespace MELT
// {
//     struct FieldInfo
//     {
//         std::string name;
//         size_t offset;
//         std::type_index type;
//     };
//
//     struct TypeInfo
//     {
//         std::string name;
//         std::vector<FieldInfo> fields;
//
//         // Factory functions for dynamic creation/destruction
//         std::function<void*()> create_instance;
//         std::function<void(void*)> destroy_instance;
//     };
//
//     class TypeRegistry {
//     public:
//         static void register_type(const std::string& name, const TypeInfo& info) {
//             registry()[name] = info;
//         }
//
//         static const TypeInfo& get(const std::string& name) {
//             auto& reg = registry();
//             auto it = reg.find(name);
//             if (it == reg.end()) {
//                 throw std::runtime_error("Type not registered: " + name);
//             }
//             return it->second;
//         }
//
//         static const std::unordered_map<std::string, TypeInfo>& get_all() {
//             return registry();
//         }
//
//     private:
//         static std::unordered_map<std::string, TypeInfo>& registry()
//         {
//             static std::unordered_map<std::string, TypeInfo> instance;
//             return instance;
//         }
//     };
//
//     // Helper class to manage reflected objects lifetime
//     struct ReflectedObject {
//         void* obj = nullptr;
//         const TypeInfo* typeInfo = nullptr;
//
//         ReflectedObject(const TypeInfo* ti) : typeInfo(ti) {
//             if (typeInfo && typeInfo->create_instance)
//                 obj = typeInfo->create_instance();
//         }
//
//         ~ReflectedObject() {
//             if (obj && typeInfo && typeInfo->destroy_instance)
//                 typeInfo->destroy_instance(obj);
//         }
//
//         // Get pointer to a field by name (returns void*)
//         void* getFieldPtr(const std::string& fieldName) const {
//             if (!typeInfo || !obj) return nullptr;
//             for (const auto& field : typeInfo->fields) {
//                 if (field.name == fieldName) {
//                     return reinterpret_cast<char*>(obj) + field.offset;
//                 }
//             }
//             return nullptr;
//         }
//     };
// }
//
// #endif //REFLECTION_H

