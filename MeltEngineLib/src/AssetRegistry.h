#ifndef ASSET_REGISTRY_H
#define ASSET_REGISTRY_H

#include "Core.h"

namespace MELT
{
    template<typename T>
    struct AssetHandle
    {
        std::string guid;
        bool is_valid() const { return !guid.empty(); }
    };

    class AssetRegistry {
    public:
        template<typename T>
        void register_asset(const std::string& guid, T* asset)
        {
            auto& table = get_table<T>();
            table[guid] = asset;
        }

        template<typename T>
        T* get(const std::string& guid)
        {
            auto& table = get_table<T>();
            auto it = table.find(guid);
            if (it != table.end()) return it->second;
            return nullptr;
        }

        template<typename T>
        void unload(const std::string& guid)
        {
            auto& table = get_table<T>();
            auto it = table.find(guid);
            if (it != table.end()) {
                delete it->second;
                table.erase(it);
            }
        }

    private:
        template<typename T>
        std::unordered_map<std::string, T*>& get_table()
        {
            static std::unordered_map<std::string, T*> table;
            return table;
        }
    };
}

#endif
