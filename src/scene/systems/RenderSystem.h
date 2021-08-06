#ifndef RPG_RENDERSYSTEM_H
#define RPG_RENDERSYSTEM_H

#include <entt.hpp>
#include "../../client/graphics/SpriteBatch.h"
#include "../components/TransformComponent.h"

class RenderSystem
{
    entt::registry& m_registry;
    Shader m_shader;
    SpriteBatch m_batch;
public:
    RenderSystem(entt::registry& registry);

    void draw();

    void destroy();
};

#endif //RPG_RENDERSYSTEM_H
