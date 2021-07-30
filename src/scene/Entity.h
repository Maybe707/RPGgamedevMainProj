#ifndef RPG_ENTITY_H
#define RPG_ENTITY_H

#include <entt.hpp>
#include "Scene.h"

class Entity
{
    entt::entity m_entity{entt::null};
    Scene *m_scene = nullptr;

public:
    Entity() = default;

    Entity(entt::entity entity, Scene *scene);

    template<typename T, typename... Args>
    T &addComponent(Args &&... args)
    {
        return m_scene->m_registry.emplace<T>(m_entity, std::forward<Args>(args)...);
    }

    template<typename T>
    T &getComponent()
    {
        return m_scene->m_registry.get<T>(m_entity);
    }

    template<typename T>
    bool hasComponent()
    {
        return m_scene->m_registry.all_of<T>(m_entity);
    }

    template<typename T>
    void removeComponent()
    {
        m_scene->m_registry.remove<T>(m_entity);
    }

    operator bool() const { return m_entity != entt::null; }

    friend class Scene;
};

#endif //RPG_ENTITY_H
