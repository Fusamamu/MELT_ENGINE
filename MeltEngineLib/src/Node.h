#pragma once
#include "Core.h"
#include "Type.h"
#include "Scene.h"

namespace MELT
{
    using NodeID = std::string;

    class Node
    {
    public:
        MELT::Entity entityRef;//will remove this

        NodeID id;
        std::string name;
        glm::vec3 position;

        bool isSelected;

        Node(const std::string& _name, Scene* _scene_owner, entt::entity _entity);
        Node(std::string _name, M_VEC3 _position);
        Node();
        ~Node();

        [[nodiscard]]
        entt::entity get_entity() const {
            return m_entity_handle;
        }
        template<typename T, typename... Args>
        T& add_component(Args&... _args){
            return m_scene_owner->ecs_registry.emplace<T>(m_entity_handle, std::forward<Args>(_args)...);
        }
        template<typename T>
        void remove_component() {
            m_scene_owner->ecs_registry.remove<T>(m_entity_handle);
        }
        template<typename T>
        T& get_component(){
            return m_scene_owner->ecs_registry.get<T>(m_entity_handle);
        }
        template<typename T>
        [[nodiscard]]
        bool has_component() const{
            return m_scene_owner->ecs_registry.all_of<T>(m_entity_handle);
        }

        explicit operator bool() const { return m_entity_handle != entt::null; }
    private:
        Scene* m_scene_owner;
        entt::entity m_entity_handle;
    };
}