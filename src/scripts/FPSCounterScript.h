#ifndef RPG_FPSCOUNTERSCRIPT_H
#define RPG_FPSCOUNTERSCRIPT_H

#include <GLFW/glfw3.h>

class FPSCounterScript : public Script
{
    Camera2D &m_camera;

    float m_currentTime{0.f};
    int m_frameCount{0};
    float m_lastTime{0.f};
    int m_fps{0};

public:
    FPSCounterScript(Camera2D &camera)
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

        auto &fpsTransform = getComponent<TransformComponent>();
        fpsTransform.position = glm::vec2(-m_camera.getWidth() / 2, -m_camera.getWidth() / 2);
        auto &fpsRenderer = getComponent<TextRendererComponent>();
        fpsRenderer.text = "FPS: " + std::to_string(m_fps);
    }

    void onDestroy() {}
};

#endif //RPG_FPSCOUNTERSCRIPT_H
