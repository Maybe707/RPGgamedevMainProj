#ifndef RPG_NATIVESCRIPTCOMPONENT_H
#define RPG_NATIVESCRIPTCOMPONENT_H

#include "../Script.h"

struct NativeScriptComponent
{
    Script* instance = nullptr;

    std::function<void()> instantiateFunction;
    std::function<void()> destroyInstanceFunction;

    std::function<void(Script*)> onCreateFunction;
    std::function<void(Script*, float)> onUpdateFunction;
    std::function<void(Script*)> onDestroyFunction;

    template<typename T, typename... Args>
    void bind(Args &&... args)
    {
        // Пока сделал передачу внешних параметров напрямую в конструктор скрипта, хз как тут лучше поступить
        instantiateFunction = [&]() { instance = new T(std::forward<Args>(args)...); };
        destroyInstanceFunction = [&]() { delete (T*)instance; instance = nullptr; };

        // TODO: Надо сделать, чтобы эти методы были необязательными в классе скрипта
        onCreateFunction = [](Script* script) { ((T*)script)->onCreate(); };
        onUpdateFunction = [](Script* script, float deltaTime) { ((T*)script)->onUpdate(deltaTime); };
        onDestroyFunction = [](Script* script) { ((T*)script)->onDestroy(); };
    }
};

#endif //RPG_NATIVESCRIPTCOMPONENT_H
