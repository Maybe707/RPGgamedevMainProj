#ifndef RPG_SCENE_H
#define RPG_SCENE_H

#include <entt.hpp>
#include "../graphics/SpriteBatch.h"

class Entity;
class TransformComponent;

class Scene
{
    entt::registry m_registry;

    Shader m_shader;
    SpriteBatch m_batch;
public:
    Scene();

    Entity createEntity(const std::string& name = "");

    void destroyEntity(Entity entity);

    void update(float deltaTime);

    void destroy();

    friend class Entity;

private:
    TransformComponent computeTransform(entt::entity entity);
};

#endif //RPG_SCENE_H
