#include <GLFW/glfw3.h>
#include "Player_Implementation.h"
class Game_Shell
{
	Player_Implementation* Player_Hero;
public:
	Game_Shell()
	{
		glfwSetKeyCallback(GLFWwindow *window, GLFWkeyfun callback);
	}

	
