#include "Player_Implementation.h"

#include <glm/gtc/matrix_transform.hpp>

PlayerImpl::PlayerImpl(float xAxis, float yAxis, float speed) :
    m_xAxis(xAxis),
    m_yAxis(yAxis),
    m_Speed(speed)
{ }

void PlayerImpl::setXAxis(float xAxis)
{
    m_xAxis = xAxis;
}

void PlayerImpl::setYAxis(float yAxis)
{
    m_yAxis = yAxis;
}

float PlayerImpl::getXAxis()
{
    return m_xAxis;
}

float PlayerImpl::getYAxis()
{
    return m_yAxis;
}

float PlayerImpl::getXRange()
{
    return m_xRange;
}

float PlayerImpl::getYRange()
{
    return m_yRange;
}

void PlayerImpl::draw(const int screenWidth, const int screenHeight,
                      Shader shader, unsigned int vaoId, Texture texture)
{
    glm::mat4 transformMat = glm::mat4(1.f);

    transformMat = glm::translate(transformMat, glm::vec3(m_xAxis, m_yAxis, 0.f));
    transformMat = glm::scale(transformMat, glm::vec3(64.f));

    shader.use();
    shader.setUniform("model", transformMat);

    texture.bind();

    glBindVertexArray(vaoId);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PlayerImpl::receiver(int key, int action)
{
    m_keyAxis = key;
    m_action = action;
}

int& PlayerImpl::getKeyAxis()
{
    return m_keyAxis;
}

void PlayerImpl::setKeyAxis(int key)
{
    m_keyAxis = key;
}

int& PlayerImpl::getAction()
{
    return m_action;
}

void PlayerImpl::set_Speed(const float &speed)
{
    m_Speed = speed;
}

float& PlayerImpl::getSpeed()
{
    return m_Speed;
}
