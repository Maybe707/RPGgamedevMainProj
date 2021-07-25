#ifndef RPG_TEXT_H
#define RPG_TEXT_H

#include "Sprite.h"
#include "Font.h"

/**
 * Сделал этот классик, чтоб была возможность удобнее работать с текстом.
 * Узнавать его размеры, изменять какие-то параметры и прочее.
 */
class Text
{
    Font& m_font;
    std::string m_text;

    glm::vec2 m_position{};

    glm::vec2 m_origin{};

    glm::vec4 m_color;

    float m_width;
    float m_height;

    std::vector<Sprite> m_sprites;

public:
    Text(Font& font, std::string text);

    void draw(SpriteBatch& batch);

    glm::vec2 getPosition() const;
    void setPosition(glm::vec2 position);

    glm::vec2 getOrigin() const;
    void setOrigin(glm::vec2 origin);

    glm::vec4 getColor() const;
    void setColor(glm::vec4 color);

    float getWidth() const;
    float getHeight() const;
};

#endif //RPG_TEXT_H
