#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../window/Window.h"

class PlayerScript : public Script
{
    float m_speed{2.f};

    Entity m_spriteEntity;

    float m_animationDelay{0.f};
    int m_currentAnimation{0};
    int m_frame{0};

public:
    void onCreate()
    {
        m_spriteEntity = Hierarchy::find(getEntity(), "sprite");
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


        // Анимация
        auto &renderer = m_spriteEntity.getComponent<SpriteRendererComponent>();

        if (movement == glm::ivec2(0.f) || m_frame > 2)
        {
            m_frame = 0;
            return;
        }

        if (m_animationDelay > 30.0f)
        {
            renderer.textureRect = IntRect(m_frame * 32, m_currentAnimation * 32, 32, 32);
            m_frame++;
            m_animationDelay = 0.f;
        }
        m_animationDelay += dt;
    }

    void onDestroy() {}
};

#endif //RPG_PLAYER_H
