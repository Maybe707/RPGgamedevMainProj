#include "Sprite_RandSet.h"

Sprite_RandSet::Sprite_RandSet(const int width, const int height) : m_width(width), m_height(height)
{
    Sprite_SetArray = new char*[m_height];
    for(int i = 0; i < m_width; ++i)
        Sprite_SetArray[i] = new char[m_width];
}

Sprite_RandSet::~Sprite_RandSet()
{
    for(int i = 0; i < m_height; ++i)
        delete [] Sprite_SetArray[i];
    delete [] Sprite_SetArray;    
}

void Sprite_RandSet::setRandSprite(const char*** Sprite_Set, const int rand_index)
{
    for(int y = 0; y < m_height; ++y)
        for(int x = 0; x < m_width; ++x)
            Sprite_SetArray[y][x] = Sprite_Set[rand_index][y][x];
}

const int Sprite_RandSet::getWidth() const
{
    return m_width;
}

const int Sprite_RandSet::getHeight() const
{
    return m_height;
}

char** Sprite_RandSet::getSprite_SetArray() const
{
    return Sprite_SetArray;
}
