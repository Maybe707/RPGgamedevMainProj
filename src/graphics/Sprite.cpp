#include "Sprite.h"


Sprite::Sprite(Texture& texture)
        : m_width((float) texture.getWidth()), m_height((float) texture.getHeight()),
          m_textureRect(0, 0, texture.getWidth(), texture.getHeight()),
          m_texture(texture) {}

glm::vec2 Sprite::getPosition() const
{
    return m_position;
}

void Sprite::setPosition(glm::vec2 position)
{
    m_position = position;
}

glm::vec2 Sprite::getOrigin() const
{
    return m_origin;
}

void Sprite::setOrigin(glm::vec2 origin)
{
    m_origin = origin;
}

float Sprite::getWidth() const
{
    return m_width;
}

void Sprite::setWidth(float width)
{
    m_width = width;
}

float Sprite::getHeight() const
{
    return m_height;
}

void Sprite::setHeight(float height)
{
    m_height = height;
}

Texture& Sprite::getTexture() const
{
    return m_texture;
}

IntRect Sprite::getTextureRect() const
{
    return m_textureRect;
}

void Sprite::setTextureRect(const IntRect &rect)
{
    m_textureRect = rect;
}
