#include "Player.h"
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window, Player &player, float &deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    glm::vec2 movementVec = player.getPosition();

    if (player.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        movementVec += glm::vec2(0.f, deltaTime * player.getSpeed());
    }

    if (player.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        movementVec -= glm::vec2(0.f, deltaTime * player.getSpeed());
    }

    if (player.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        movementVec -= glm::vec2(deltaTime * player.getSpeed(), 0.f);
    }

    if (player.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        movementVec += glm::vec2(deltaTime * player.getSpeed(), 0.f);
    }

    player.setPosition(movementVec);
}
