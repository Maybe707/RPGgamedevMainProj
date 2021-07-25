#include <glad/gl.h>
#include "window/Window.h"
#include "Collision.h"

// TODO: Временно вырезанно для переработки

// bool Collision::detectionBox(Player& player, MapObject& mapObject, float& deltaTime)
// {
//     bool stateX;
//     Window& wnd = Window::getInstance();

//     glm::vec2 playerPosition = player.getPosition();

//     if (playerPosition.x < mapObject.getXAxis() + 58.0f && //HACK: Кто знает, почему тут 58? Это хак
//         playerPosition.x + 58.0f > mapObject.getXAxis() &&
//         playerPosition.y < mapObject.getYAxis() + 58.0f &&
//         playerPosition.y + 58.0f > mapObject.getYAxis())
//     {

//         // TODO: В инпуте кнопки проверяются, тут проверяются. Что-то очень странное...
//         if (wnd.getKey(GLFW_KEY_W))
//         {
//             playerPosition -= glm::vec2(0.f, deltaTime * player.getSpeed());
//         }

//         if (wnd.getKey(GLFW_KEY_S))
//         {
//             playerPosition += glm::vec2(0.f, deltaTime * player.getSpeed());
//         }

//         if (wnd.getKey(GLFW_KEY_A))
//         {
//             playerPosition += glm::vec2(deltaTime * player.getSpeed(), 0.f);
//         }

//         if (wnd.getKey(GLFW_KEY_D))
//         {
//             playerPosition -= glm::vec2(deltaTime * player.getSpeed(), 0.f);
//         }

//         player.setPosition(playerPosition);

//         stateX = true;
//     }
//     else
//     {
//         stateX = false;
//     }

//     return stateX;
// }

// void Collision::detection(MapObject** mapObjects, Player& player, float& deltaTime, WorldMap& worldmap)
// {
//     for (int i = 0; i < worldmap.getMapHeight(); ++i)
//     {
//         for (int j = 0; j < worldmap.getMapWidth(); ++j)
//         {
//             if (worldmap.getMapKey(i, j) == '0' && detectionBox(player, mapObjects[i][j], deltaTime))
//             {
//                 return;
//             }
//         }
//     }
// }
