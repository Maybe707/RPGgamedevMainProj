#ifndef RPG_WORLDMAPCOMPONENT_H
#define RPG_WORLDMAPCOMPONENT_H

#include <unordered_map>
#include <vector>
#include <glm/vec2.hpp>
#include "../../client/graphics/Texture.h"
#include "../../client/graphics/Rect.h"

struct Tile
{
    Texture *texture;
    IntRect textureRect{0, 0, 0, 0};

    int layer{0};
    glm::vec2 origin;
};

class IWorldMapGenerator
{
public:
    virtual ~IWorldMapGenerator() = default;

    virtual std::vector<Tile> generate(int x, int y) = 0;
};

struct WorldMapComponent
{
    int tileSize{32};

    IWorldMapGenerator *generator;

    int renderRadius{12};
};

#endif //RPG_WORLDMAPCOMPONENT_H
