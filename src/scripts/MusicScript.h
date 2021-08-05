#ifndef RPG_MUSICSCRIPT_H
#define RPG_MUSICSCRIPT_H

class MusicScript : public Script
{
public:
    void onCreate() {}

    void onUpdate(float deltaTime)
    {
        Window &window = Window::getInstance();

        auto &audioSourceComponent = getComponent<AudioSourceComponent>();

        if (window.getKey(GLFW_KEY_1))
        {
            audioSourceComponent.play();
        }
        if (window.getKey(GLFW_KEY_2))
        {
            audioSourceComponent.pause();
        }
        if (window.getKey(GLFW_KEY_3))
        {
            audioSourceComponent.stop();
        }
    }

    void onDestroy() {}
};

#endif //RPG_MUSICSCRIPT_H
