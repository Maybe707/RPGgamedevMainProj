#include "Scene.h"

#include "Entity.h"
#include "Components.h"
#include "../graphics/Text.h"

Scene::Scene()
        : m_shader(Shader::createShader("../res/shaders/shader.vs", "../res/shaders/shader.fs")),
          m_batch(m_shader) {}

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
    // Уничтожаем скрипт
    auto& nativeScriptComponent = entity.getComponent<NativeScriptComponent>();
    if (!nativeScriptComponent.instance)
    {
        nativeScriptComponent.onDestroyFunction(nativeScriptComponent.instance);
        nativeScriptComponent.destroyInstanceFunction();
    }
    m_registry.destroy(entity.m_entity);
}

// TODO: наверное стоит разбить код из этого метода на отдельные системы
void Scene::update(float deltaTime)
{
    // Обновление скриптов
    {
        auto view = m_registry.view<NativeScriptComponent>();
        for (auto entity : view)
        {
            auto& nativeScriptComponent = view.get<NativeScriptComponent>(entity);
            if (!nativeScriptComponent.instance)
            {
                nativeScriptComponent.instantiateFunction();
                nativeScriptComponent.instance->m_entity = Entity(entity, this);
                nativeScriptComponent.onCreateFunction(nativeScriptComponent.instance);
            }

            nativeScriptComponent.onUpdateFunction(nativeScriptComponent.instance, deltaTime);
        }
    }

    // Находим камеру
    Camera2D* camera = nullptr;
    {
        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            auto transformComponent = computeTransform(entity);
            camera = cameraComponent.camera;
            camera->setPosition(-transformComponent.position);
        }
    }
    if (camera != nullptr)
    {
        m_batch.setProjectionMatrix(camera->getProjectionMatrix());
        m_batch.setViewMatrix(camera->getViewMatrix());
        m_batch.begin();

        // Рендеринг спрайтов
        {
            auto view = m_registry.view<SpriteRendererComponent>();
            for (auto entity : view)
            {
                auto &spriteComponent = view.get<SpriteRendererComponent>(entity);
                Sprite sprite(spriteComponent.texture);
                sprite.setTextureRect(spriteComponent.textureRect);
                sprite.setColor(spriteComponent.color);

                auto transformComponent = computeTransform(entity);

                sprite.setPosition(transformComponent.position);
                sprite.setOrigin(transformComponent.origin);
                sprite.setScale(transformComponent.scale);

                m_batch.draw(sprite);
            }
        }

        // Рендеринг текста
        {
            auto view = m_registry.view<TextRendererComponent>();
            for (auto entity : view)
            {
                auto &textComponent = view.get<TextRendererComponent>(entity);
                Text text(*textComponent.font, textComponent.text);
                text.setColor(textComponent.color);

                auto transformComponent = computeTransform(entity);

                text.setPosition(transformComponent.position);
                FloatRect localBound = text.getLocalBounds();
                glm::vec2 textOrigin = transformComponent.origin;
                if (textComponent.horizontalAlign == HorizontalAlign::Center) {
                    textOrigin += glm::vec2(localBound.getWidth() / 2, 0.f);
                }
                if (textComponent.horizontalAlign == HorizontalAlign::Right) {
                    textOrigin += glm::vec2(localBound.getWidth(), 0.f);
                }
                if (textComponent.verticalAlign == VerticalAlign::Center) {
                    textOrigin += glm::vec2(0.f, localBound.getHeight() / 2);
                }
                if (textComponent.verticalAlign == VerticalAlign::Top) {
                    textOrigin += glm::vec2(0.f, localBound.getHeight());
                }
                text.setOrigin(textOrigin);
                text.setScale(transformComponent.scale);

                text.draw(m_batch);
            }
        }

        m_batch.end();
    }
}

void Scene::destroy()
{
    // Уничтожаем все скрипты
    auto view = m_registry.view<NativeScriptComponent>();
    for (auto entity : view)
    {
        auto& nativeScriptComponent = view.get<NativeScriptComponent>(entity);
        if (nativeScriptComponent.instance)
        {
            nativeScriptComponent.onDestroyFunction(nativeScriptComponent.instance);
            nativeScriptComponent.destroyInstanceFunction();
        }
    }
    m_shader.destroy();
    m_batch.destroy();
}

TransformComponent Scene::computeTransform(entt::entity entity)
{
    auto entityTransform = m_registry.get<TransformComponent>(entity);

    auto &entityHierarchy = m_registry.get<HierarchyComponent>(entity);
    auto current = entityHierarchy.parent;

    while(current) {
        auto currentTransform = current.getComponent<TransformComponent>();
        entityTransform.position += currentTransform.position;
        entityTransform.origin += currentTransform.origin;
        entityTransform.scale *= currentTransform.scale;

        current = current.getComponent<HierarchyComponent>().parent;
    }

    return entityTransform;
}
