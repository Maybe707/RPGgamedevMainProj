#include "Text.h"

Text::Text(Font &font, std::string text)
        : m_font(font), m_color(1.f), m_text(std::move(text))
{
    Sprite sprite(m_font.getTexture());

    // Сразу при генерации узнаем размеры текста
    float maxWidth = 0;
    float maxHeight = font.getSize();

    glm::vec2 pos(0.f);
    for (char c : m_text)
    {
        if (c == ' ')
        {
            // Размер пробела пусть зависит от высоты шрифта
            pos += glm::vec2(m_font.getSize() / 4, 0.f);
            continue;
        }
        if (c == '\n')
        {
            // Тут шаманим, чтоб сделать отступ, вычислить ширину и высоту. Бррр..
            if (maxWidth < pos.x) {
                maxWidth = pos.x;
            }
            maxHeight += m_font.getSize();
            pos = glm::vec2(0.f, pos.y - m_font.getSize());
            continue;
        }

        Character character = m_font.getCharacter(c);

        // Приходится переворачивать текстуру, потому что у freetype точка отчета находится слева вверху, а у нас слева внизу.
        // Если кто-то знает способ лучше, сообщите
        sprite.setTextureRect(
                IntRect(character.xOffset, character.size.y, character.size.x, -character.size.y)
        );
        sprite.setOrigin(glm::vec2(0.f, character.size.y / 2));
        sprite.setWidth(character.size.x);
        sprite.setHeight(character.size.y);
        sprite.setPosition(pos);

        m_sprites.push_back(sprite);

        pos += glm::vec2(sprite.getWidth(), 0.f);
    }
    // Еще раз проверяем ширину для последней строки
    if (maxWidth < pos.x) {
        maxWidth = pos.x;
    }
    m_width = maxWidth;
    m_height = maxHeight;
}

void Text::draw(SpriteBatch &batch)
{
    for (auto sprite : m_sprites)
    {
        // Шаманим, чтобы центр был в левом нижнем углу текста и работал ориджин
        sprite.setPosition(sprite.getPosition() + m_position + glm::vec2(0.f, m_height - m_font.getSize() / 2) - m_origin);
        sprite.setColor(m_color);
        batch.draw(sprite);
    }
}

glm::vec2 Text::getPosition() const
{
    return m_position;
}

void Text::setPosition(glm::vec2 position)
{
    m_position = position;
}

glm::vec2 Text::getOrigin() const
{
    return m_origin;
}

void Text::setOrigin(glm::vec2 origin)
{
    m_origin = origin;
}

glm::vec4 Text::getColor() const
{
    return m_color;
}

void Text::setColor(glm::vec4 color)
{
    m_color = color;
}

float Text::getWidth() const
{
    return m_width;
}

float Text::getHeight() const
{
    return m_height;
}


