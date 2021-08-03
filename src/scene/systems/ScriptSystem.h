#ifndef RPG_SCRIPTSYSTEM_H
#define RPG_SCRIPTSYSTEM_H

#include <entt.hpp>

class Scene;

class ScriptSystem
{
    entt::registry &m_registry;
    Scene *m_scene;
public:
    ScriptSystem(entt::registry &registry, Scene *scene);

    void update(float deltaTime);

    void destroyScript(entt::entity entity);

    void destroy();
};

#endif //RPG_SCRIPTSYSTEM_H
