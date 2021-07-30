#ifndef RPG_SCENE_H
#define RPG_SCENE_H

#include <entt.hpp>
#include "../graphics/SpriteBatch.h"

#include "systems/ScriptSystem.h"
#include "systems/RenderSystem.h"

class Entity;

class Scene
{
    entt::registry m_registry;

    ScriptSystem m_scriptSystem;
    RenderSystem m_renderSystem;
public:
    Scene();

    Entity createEntity(const std::string& name = "");

    void destroyEntity(Entity entity);

    void update(float deltaTime);

    void destroy();

    friend class Entity;
};

#endif //RPG_SCENE_H
