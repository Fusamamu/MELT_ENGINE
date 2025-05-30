// #pragma once
// #include "Scene.h"
//
// template<typename T, typename... Args>
//     T& Node::add_component(Args&&... _args){
//     return m_scene_owner->ecs_registry.emplace<T>(m_entity_handle, std::forward<Args>(_args)...);
// }
//
// template<typename T>
// void Node::remove_component() {
//     m_scene_owner->ecs_registry.remove<T>(m_entity_handle);
// }
//
// template<typename T>
// T& Node::get_component(){
//     return m_scene_owner->ecs_registry.get<T>(m_entity_handle);
// }
//
// template<typename T>
// [[nodiscard]]
// bool Node::has_component() const {
//     return m_scene_owner->ecs_registry.all_of<T>(m_entity_handle);
// }
//
