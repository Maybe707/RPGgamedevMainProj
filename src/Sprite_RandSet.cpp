#include "Sprite_RandSet.h"

SpriteRandSet::SpriteRandSet(const int width, const int height) :
    m_width(width),
    m_height(height)
{
    m_spriteSetArray = new char *[m_height];

    for (int i = 0; i < m_width; ++i)
    {
        m_spriteSetArray[i] = new char[m_width];
    }
}

SpriteRandSet::~SpriteRandSet()
{
    for (int i = 0; i < m_height; ++i)
    {
        delete[] m_spriteSetArray[i];
    }

    delete[] m_spriteSetArray;    
}

void SpriteRandSet::setRandSprite(const char*** spriteSet, const int randIndex)
{
    for(int y = 0; y < m_height; ++y)
    {
        for(int x = 0; x < m_width; ++x)
        {
            m_spriteSetArray[y][x] = spriteSet[randIndex][y][x];
        }
    }
}

const int SpriteRandSet::getWidth() const
{
    return m_width;
}

const int SpriteRandSet::getHeight() const
{
    return m_height;
}

char** SpriteRandSet::getSpriteSetArray() const
{
    return m_spriteSetArray;
}
