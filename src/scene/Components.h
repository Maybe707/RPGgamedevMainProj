#ifndef RPG_COMPONENTS_H
#define RPG_COMPONENTS_H

#include <glm/glm.hpp>
#include "../graphics/Texture.h"
#include "../graphics/Rect.h"
#include "../graphics/Camera2D.h"
#include "../graphics/Font.h"
#include "Script.h"

struct NameComponent
{
    std::string name;
};

struct TransformComponent
{
    glm::vec2 position{};
    glm::vec2 origin{};
    glm::vec2 scale{1.f};
};

struct HierarchyComponent
{
    std::size_t children{}; // Количество детей у текущего энтити
    Entity firstChild{}; // Первый ребенок у текущего энтити
    Entity prev{}; // Предыдущий ребенок у родителя
    Entity next{}; // Следующий ребенок у родителя
    Entity parent{}; // Родительский энтити
};

// TODO: переделать компонент камеры
struct CameraComponent
{
    Camera2D *camera;
};

struct SpriteRendererComponent
{
    Texture texture;
    IntRect textureRect{0, 0, 0, 0};
    glm::vec4 color{1.f};

    SpriteRendererComponent(Texture texture)
            : texture(texture),
              textureRect(0, 0, texture.getWidth(), texture.getHeight()) {}
};

enum class HorizontalAlign
{
    Left, Right, Center
};

enum class VerticalAlign
{
    Top, Bottom, Center
};

struct TextRendererComponent
{
    Font *font;
    std::string text;
    glm::vec4 color{1.f};
    HorizontalAlign horizontalAlign = HorizontalAlign::Left;
    VerticalAlign verticalAlign = VerticalAlign::Bottom;

    TextRendererComponent(Font *font, std::string text)
            : font(font), text(text) {}
};

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

#endif //RPG_COMPONENTS_H
