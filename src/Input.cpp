#include "Player.h"
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window, Player &player, float &deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (player.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        player.setYAxis(player.getYAxis() + deltaTime * player.getSpeed());
    }

    if (player.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        player.setYAxis(player.getYAxis() - deltaTime * player.getSpeed());
    }

    if (player.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        player.setXAxis(player.getXAxis() - deltaTime * player.getSpeed());
    }

    if (player.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        player.setXAxis(player.getXAxis() + deltaTime * player.getSpeed());
    }
}
