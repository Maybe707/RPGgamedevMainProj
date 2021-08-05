#include "Game.h"

#include "scene/Entity.h"
#include "scene/components/CameraComponent.h"
#include "scene/components/NativeScriptComponent.h"
#include "scene/components/SpriteRendererComponent.h"
#include "scene/components/TextRendererComponent.h"
#include "scene/components/TileMapComponent.h"
#include "scene/Hierarchy.h"

#include "scripts/PlayerScript.h"
#include "scripts/TextScript.h"
#include "scripts/DebugInfoScript.h"
#include "scripts/WorldGenScript.h"

Game::Game()
        : m_font("../res/fonts/vt323.ttf", 32),
          m_heroTexture(Texture::create("../res/textures/hero.png")),
          m_baseTexture(Texture::create("../res/textures/base.png"))
{
    m_pallet.setTexture(&m_baseTexture);
    m_pallet.setCellSize({32.f, 32.f});
    m_pallet.setCellOrigin({16.f, 16.f});
    m_pallet.setCellScale({2.f, 2.f});

    m_pallet.addTile({160, 4256 - 32});
    m_pallet.addTile({64, 4256 - 64});
    m_pallet.addTile({192, 4256 - 32});
    m_pallet.addTile({96, 4256 - 32});

    m_cameraEntity = m_scene.createEntity("camera");
    m_cameraEntity.addComponent<CameraComponent>();


    Entity tileMapEntity = m_scene.createEntity("TileMapComponent");
    auto& tileMap = tileMapEntity.addComponent<TileMapComponent>(IntRect(-10, -10, 10, 10));
    tileMap.setTilePallet(&m_pallet);
    tileMapEntity.addComponent<NativeScriptComponent>().bind<WorldGenScript>();


    // Создание текста
    Entity textEntity = m_scene.createEntity("text");
    auto &textRenderer = textEntity.addComponent<TextRendererComponent>(&m_font, "True RPG!\n Welcome!");

    // Некоторые настройки текста для примера
    textRenderer.horizontalAlign = HorizontalAlign::Center;
    textRenderer.verticalAlign = VerticalAlign::Top;

    // Биндим скрипт к энтити и передаем туда камеру
    textEntity.addComponent<NativeScriptComponent>().bind<TextScript>(m_cameraEntity);


    // Создание fps счетчика
    Entity debugInfoEntity = m_scene.createEntity("debugInfo");
    debugInfoEntity.addComponent<TextRendererComponent>(&m_font, "");
    auto &fpsTransform = debugInfoEntity.getComponent<TransformComponent>();
    fpsTransform.scale = glm::vec2(0.8f, 0.8f);
    debugInfoEntity.addComponent<NativeScriptComponent>().bind<DebugInfoScript>(m_cameraEntity);


    // Создание игрока
    Entity playerEntity = m_scene.createEntity("player");
    auto &playerTransform = playerEntity.getComponent<TransformComponent>();
    playerTransform.position = glm::vec2(0.0f, 0.0f);

    Entity spriteEntity = m_scene.createEntity("sprite");
    auto &heroRenderer = spriteEntity.addComponent<SpriteRendererComponent>(m_heroTexture);
    heroRenderer.textureRect = IntRect(32, 96, 32, 32);

    auto &heroTransform = spriteEntity.getComponent<TransformComponent>();
    heroTransform.scale = glm::vec2(2.f, 2.f);
    heroTransform.origin = glm::vec2(16, 16);

    // Крепим к игроку спрайт, текст и камеру
    Hierarchy::addChild(playerEntity, spriteEntity);
    Hierarchy::addChild(playerEntity, textEntity);
    Hierarchy::addChild(playerEntity, debugInfoEntity);
    Hierarchy::addChild(playerEntity, m_cameraEntity);

    // Биндим скрипт к игроку
    playerEntity.addComponent<NativeScriptComponent>().bind<PlayerScript>();
}

void Game::update(float deltaTime)
{
    m_scene.update(deltaTime);
}

void Game::destroy()
{
    m_scene.destroy();
    m_font.destroy();
    m_heroTexture.destroy();
    m_baseTexture.destroy();
}
