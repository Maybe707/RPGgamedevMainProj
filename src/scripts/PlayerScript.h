#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../client/window/Window.h"

class PlayerScript : public Script
{
    float m_speed{2.f};

    Entity m_spriteEntity{};
    Entity m_stepsEntity{};

    float m_animationDelay{0.f};
    int m_currentAnimation{3};
    int m_frame{0};

public:
    void onCreate()
    {
        m_spriteEntity = Hierarchy::find(getEntity(), "sprite");
        m_stepsEntity = Hierarchy::find(getEntity(), "stepsSound");
    }

    void onUpdate(float deltaTime)
    {
        Window &window = Window::getInstance();
        float dt = deltaTime * 200;

        // Пока поместил выход из игры сюда
        if (window.getKey(GLFW_KEY_ESCAPE))
        {
            window.close();
        }

        auto &transform = getComponent<TransformComponent>();
        auto &stepsSound = m_stepsEntity.getComponent<AudioSourceComponent>();

        // Управление
        glm::ivec2 movement(0);
        if (window.getKey(GLFW_KEY_W))
        {
            movement = glm::ivec2(0, 1);
            m_currentAnimation = 0;
        }
        if (window.getKey(GLFW_KEY_S))
        {
            movement = glm::ivec2(0, -1);
            m_currentAnimation = 3;
        }
        if (window.getKey(GLFW_KEY_A))
        {
            movement = glm::ivec2(-1, 0);
            m_currentAnimation = 2;
        }
        if (window.getKey(GLFW_KEY_D))
        {
            movement = glm::ivec2(1, 0);
            m_currentAnimation = 1;
        }

        transform.position += glm::vec2(movement) * dt * m_speed;

        // Шаманю с анимацией
        auto &renderer = m_spriteEntity.getComponent<SpriteRendererComponent>();

        if (m_animationDelay > 30.0f)
        {
            renderer.textureRect = IntRect(m_frame * 32, m_currentAnimation * 32, 32, 32);
            m_frame++;
            m_animationDelay = 0.f;
        }
        m_animationDelay += dt;

        if (m_frame > 2)
        {
            m_frame = 0;
        }

        if (movement == glm::ivec2(0.f))
        {
            m_frame = 1;
            stepsSound.pause();
        }
        else
        {
            stepsSound.play();
        }
    }

    void onDestroy() {}
};

#endif //RPG_PLAYER_H
