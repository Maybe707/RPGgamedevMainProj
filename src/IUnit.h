#ifndef UNIT_INTERFACE_H
#define UNIT_INTERFACE_H

#include "graphics/Shader.h"
#include "graphics/Texture.h"

class IUnit
{
public:
    virtual ~IUnit() {}

    virtual void draw(const int screenWidth, const int screenHeight,
                      Shader shader, unsigned int vaoId, Texture texture) = 0;

    virtual void receiver(int key, int action) = 0;
};

#endif
