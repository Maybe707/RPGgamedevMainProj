/*#include <GLFW/glfw3.h>
#include <iostream>

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Убеждаемся, что окно просмотра соответствует новым размерам окна.
	// Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
	glViewport(0, 0, width, height);
}

class GL_Window
{
	GLFWwindow* m_window;
	const unsigned int m_SCR_WIDTH;
	const unsigned int m_SCR_HEIGHT;
	public:
GL_Window(const unsigned int scr_width, const unsigned int scr_height) :
	m_SCR_WIDTH(scr_width), m_SCR_HEIGHT(scr_height)
	{
    // glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(m_SCR_WIDTH, m_SCR_HEIGHT, "RPG", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }
	m_window = window;
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	}

	GLFWwindow* get_Window() { return m_window; }
};
*/
