#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../window/Window.h"

Camera2D::Camera2D(glm::vec2 position, float width, float height,  float scale, float zn, float zf) 
        : m_position(position),
          m_width(width), m_height(height),
          m_zn(zn), m_zf(zf), m_scale(scale) {}

glm::vec2 Camera2D::getPosition() const
{
    return m_position;
}

void Camera2D::setPosition(glm::vec2 position)
{
    m_position = position;
}
// TODO: временное решение
void Camera2D::update()
{
    auto& wnd = Window::getInstance();
    m_width = wnd.getWidth();
    m_height = wnd.getHeight();
}

glm::mat4 Camera2D::getProjectionMatrix() const
{
    auto& wnd = Window::getInstance();
    int width = wnd.getWidth();
    int height = wnd.getHeight();

    return glm::ortho(
            -m_width  * m_scale, m_width  * m_scale,
            -m_height * m_scale, m_height * m_scale,
            m_zn, m_zf
    );
}

glm::mat4 Camera2D::getViewMatrix() const
{
    return glm::translate(glm::mat4(1), glm::vec3(m_position, 0));
}
