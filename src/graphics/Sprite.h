#ifndef RPG_SPRITE_H
#define RPG_SPRITE_H

#include <glm/glm.hpp>
#include "Rect.h"
#include "Texture.h"

class Sprite
{
    glm::vec2 m_position{};
    glm::vec2 m_origin{};
    float m_width;
    float m_height;
    IntRect m_textureRect;
    Texture& m_texture;

public:
    Sprite(Texture& texture);

    glm::vec2 getPosition() const;

    void setPosition(glm::vec2 position);

    glm::vec2 getOrigin() const;

    void setOrigin(glm::vec2 origin);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    Texture& getTexture() const;

    IntRect getTextureRect() const;

    void setTextureRect(const IntRect &rect);

};

#endif //RPG_SPRITE_H
