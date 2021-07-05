#include "Player_Implementation.h"
#include "glfw3.h"


// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании кнопки мыши в данном кадре и соответствующая обработка данных событий
void Process_Input(GLFWwindow* window, Player_Implementation& Player_Hero, float& Delta_Time);
