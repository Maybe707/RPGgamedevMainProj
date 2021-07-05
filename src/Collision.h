#ifndef COLLISION_H
#define COLLISION_H


#include "Map_Objects.h"
#include "Player_Implementation.h"
#include "Map.h"

class Collision
{
public:
	void Repel(Map_Objects** Map_Objects_Pointer, Player_Implementation& Player_Hero,
		       float& Delta_Time, GLFWwindow* window);
	bool Detection_Box(Player_Implementation& player, Map_Objects& map_object, float& Delta_Time, GLFWwindow* window);
	void Detection(Map_Objects** Map_Objects_Pointer, Player_Implementation& Player_Hero, float& Delta_Time, WorldMap& Tile_Map, float SCR_WIDTH, float SCR_HEIGHT, GLFWwindow* window);
};

#endif
