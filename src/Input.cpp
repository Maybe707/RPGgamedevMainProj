#include "Player_Implementation.h"
#include <GLFW/glfw3.h>

void Process_Input(GLFWwindow* window, Player_Implementation& Player_Hero, float& Delta_Time)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if (Player_Hero.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Player_Hero.set_yAxis(Player_Hero.get_yAxis() + Delta_Time * Player_Hero.get_Speed());
	}
	if (Player_Hero.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Player_Hero.set_yAxis(Player_Hero.get_yAxis() - Delta_Time * Player_Hero.get_Speed());
	}
	if (Player_Hero.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Player_Hero.set_xAxis(Player_Hero.get_xAxis() - Delta_Time * Player_Hero.get_Speed());
	}
	if (Player_Hero.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Player_Hero.set_xAxis(Player_Hero.get_xAxis() + Delta_Time * Player_Hero.get_Speed());
	}
}
