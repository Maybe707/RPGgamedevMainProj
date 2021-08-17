#ifndef RPG_WORLDMAPCOMPONENT_H
#define RPG_WORLDMAPCOMPONENT_H

#include <unordered_map>
#include "../../client/graphics/Texture.h"
#include "../../client/graphics/Rect.h"

struct Tile
{
    Texture *texture;
    IntRect textureRect{0, 0, 0, 0};
};

class IWorldMapGenerator
{
public:
    virtual ~IWorldMapGenerator() = default;

    virtual int generate(int x, int y) = 0;
};

struct WorldMapComponent
{
    std::unordered_map<int, Tile> tileSet;
    int tileSize{32};

    IWorldMapGenerator *generator;

    int renderRadius{12};

    void addTile(int id, Tile tile);
};

#endif //RPG_WORLDMAPCOMPONENT_H
