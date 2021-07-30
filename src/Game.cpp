#include "Game.h"

#include "scene/Entity.h"
#include "scene/Components.h"
#include "scene/TileMapComponent.h"
#include "scene/Hierarchy.h"

#include "scripts/PlayerScript.h"
#include "scripts/TextScript.h"
#include "scripts/FPSCounterScript.h"
#include "scripts/WorldGenScript.h"

Game::Game()
        : m_font("../res/fonts/vt323.ttf", 32),
          m_heroTexture(Texture::create("../res/textures/hero.png"))
{
    // TODO: Пока с камерой работаем так, потому что нужно поддерживать старый говнокод.
    //  Когда полностью переедем на ecs, нужно будет сделать нормальный компонент
    m_camera = Camera2D(glm::vec2(0), 800, 800);
    Entity cameraEntity = m_scene.createEntity("camera");
    cameraEntity.addComponent<CameraComponent>().camera = &m_camera;

    Entity tileMapEntity = m_scene.createEntity("TileMap");
    auto& tileMap = tileMapEntity.addComponent<TileMapComponent>(IntRect(-3, -3, 3, 3));
    tileMapEntity.addComponent<NativeScriptComponent>().bind<WorldGenScript>();

    // Создание текста
    m_textEntity = m_scene.createEntity("text");
    auto &textRenderer = m_textEntity.addComponent<TextRendererComponent>(&m_font, "True RPG!\n Welcome!");

    // Некоторые настройки текста для примера
    textRenderer.horizontalAlign = HorizontalAlign::Center;
    textRenderer.verticalAlign = VerticalAlign::Top;

    // Биндим скрипт к энтити и передаем туда камеру
    m_textEntity.addComponent<NativeScriptComponent>().bind<TextScript>(m_camera);


    // Создание fps счетчика
    m_fpsEntity = m_scene.createEntity("fps");
    m_fpsEntity.addComponent<TextRendererComponent>(&m_font, "FPS: 0");
    auto &fpsTransform = m_fpsEntity.getComponent<TransformComponent>();
    fpsTransform.scale = glm::vec2(0.8f, 0.8f);
    m_fpsEntity.addComponent<NativeScriptComponent>().bind<FPSCounterScript>(m_camera);


    // Создание игрока
    m_playerEntity = m_scene.createEntity("player");
    auto &playerTransform = m_playerEntity.getComponent<TransformComponent>();
    playerTransform.position = glm::vec2(0.0f, 0.0f);

    Entity spriteEntity = m_scene.createEntity("sprite");
    auto &heroRenderer = spriteEntity.addComponent<SpriteRendererComponent>(m_heroTexture);
    heroRenderer.textureRect = IntRect(32, 96, 32, 32);

    auto &heroTransform = spriteEntity.getComponent<TransformComponent>();
    heroTransform.scale = glm::vec2(2.f, 2.f);
    heroTransform.origin = glm::vec2(16, 16);

    Hierarchy::addChild(m_playerEntity, spriteEntity);
    Hierarchy::addChild(m_playerEntity, m_textEntity);
    Hierarchy::addChild(m_playerEntity, m_fpsEntity);
    Hierarchy::addChild(m_playerEntity, cameraEntity);

    // Биндим скрипт к игроку
    m_playerEntity.addComponent<NativeScriptComponent>().bind<PlayerScript>();
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
}

Camera2D *Game::getCamera()
{
    return &m_camera;
}
