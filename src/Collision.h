#ifndef COLLISION_H
#define COLLISION_H

#include "MapObjects.h"
#include "Player.h"
#include "Map.h"

class Collision
{
public:
    void repel(MapObjects** mapObjects, Player& player, float& deltaTime, GLFWwindow* window);
    bool detectionBox(Player& player, MapObjects& mapObjects, float& deltaTime, GLFWwindow* window);
    void detection(MapObjects** mapObjects, Player& player, float& deltaTime, WorldMap& worldmap, GLFWwindow* window);
};

#endif
