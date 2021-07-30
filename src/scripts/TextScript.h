#ifndef RPG_TEXTSCRIPT_H
#define RPG_TEXTSCRIPT_H

#include "../scene/Script.h"

class TextScript : public Script
{
    Camera2D &m_camera;

public:
    TextScript(Camera2D &camera)
            : m_camera(camera) {}

    void onCreate() {}

    void onUpdate(float deltaTime)
    {
        static float t = 0;
        t += deltaTime / 100;

        auto &textTransform = getComponent<TransformComponent>();
        textTransform.position = glm::vec2(0.f, m_camera.getHeight() / 2);
        auto &textRenderer = getComponent<TextRendererComponent>();
        textRenderer.color = glm::vec4(
                (std::sin(t) + 1) / 2,
                (std::sin(2 * t + 1) + 1) / 2,
                (std::sin(0.5 * t) + 2) / 2, 1.f
        );
    }

    void onDestroy() {}
};

#endif //RPG_TEXTSCRIPT_H
