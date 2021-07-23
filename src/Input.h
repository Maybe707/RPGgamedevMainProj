#include "Player_Implementation.h"
#include <GLFW/glfw3.h>

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании кнопки мыши в 
// данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow* window, PlayerImpl& Player_Hero, float& Delta_Time);
