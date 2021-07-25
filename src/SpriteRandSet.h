#ifndef SPRITE_RANDSET_H
#define SPRITE_RANDSET_H

class SpriteRandSet
{
    const int m_width;
    const int m_height;
    char** m_spriteSetArray;
public:
    SpriteRandSet(const int width, const int height);

    virtual ~SpriteRandSet();
    
    void setRandSprite(const char*** spriteSet, const int randIndex);

    const int getWidth() const;
    const int getHeight() const;

    char** getSpriteSetArray() const;
};

#endif
