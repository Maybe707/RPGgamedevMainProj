#include "Window.h"

#include <iostream>

Window::Window(int width, int height, const std::string &title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    m_inputCallback = [](Window *, int, int, int, int) {};
    m_resizeCallback = [](Window *, int, int) {};

    if (m_window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    //glfwSwapInterval(1); - Turn on vertical synchronization.
    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, glfwKeyCallback);
    glfwSetFramebufferSizeCallback(m_window, glfwFramebufferSizeCallback);
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(m_window);
}

void Window::close() {
    glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(m_window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

int Window::getWidth() {
    int width;
    glfwGetWindowSize(m_window, &width, nullptr);
    return width;
}

int Window::getHeight() {
    int height;
    glfwGetWindowSize(m_window, nullptr, &height);
    return height;
}

void Window::setInputCallback(InputCallback inputCallback) {
    m_inputCallback = inputCallback;
}

void Window::setResizeCallback(ResizeCallback resizeCallback) {
    m_resizeCallback = resizeCallback;
}

void Window::onKey(int key, int scancode, int actions, int mods) {
    m_inputCallback(this, key, scancode, actions, mods);
}

void Window::onResize(int width, int height) {
    m_resizeCallback(this, width, height);
}

void Window::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods) {
    auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
    win->onKey(key, scancode, actions, mods);
}

void Window::glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
    win->onResize(width, height);
}
