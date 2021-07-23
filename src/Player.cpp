#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(float xAxis, float yAxis, float speed) :
        m_xAxis(xAxis),
        m_yAxis(yAxis),
        m_Speed(speed) {}

void Player::setXAxis(float xAxis)
{
    m_xAxis = xAxis;
}

void Player::setYAxis(float yAxis)
{
    m_yAxis = yAxis;
}

float Player::getXAxis()
{
    return m_xAxis;
}

float Player::getYAxis()
{
    return m_yAxis;
}

float Player::getXRange()
{
    return m_xRange;
}

float Player::getYRange()
{
    return m_yRange;
}

void Player::draw(const int screenWidth, const int screenHeight,
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

void Player::receiver(int key, int action)
{
    m_keyAxis = key;
    m_action = action;
}

int &Player::getKeyAxis()
{
    return m_keyAxis;
}

void Player::setKeyAxis(int key)
{
    m_keyAxis = key;
}

int &Player::getAction()
{
    return m_action;
}

void Player::setSpeed(const float &speed)
{
    m_Speed = speed;
}

float &Player::getSpeed()
{
    return m_Speed;
}
