#ifndef COLLISION_H
#define COLLISION_H

#include "Map_Objects.h"
#include "Player_Implementation.h"
#include "Map.h"

class Collision
{
public:
    void repel(MapObjects** mapObjects, PlayerImpl& player, float& deltaTime, GLFWwindow* window);
    bool detectionBox(PlayerImpl& player, MapObjects& mapObjects, float& deltaTime, GLFWwindow* window);
    void detection(MapObjects** mapObjects, PlayerImpl& player, float& deltaTime, WorldMap& worldmap, GLFWwindow* window);
};

#endif
