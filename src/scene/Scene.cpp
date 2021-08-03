#include "Scene.h"

#include "Entity.h"
#include "components/HierarchyComponent.h"
#include "components/NameComponent.h"

Scene::Scene()
        : m_scriptSystem(m_registry, this),
          m_renderSystem(m_registry) {}

Entity Scene::createEntity(const std::string &name)
{
    Entity entity(m_registry.create(), this);
    // Добавляем обязательные компоненты, которые должны быть у всех энитити
    entity.addComponent<TransformComponent>();
    entity.addComponent<HierarchyComponent>();
    auto &nameComponent = entity.addComponent<NameComponent>();
    nameComponent.name = name.empty() ? "Entity" : name;
    return entity;
}

void Scene::destroyEntity(Entity entity)
{
    m_scriptSystem.destroyScript(entity.m_entity);
    m_registry.destroy(entity.m_entity);
}

void Scene::update(float deltaTime)
{
    m_scriptSystem.update(deltaTime);
    m_renderSystem.draw();
}

void Scene::destroy()
{
    m_scriptSystem.destroy();
    m_renderSystem.destroy();
}
