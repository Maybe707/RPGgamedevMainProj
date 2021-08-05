#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "window/Window.h"
#include "RTime.h"
#include "Game.h"

// Никто не забыт, ничто не забыто

// D.E.L.E.T.E.D
// summonDestructor3000 
// 2021-2021
// Покойся с миром 

void resizeCallback(Window *window, int width, int height);

int main()
{
    // Создание окна
    auto &window = Window::getInstance(1280, 720, "TRUE RPG");
    window.makeContextCurrent();
    window.setResizeCallback(resizeCallback);

    Game game;

    // Game timer
    RTime time(0.0f, 0.0f, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (window.isOpen())
    {
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.update(time.getDeltaTime());

        // Обмен содержимым front- и back- буферов.
        // Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        window.swapBuffers();
        glfwPollEvents();
    }
    
    game.destroy();

    window.destroy();

    return 0;
}

// всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void resizeCallback(Window *window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}
