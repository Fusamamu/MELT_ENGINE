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
