#ifndef RPG_SPRITE_H
#define RPG_SPRITE_H

#include <glm/glm.hpp>
#include "Rect.h"
#include "Texture.h"

class Sprite
{
    glm::vec2 m_position{};
    glm::vec2 m_origin{};
    glm::vec2 m_scale;
    glm::vec4 m_color;
    IntRect m_textureRect;
    Texture& m_texture;

public:
    Sprite(Texture& texture);

    glm::vec2 getPosition() const;
    void setPosition(glm::vec2 position);

    glm::vec2 getOrigin() const;
    void setOrigin(glm::vec2 origin);

    glm::vec2 getScale() const;
    void setScale(glm::vec2 scale);

    glm::vec4 getColor() const;
    void setColor(glm::vec4 color);

    Texture& getTexture() const;

    IntRect getTextureRect() const;
    void setTextureRect(const IntRect &rect);

    /**
     * Получить границы спрайта без учета всех трансформаций.
     *
     * @return локальные границы спрайта
     */
    FloatRect getLocalBounds();

    /**
     * Получить границы спрайта с учетом всех трансформаций.
     *
     * @return глобальные границы спрайта
     */
    FloatRect getGlobalBounds();
};

#endif //RPG_SPRITE_H
