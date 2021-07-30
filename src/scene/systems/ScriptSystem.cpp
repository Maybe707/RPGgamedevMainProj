#include "ScriptSystem.h"

#include "../components/NativeScriptComponent.h"

ScriptSystem::ScriptSystem(entt::registry &registry, Scene *scene)
        : m_registry(registry), m_scene(scene) {}

void ScriptSystem::update(float deltaTime)
{
    // Обновляем все скрипты
    auto view = m_registry.view<NativeScriptComponent>();
    for (auto entity : view)
    {
        auto &nativeScriptComponent = view.get<NativeScriptComponent>(entity);

        // Если они еще не были созданы, то создаем
        if (!nativeScriptComponent.instance)
        {
            nativeScriptComponent.instantiateFunction();
            nativeScriptComponent.instance->m_entity = Entity(entity, m_scene);
            nativeScriptComponent.onCreateFunction(nativeScriptComponent.instance);
        }

        nativeScriptComponent.onUpdateFunction(nativeScriptComponent.instance, deltaTime);
    }
}

void ScriptSystem::destroyScript(entt::entity entity)
{
    // Уничтожаем скрипт
    auto &nativeScriptComponent = m_registry.get<NativeScriptComponent>(entity);
    if (!nativeScriptComponent.instance)
    {
        nativeScriptComponent.onDestroyFunction(nativeScriptComponent.instance);
        nativeScriptComponent.destroyInstanceFunction();
    }
}

void ScriptSystem::destroy()
{
    // Уничтожаем все скрипты
    auto view = m_registry.view<NativeScriptComponent>();
    for (auto entity : view)
    {
        auto &nativeScriptComponent = view.get<NativeScriptComponent>(entity);
        if (nativeScriptComponent.instance)
        {
            nativeScriptComponent.onDestroyFunction(nativeScriptComponent.instance);
            nativeScriptComponent.destroyInstanceFunction();
        }
    }
}
