#ifndef ASSET_REGISTRY_H
#define ASSET_REGISTRY_H

#include "Core.h"

namespace MELT
{
    class AssetRegistry;

    template<typename T>
    struct AssetHandle
    {
        UUID uuid;

        bool is_valid() const { return !uuid.empty(); }

        T* get() const;
        std::string get_name() const;
    };

    struct AssetMetadata
    {
        UUID uuid;
        std::string name;
        std::string path;
        // std::vector<std::string> tags;
        // std::string import_time;
    };

    class AssetRegistry {
    public:
        static AssetRegistry& instance()
        {
            static AssetRegistry _instance;
            return _instance;
        }

        AssetRegistry(const AssetRegistry&) = delete;
        AssetRegistry& operator=(const AssetRegistry&) = delete;
        
        template<typename T>
        void register_asset(const std::string& _guid, T* _asset)
        {
            std::unordered_map<UUID, T*>& _table = get_table<T>();
            _table[_guid] = _asset;
        }

        template<typename T>
        void register_asset(const AssetMetadata& meta, T* asset)
        {
            std::unordered_map<UUID, T*>& table = get_table<T>();
            auto& meta_table = get_metadata_table<T>();

            table     [meta.uuid] = asset;
            meta_table[meta.uuid] = meta;
        }

        template<typename T>
        T* get(const UUID& guid)
        {
            std::unordered_map<UUID, T*>& _table = get_table<T>();
            auto it = _table.find(guid);
            if (it != _table.end())
                return it->second;
            return nullptr;
        }

        template<typename T>
        T* get(const AssetHandle<T>& _asset_handle)
        {
            std::unordered_map<UUID, T*>& _table = get_table<T>();
            auto it = _table.find(_asset_handle.uuid);
            if (it != _table.end())
                return it->second;
            return nullptr;
        }

        template<typename T>
        T* get_by_name(const std::string& name)
        {
            const auto& meta_table = get_metadata_table<T>();
            for (const auto& [uuid, meta] : meta_table)
            {
                if (meta.name == name)
                    return get<T>(uuid);
            }
            return nullptr;
        }

        template<typename T>
        const AssetMetadata& get_meta_by_name(const std::string& _name) const
        {
            const auto& meta_table = get_metadata_table<T>();
            for (const auto& [uuid, meta] : meta_table)
            {
                if (meta.name == _name)
                    return meta;
            }
            return AssetMetadata();
        }

        template<typename T>
        T* get_by_path(const std::string& path)
        {
            const auto& meta_table = get_metadata_table<T>();
            for (const auto& [uuid, meta] : meta_table)
            {
                if (meta.path == path)
                    return get<T>(uuid);
            }
            return nullptr;
        }

#pragma region Handle
        template<typename T>
        AssetHandle<T> get_handle_by_name(const std::string& name)
        {
            const auto& meta_table = get_metadata_table<T>();
            for (const auto& [uuid, meta] : meta_table)
            {
                if (meta.name == name)
                    return AssetHandle<T>{ uuid };
            }
            return {};
        }

        template<typename T>
        AssetHandle<T> get_handle_by_path(const std::string& path)
        {
            const auto& meta_table = get_metadata_table<T>();
            for (const auto& [uuid, meta] : meta_table)
            {
                if (meta.path == path)
                    return AssetHandle<T>{ uuid };
            }
            return {};
        }

        template<typename T>
        std::vector<AssetHandle<T>> get_all_handles()
        {
            std::vector<AssetHandle<T>> handles;
            const auto& meta_table = get_metadata_table<T>();
            for (const auto& [uuid, _] : meta_table)
                handles.emplace_back(AssetHandle<T>{ uuid });
            return handles;
        }
#pragma endregion


        template<typename T>
        void rename_asset(const UUID& uuid, const std::string& new_name)
        {
            auto& meta_table = get_metadata_table<T>();
            if (auto it = meta_table.find(uuid); it != meta_table.end())
            {
                it->second.name = new_name;
            }
        }

        template<typename T>
        void unload(const UUID& guid)
        {
            std::unordered_map<UUID, T*>& _table = get_table<T>();
            auto it = _table.find(guid);
            if (it != _table.end())
            {
                delete it->second;
                _table.erase(it);
            }
        }

        template<typename T>
        void unload(const AssetHandle<T>& _asset_handle)
        {
            std::unordered_map<UUID, T*>& _table = get_table<T>();
            auto it = _table.find(_asset_handle.uuid);
            if (it != _table.end())
            {
                delete it->second;
                _table.erase(it);
            }
        }

        template<typename T>
        std::vector<std::string> get_all_names()
        {
            std::vector<std::string> names;
            std::unordered_map<UUID, AssetMetadata>& meta_table = get_metadata_table<T>();
            for (const auto& [_uuid, _meta_data] : meta_table)
                names.push_back(_meta_data.name);
            return names;
        }

        template<typename T>
        static std::unordered_map<UUID, AssetMetadata>& get_metadata_table()
        {
            static std::unordered_map<UUID, AssetMetadata> meta_table;
            return meta_table;
        }
    private:
        AssetRegistry() = default;
        ~AssetRegistry() = default;

        // Static table per asset type
        template<typename T>
        static std::unordered_map<UUID, T*>& get_table()
        {
            static std::unordered_map<UUID, T*> table;
            return table;
        }

    };

    template<typename T>
    T* AssetHandle<T>::get() const
    {
        return AssetRegistry::instance().get<T>(uuid);
    }

    template<typename T>
    std::string AssetHandle<T>::get_name() const
    {
        auto& _meta_table = AssetRegistry::get_metadata_table<T>();
        auto _it = _meta_table.find(uuid);
        if (_it != _meta_table.end())
            return _it->second.name;
        return "";
    }
}

#endif
