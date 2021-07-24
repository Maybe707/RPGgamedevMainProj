#ifndef COLLISION_H
#define COLLISION_H

#include "MapObject.h"
#include "Player.h"
#include "Map.h"

class Collision
{
public:
    bool detectionBox(Player& player, MapObject& mapObjects, float& deltaTime);
    void detection(MapObject** mapObjects, Player& player, float& deltaTime, WorldMap& worldmap);
};

#endif
