#ifndef COLLISION_H
#define COLLISION_H

#include "Player.h"
#include "scene/TileMapComponent.h"

// TODO: Нуэно изменить коллизию. 

class Collision
{
public:
    static void detection(const TileMap& world, Player& player, float& deltaTime);
private:
    static bool detectionBox(Player& player, const glm::ivec2& tilePos, float& deltaTime);
};

#endif
