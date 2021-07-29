#ifndef UNIT_INTERFACE_H
#define UNIT_INTERFACE_H

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/SpriteBatch.h"

// TODO: удалить
class IUnit
{
public:
    virtual ~IUnit() {}

    virtual void draw(SpriteBatch& batch) = 0;

    virtual void receiver(int key, int action) = 0;
};

#endif
