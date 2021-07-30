#ifndef RPG_SPRITERENDERERCOMPONENT_H
#define RPG_SPRITERENDERERCOMPONENT_H

#include <glm/glm.hpp>
#include "../../graphics/Texture.h"
#include "../../graphics/Rect.h"

struct SpriteRendererComponent
{
    Texture texture;
    IntRect textureRect{0, 0, 0, 0};
    glm::vec4 color{1.f};

    SpriteRendererComponent(Texture texture);
};

#endif //RPG_SPRITERENDERERCOMPONENT_H
