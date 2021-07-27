#include "Sprite.h"


Sprite::Sprite(Texture &texture)
        : m_scale(1.f),
          m_color(1.f),
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

glm::vec2 Sprite::getScale() const
{
    return m_scale;
}

void Sprite::setScale(glm::vec2 scale)
{
    m_scale = scale;
}

glm::vec4 Sprite::getColor() const
{
    return m_color;
}

void Sprite::setColor(glm::vec4 color)
{
    m_color = color;
}

Texture &Sprite::getTexture() const
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
