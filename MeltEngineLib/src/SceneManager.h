#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Core.h"
#include "Scene.h"

namespace MELT
{
    class SceneManager
    {
    public:
        Scene* working_scene = nullptr;
        std::unordered_map<std::string, std::unique_ptr<Scene>> scene_table;

        SceneManager()  = default;
        ~SceneManager() = default;

        void init();

        Scene* create_scene(const std::string& _scene_name);
        Scene* get_scene   (const std::string& name);

        bool set_active_scene(const std::string& name);
    };
}

#endif
