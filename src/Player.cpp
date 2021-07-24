#include "Player.h"

Player::Player(Sprite& sprite, float speed)
        : m_sprite(sprite),
          m_speed(speed) {}

glm::vec2 Player::getPosition() const
{
    return m_sprite.getPosition();
}

void Player::setPosition(glm::vec2 position)
{
    m_sprite.setPosition(position);
}

void Player::setSpeed(const float speed)
{
    m_speed = speed;
}

float Player::getSpeed() const
{
    return m_speed;
}

void Player::draw(SpriteBatch& batch)
{
    batch.draw(m_sprite);
}

void Player::receiver(int key, int action)
{
    m_keyAxis = key;
}

int Player::getKeyAxis() const
{
    return m_keyAxis;
}
