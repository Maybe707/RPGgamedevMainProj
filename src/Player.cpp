#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(glm::vec2 position, float speed)
        : m_position(position),
          m_Speed(speed) {}

glm::vec2 Player::getPosition() const
{
    return m_position;
}

void Player::setPosition(glm::vec2 position)
{
    m_position = position;
}

void Player::setSpeed(const float speed)
{
    m_Speed = speed;
}

float Player::getSpeed() const
{
    return m_Speed;
}

void Player::draw(Shader shader, unsigned int vaoId, Texture texture)
{
    glm::mat4 transformMat(1.f);

    transformMat = glm::translate(transformMat, glm::vec3(m_position, 0.f));
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
}

int Player::getKeyAxis()
{
    return m_keyAxis;
}
