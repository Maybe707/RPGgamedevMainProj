#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D(glm::vec2 position, float width, float height, float zn, float zf)
        : m_position(position),
          m_width(width), m_height(height),
          m_zn(zn), m_zf(zf) {}

glm::vec2 Camera2D::getPosition() const
{
    return m_position;
}

void Camera2D::setPosition(glm::vec2 position)
{
    m_position = position;
}

glm::mat4 Camera2D::getProjectionMatrix() const
{
    return glm::ortho(
            -m_width / 2, m_width / 2,
            -m_height / 2, m_height / 2,
            m_zn, m_zf
    );
}

glm::mat4 Camera2D::getViewMatrix() const
{
    return glm::translate(glm::mat4(1), glm::vec3(m_position, 0));
}
