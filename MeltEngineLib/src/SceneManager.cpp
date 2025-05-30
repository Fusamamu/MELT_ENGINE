#include "SceneManager.h"

namespace MELT
{
    void SceneManager::init()
    {
        working_scene = create_scene("sample scene");
        working_scene->is_active = true;
    }

    Scene* SceneManager::create_scene(const std::string& name)
    {
        auto [it, inserted] = scene_table.try_emplace(name, std::make_unique<Scene>());
        return it->second.get();
    }

    Scene* SceneManager::get_scene(const std::string& name)
    {
        auto it = scene_table.find(name);
        if (it != scene_table.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    bool SceneManager::set_active_scene(const std::string& name)
    {
        auto it = scene_table.find(name);
        if (it != scene_table.end()) {
            working_scene = it->second.get();
            return true;
        }
        return false;
    }
}