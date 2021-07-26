#include <glad/gl.h>
#include "window/Window.h"
#include "Collision.h"
#include "utils/Coordinate.h"

bool Collision::detectionBox(Player& player, const glm::ivec2& tilePos, float& deltaTime)
{
    bool stateX;
    Window& wnd = Window::getInstance();

    glm::vec2 playerPosition = player.getPosition();

    if (playerPosition.x < tilePos.x + 0.7f && // 0.7f - это прибовление к размеру. Еракто это как reactangel collider
        playerPosition.x + 0.7f > tilePos.x &&
        playerPosition.y < tilePos.y + 0.7f &&
        playerPosition.y + 0.7f > tilePos.y)
    {

        // TODO: В инпуте кнопки проверяются, тут проверяются. Что-то очень странное...
        if (wnd.getKey(GLFW_KEY_W))
        {
            playerPosition -= glm::vec2(0.f, deltaTime * player.getSpeed());
        }

        if (wnd.getKey(GLFW_KEY_S))
        {
            playerPosition += glm::vec2(0.f, deltaTime * player.getSpeed());
        }

        if (wnd.getKey(GLFW_KEY_A))
        {
            playerPosition += glm::vec2(deltaTime * player.getSpeed(), 0.f);
        }

        if (wnd.getKey(GLFW_KEY_D))
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

void Collision::detection(const map::World& world, Player& player, float& deltaTime)
{
    for (int i = 0; i < world.getSize(); ++i)
    {
        for (int j = 0; j < world.getSize(); ++j)
        {
            auto& chunk = world.getChunk({i, j}); 
            for (size_t x = 0; x < CHUNK_SIZE; x++)
            {
                for (size_t y = 0; y < CHUNK_SIZE; y++)
                {
                    if (chunk.getTile({x, y}) == 1 && detectionBox(player, {
                            x + chunk.getPosition().x * CHUNK_SIZE, 
                            y + chunk.getPosition().y * CHUNK_SIZE
                        }, deltaTime))
                    {
                        return;
                    }
                }
            }
        }
    }
}
