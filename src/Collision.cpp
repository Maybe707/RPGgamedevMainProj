#include <glad/gl.h>
#include "window/Window.h"
#include "Collision.h"

bool Collision::detectionBox(Player &player, MapObject &mapObjects, float &deltaTime)
{
    bool stateX;
    Window& wnd = Window::getInstance();

    glm::vec2 playerPosition = player.getPosition();

    if (playerPosition.x < mapObjects.getXAxis() + 58.0f && // Кто знает, почему тут 58?
        playerPosition.x + 58.0f > mapObjects.getXAxis() &&
        playerPosition.y < mapObjects.getYAxis() + 58.0f &&
        playerPosition.y + 58.0f > mapObjects.getYAxis())
    {

        // TODO: В инпуте кнопки проверяются, тут проверяются. Что-то очень странное...
        if (player.getKeyAxis() == GLFW_KEY_W && wnd.getKey(GLFW_KEY_W))
        {
            playerPosition -= glm::vec2(0.f, deltaTime * player.getSpeed());
        }

        if (player.getKeyAxis() == GLFW_KEY_S && wnd.getKey(GLFW_KEY_S))
        {
            playerPosition += glm::vec2(0.f, deltaTime * player.getSpeed());
        }

        if (player.getKeyAxis() == GLFW_KEY_A && wnd.getKey(GLFW_KEY_A))
        {
            playerPosition += glm::vec2(deltaTime * player.getSpeed(), 0.f);
        }

        if (player.getKeyAxis() == GLFW_KEY_D && wnd.getKey(GLFW_KEY_D))
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

void Collision::detection(MapObject **mapObjects, Player &player, float &deltaTime, WorldMap &worldmap)
{
    for (int i = 0; i < worldmap.getMapHeight(); ++i)
    {
        for (int j = 0; j < worldmap.getMapWidth(); ++j)
        {
            if (worldmap.getMapKey(i, j) == '0' && detectionBox(player, mapObjects[i][j], deltaTime))
            {
                return;
            }
        }
    }
}
