#ifndef RPG_WINDOW_H
#define RPG_WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>

class Window;

using InputCallback = void (*)(Window *, int, int, int, int);
using ResizeCallback = void (*)(Window *, int, int);

class Window
{
private:
    GLFWwindow *m_window;
    InputCallback m_inputCallback;
    ResizeCallback m_resizeCallback;
public:
    Window(int width, int height, const std::string &title);

    ~Window();

    // TODO: в идеале нужно избавиться от этого метода
    inline GLFWwindow *getGLFWwindow()
    {
        return m_window;
    }

    bool isOpen();

    void close();

    void makeContextCurrent();

    void swapBuffers();

    int getWidth();

    int getHeight();

    void setInputCallback(InputCallback inputCallback);

    void setResizeCallback(ResizeCallback resizeCallback);

private:
    void onKey(int key, int scancode, int actions, int mods);

    void onResize(int width, int height);

    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods);

    static void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height);
};

#endif //RPG_WINDOW_H
