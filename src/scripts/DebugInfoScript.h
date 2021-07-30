#ifndef RPG_DEBUGINFOSCRIPT_H
#define RPG_DEBUGINFOSCRIPT_H

#include <GLFW/glfw3.h>

class DebugInfoScript : public Script
{
    Camera2D &m_camera;

    float m_currentTime{0.f};
    int m_frameCount{0};
    float m_lastTime{0.f};
    int m_fps{0};

public:
    DebugInfoScript(Camera2D &camera)
            : m_camera(camera) {}

    void onCreate() {}

    void onUpdate(float deltaTime)
    {
        // TODO: Приходится обращаться к функции glfw, это плохо
        m_currentTime = glfwGetTime();
        m_frameCount++;

        // Если прошла секунда
        if (m_currentTime - m_lastTime >= 1.0)
        {
            m_fps = m_frameCount;

            m_frameCount = 0;
            m_lastTime = m_currentTime;
        }

        auto &transform = getComponent<TransformComponent>();
        transform.position = glm::vec2(-m_camera.getWidth() / 2, -m_camera.getWidth() / 2);
        auto &textRenderer = getComponent<TextRendererComponent>();
        textRenderer.text = "FPS: " + std::to_string(m_fps);

        Entity playerEntity = getComponent<HierarchyComponent>().parent;
        auto& playerPosition = playerEntity.getComponent<TransformComponent>().position;

        textRenderer.text += "\nx: " + std::to_string(playerPosition.x) + " y: " + std::to_string(playerPosition.y);
    }

    void onDestroy() {}
};

#endif //RPG_DEBUGINFOSCRIPT_H
