#include <glad/gl.h>
#include "window/Window.h"
#include "Collision.h"
#include "utils/Coordinate.h"

bool Collision::detectionBox(Player& player, const glm::ivec2& tilePos, float& deltaTime)
{
    bool stateX;
    Window& wnd = Window::getInstance();
    
    glm::vec2 playerPosition = player.getPosition();
    // TODO: нужно сдлеать нормальный коллайдер что бы удалить 58.f
    if (playerPosition.x < tilePos.x + 58.f && // 58.f - это прибовление к размеру. Еракто это как reactangel collider
        playerPosition.x + 58.f > tilePos.x &&
        playerPosition.y < tilePos.y + 58.f &&
        playerPosition.y + 58.f > tilePos.y)
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
    for (auto& ch : world.getChunks())
    {
        for (size_t x = 0; x < CHUNK_SIZE; x++)
        {
            for (size_t y = 0; y < CHUNK_SIZE; y++)
            {
                float wd = map::TilesData.at(ch.second.getTile({x, y}))->getSprite().getGlobalBounds().getWidth();
                float ht = map::TilesData.at(ch.second.getTile({x, y}))->getSprite().getGlobalBounds().getHeight();
                if (map::TilesData.at(ch.second.getTile({x, y}))->isCollide() && 
                        detectionBox(player, map::toGlobalTilePos({x, y}, ch.second.getPosition()) * glm::ivec2(wd, ht), deltaTime))
                {
                    return;
                }
            }
            
        }
    }
}
