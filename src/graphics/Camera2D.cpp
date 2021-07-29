#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

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

float Camera2D::getWidth() const
{
    return m_width;
}

float Camera2D::getHeight() const
{
    return m_height;
}

glm::mat4 Camera2D::getProjectionMatrix() const
{
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
