#ifndef SPRITE_RANDSET
#define SPRITE_RANDSET

#include "Map_Objects.h"

class Sprite_RandSet
{

    const int m_width;
    const int m_height;
    char** Sprite_SetArray;

public:
    Sprite_RandSet(const int width, const int height);

    ~Sprite_RandSet();
    
    void setRandSprite(const char*** Sprite_Set, const int rand_index);

    const int getWidth() const;
    const int getHeight() const;
    char** getSprite_SetArray() const;
};

#endif
