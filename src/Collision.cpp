#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Collision.h"

void Collision::Repel(Map_Objects** Map_Objects_Pointer, Player_Implementation& Player_Hero, float& Delta_Time, GLFWwindow* window)
{
	if (Player_Hero.getKeyAxis() == GLFW_KEY_W)
	{
		Player_Hero.set_yAxis(Player_Hero.get_yAxis() - Delta_Time);
	}
	if (Player_Hero.getKeyAxis() == GLFW_KEY_S)
	{
		Player_Hero.set_yAxis(Player_Hero.get_yAxis() + Delta_Time);
	}
	if (Player_Hero.getKeyAxis() == GLFW_KEY_A)
	{
		Player_Hero.set_xAxis(Player_Hero.get_xAxis() + Delta_Time);
	}
	if (Player_Hero.getKeyAxis() == GLFW_KEY_D)
	{
		Player_Hero.set_xAxis(Player_Hero.get_xAxis() - Delta_Time);
	}
}

bool Collision::Detection_Box(Player_Implementation& player, Map_Objects& map_object, float& Delta_Time, GLFWwindow* window)
{
	bool state_x = false;
	float axisX = 0;
	float axisY = 0;
    
	if(player.get_xAxis() < map_object.get_xAxis() + 58.0f &&
	   player.get_xAxis() + 58.0f > map_object.get_xAxis() &&
	   player.get_yAxis() < map_object.get_yAxis() + 58.0f &&
	   player.get_yAxis() + 58.0f > map_object.get_yAxis())
	{
		if (player.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player.set_yAxis(player.get_yAxis() - Delta_Time*player.get_Speed());
		}
		if (player.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			player.set_yAxis(player.get_yAxis() + Delta_Time*player.get_Speed());
		}
		if (player.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			player.set_xAxis(player.get_xAxis() + Delta_Time*player.get_Speed());
		}
		if (player.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			player.set_xAxis(player.get_xAxis() - Delta_Time*player.get_Speed());
		}
		state_x = true;
	}
	else
	{
		state_x = false;
	}

	return state_x;
}

void Collision::Detection(Map_Objects** Map_Objects_Pointer, Player_Implementation& Player_Hero, float& Delta_Time, WorldMap& Tile_Map, GLFWwindow* window)
{
	for(int i = 0; i < Tile_Map.getMapHeight(); ++i)
		for(int j = 0; j < Tile_Map.getMapWidth(); ++j)
		{
			if(Tile_Map.getMapKey(i, j) == '0')
			{
				bool collision_Flag = false;
				collision_Flag = Detection_Box(Player_Hero, Map_Objects_Pointer[i][j], Delta_Time, window);
				if(collision_Flag)
					return;
			}
		}
}
