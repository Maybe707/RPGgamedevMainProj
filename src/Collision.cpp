#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "Collision.h"

bool Collision::detectionBox(Player &player, MapObjects &mapObjects, float &deltaTime, GLFWwindow *window)
{
    bool stateX;

    glm::vec2 playerPosition = player.getPosition();

    if (playerPosition.x < mapObjects.getXAxis() + 58.0f && // Кто знает, почему тут 58?
        playerPosition.x + 58.0f > mapObjects.getXAxis() &&
        playerPosition.y < mapObjects.getYAxis() + 58.0f &&
        playerPosition.y + 58.0f > mapObjects.getYAxis())
    {

        // TODO: В инпуте кнопки проверяются, тут проверяются. Что-то очень странное...
        if (player.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            playerPosition -= glm::vec2(0.f, deltaTime * player.getSpeed());
        }

        if (player.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            playerPosition += glm::vec2(0.f, deltaTime * player.getSpeed());
        }

        if (player.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            playerPosition += glm::vec2(deltaTime * player.getSpeed(), 0.f);
        }

        if (player.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            playerPosition -= glm::vec2(deltaTime * player.getSpeed(), 0.f);
        }

        player.setPosition(playerPosition);

        stateX = true;
    }
    else
    {
        stateX = false;
    }

    return stateX;
}

void Collision::detection(MapObjects **mapObjects, Player &player, float &deltaTime, WorldMap &worldmap, GLFWwindow *window)
{
    for (int i = 0; i < worldmap.getMapHeight(); ++i)
    {
        for (int j = 0; j < worldmap.getMapWidth(); ++j)
        {
            if (worldmap.getMapKey(i, j) == '0' && detectionBox(player, mapObjects[i][j], deltaTime, window))
            {
                return;
            }
        }
    }
}
