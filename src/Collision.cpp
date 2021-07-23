#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "Collision.h"

void Collision::repel(MapObjects **mapObjects, Player &player, float &deltaTime, GLFWwindow *window)
{
    if (player.getKeyAxis() == GLFW_KEY_W)
    {
        player.setYAxis(player.getYAxis() - deltaTime);
    }

    if (player.getKeyAxis() == GLFW_KEY_S)
    {
        player.setYAxis(player.getYAxis() + deltaTime);
    }

    if (player.getKeyAxis() == GLFW_KEY_A)
    {
        player.setXAxis(player.getXAxis() + deltaTime);
    }

    if (player.getKeyAxis() == GLFW_KEY_D)
    {
        player.setXAxis(player.getXAxis() - deltaTime);
    }
}

bool Collision::detectionBox(Player &player, MapObjects &mapObjects, float &deltaTime, GLFWwindow *window)
{
    bool stateX = false;
    float axisX = 0;
    float axisY = 0;

    if (player.getXAxis() < mapObjects.getXAxis() + 58.0f &&
        player.getXAxis() + 58.0f > mapObjects.getXAxis() &&
        player.getYAxis() < mapObjects.getYAxis() + 58.0f &&
        player.getYAxis() + 58.0f > mapObjects.getYAxis())
    {
        if (player.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            player.setYAxis(player.getYAxis() - deltaTime * player.getSpeed());
        }

        if (player.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            player.setYAxis(player.getYAxis() + deltaTime * player.getSpeed());
        }

        if (player.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            player.setXAxis(player.getXAxis() + deltaTime * player.getSpeed());
        }

        if (player.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            player.setXAxis(player.getXAxis() - deltaTime * player.getSpeed());
        }

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
            if (worldmap.getMapKey(i, j) == '0')
            {
                if (detectionBox(player, mapObjects[i][j], deltaTime, window))
                {
                    return;
                }
            }
        }
    }
}
