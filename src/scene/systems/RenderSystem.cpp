#include "RenderSystem.h"

#include <entt.hpp>
#include "../../graphics/Text.h"
#include "../components/CameraComponent.h"
#include "../components/TileMapComponent.h"
#include "../components/SpriteRendererComponent.h"
#include "../components/TextRendererComponent.h"
#include "../components/HierarchyComponent.h"

RenderSystem::RenderSystem(entt::registry &registry)
        : m_registry(registry),
          m_shader(Shader::createShader("../res/shaders/shader.vs", "../res/shaders/shader.fs")),
          m_batch(m_shader, 30000) {}

void RenderSystem::draw()
{
    // TODO: Пока не очень понятно, как быть с приоритетом отрисовки.
    //  Например, если нам нужно нарисовать спрайт поверх текста.

    // Находим камеру
    Camera2D *camera = nullptr;
    {
        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto &cameraComponent = view.get<CameraComponent>(entity);
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

        // TODO: доделать. Скорее всего переделать весь.
        // Рендеринг карты тайлов
        {
            auto view = m_registry.view<TileMap>();
            for (auto entity : view)
            {
                auto &tilemapComponent = view.get<TileMap>(entity);
                for (auto &chunkPair : tilemapComponent.chunks)
                {
                    auto &chunk = chunkPair.second;
                    for (size_t y = 0; y < CHUNK_SIZE; y++)
                    {
                        for (size_t x = 0; x < CHUNK_SIZE; x++)
                        {
                            u8 tileId = chunk.getTile({x, y});
                            if (tileId == 0) continue;

                            auto &tileSprite = TilesData.at(tileId)->getSprite();
                            int realX = chunk.getPosition().x * CHUNK_SIZE + x;
                            int realY = chunk.getPosition().y * CHUNK_SIZE + y;

                            tileSprite.setPosition({
                                                           realX * tileSprite.getGlobalBounds().getWidth(),
                                                           realY * tileSprite.getGlobalBounds().getHeight()
                                                   });

                            m_batch.draw(tileSprite);
                        }
                    }
                }
            }
        }

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
                if (textComponent.horizontalAlign == HorizontalAlign::Center)
                {
                    textOrigin += glm::vec2(localBound.getWidth() / 2, 0.f);
                }
                if (textComponent.horizontalAlign == HorizontalAlign::Right)
                {
                    textOrigin += glm::vec2(localBound.getWidth(), 0.f);
                }
                if (textComponent.verticalAlign == VerticalAlign::Center)
                {
                    textOrigin += glm::vec2(0.f, localBound.getHeight() / 2);
                }
                if (textComponent.verticalAlign == VerticalAlign::Top)
                {
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

void RenderSystem::destroy()
{
    m_batch.destroy();
    m_shader.destroy();
}

TransformComponent RenderSystem::computeTransform(entt::entity entity)
{
    auto entityTransform = m_registry.get<TransformComponent>(entity);

    auto &entityHierarchy = m_registry.get<HierarchyComponent>(entity);
    auto current = entityHierarchy.parent;

    while (current)
    {
        auto currentTransform = current.getComponent<TransformComponent>();
        entityTransform.position += currentTransform.position;
        entityTransform.origin += currentTransform.origin;
        entityTransform.scale *= currentTransform.scale;

        current = current.getComponent<HierarchyComponent>().parent;
    }

    return entityTransform;
}
