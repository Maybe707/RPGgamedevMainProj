#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera2D::Camera2D(float xAxis, float yAxis, float zAxis,
                   float width, float height,
                   float zn, float zf)
    : m_width(width), m_height(height),
      m_zn(zn), m_zf(zf)
{
    for (int i = 0; i < 16; ++i)
        m_transformMatrix[i] = 0.0f;

    for (int i = 0; i < 16; i += 5)
        m_transformMatrix[i] = 1.0f;

    m_transformMatrix[12] = xAxis;
    m_transformMatrix[13] = yAxis;
    m_transformMatrix[14] = zAxis;
}

void Camera2D::moveLocal(float xAxis, float yAxis, float zAxis, float distance)
{
    float deltaX = xAxis * m_transformMatrix[0] + 
                   yAxis * m_transformMatrix[4] +
                   zAxis * m_transformMatrix[8];

    float deltaY = xAxis * m_transformMatrix[1] + 
                   yAxis * m_transformMatrix[5] + 
                   zAxis * m_transformMatrix[9];

    float deltaZ = xAxis * m_transformMatrix[2] + 
                   yAxis * m_transformMatrix[6] +
                   zAxis * m_transformMatrix[10];

    m_transformMatrix[12] += deltaX * distance;
    m_transformMatrix[13] += deltaY * distance;
    m_transformMatrix[14] += deltaZ * distance;
}

void Camera2D::moveGlobal(float xAxis, float yAxis, float zAxis, float distance)
{
    m_transformMatrix[12] += xAxis * distance;
    m_transformMatrix[13] += yAxis * distance;
    m_transformMatrix[14] += zAxis * distance;
}

void Camera2D::setPosition(float xAxis, float yAxis, float zAxis, float distance)
{
    m_transformMatrix[12]  = xAxis * distance;
    m_transformMatrix[13]  = yAxis * distance;
    m_transformMatrix[14]  = zAxis * distance;
}

void Camera2D::setView(Shader shader)
{
    glm::mat4 projMat = glm::ortho(
        -m_width / 2, m_width / 2,
        -m_height / 2, m_height / 2,
        0.0f, 100.0f
    );

    shader.setUniform("projection", projMat);

    const float * const mp = m_transformMatrix;

    float viewArray[16] =
    {
        mp[0], mp[4], mp[8],  0.0f,
        mp[1], mp[5], mp[9],  0.0f,
        mp[2], mp[6], mp[10], 0.0f,

        (
            mp[0] * mp[12] + mp[1] * mp[13] + mp[2] * mp[14]
        ),
        (
            mp[4] * mp[12] + mp[5] * mp[13] + mp[6] * mp[14]
        ),
        (
            mp[8] * mp[12] + mp[9] * mp[13] + mp[10] * mp[14]
        ),

        1.0f
    };

    glm::mat4 viewMat = glm::make_mat4(viewArray);

    shader.setUniform("view", viewMat);
}
