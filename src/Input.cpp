#include "Player.h"
#include <GLFW/glfw3.h>
#include "window/Window.h"

void processInput(Player &player, float &deltaTime)
{
    Window& window = Window::getInstance();

    if (window.getKey(GLFW_KEY_ESCAPE))
    {
        window.close();
    }

    glm::vec2 movementVec = player.getPosition();

    if (window.getKey(GLFW_KEY_W))
    {
        movementVec += glm::vec2(0.f, deltaTime * player.getSpeed());
    }

    if (window.getKey(GLFW_KEY_S))
    {
        movementVec -= glm::vec2(0.f, deltaTime * player.getSpeed());
    }

    if (window.getKey(GLFW_KEY_A))
    {
        movementVec -= glm::vec2(deltaTime * player.getSpeed(), 0.f);
    }

    if (window.getKey(GLFW_KEY_D))
    {
        movementVec += glm::vec2(deltaTime * player.getSpeed(), 0.f);
    }
    
    player.setPosition(movementVec);
}
