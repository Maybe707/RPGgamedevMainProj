#ifndef TILEMAPCOMPONENT_H
#define TILEMAPCOMPONENT_H

#include <unordered_map>
#include <glm/vec2.hpp>
#include "../../utils/Types.h"
#include "../../utils/Coordinate.h"
#include "../../world/Chunk.h"

struct ChunkHash
{
    // http://www.beosil.com/download/CollisionDetectionHashing_VMV03.pdf
    std::size_t operator()(const glm::ivec2 position) const
    {
        return (position.x * 56554) ^ (position.y * 211287);
    }
};

using ChunkHashMap = std::unordered_map<glm::ivec2, map::Chunk, ChunkHash>;

class TilePallet
{
    

};

struct TileMap
{
    ChunkHashMap chunks;
    IntRect bounds;

    // временная реализация через указатель.
    TilePallet* tilePallet;

    TileMap(const IntRect& startBounds) : bounds(startBounds)
    {
        for (int x = bounds.getLeft(); x < bounds.getWidth(); x++)
        {
            for (int y = bounds.getBottom(); y < bounds.getHeight(); y++)
            {
                chunks[glm::ivec2(x, y)] = map::Chunk({x, y});
            }
        }
    }

    void setTilePallet(TilePallet* pallet)
    {
        tilePallet = pallet;
    }

    const TilePallet* getPallet() const
    {
        return tilePallet;
    }

    bool hasTile(const glm::ivec2& tilePosition) const
    {
        return chunks.at(utils::toChunkPos(tilePosition))
            .hasTile(utils::toLocalTilePos(tilePosition));
    }

    u8 getTile(const glm::ivec2& tilePosition) const
    {
        return chunks.at(utils::toChunkPos(tilePosition))
            .getTile(utils::toLocalTilePos(tilePosition));
    }

    void setTile(const glm::ivec2& position, const map::Tile& tile)
    {
        chunks.at(utils::toChunkPos(position))
            .setTile(utils::toLocalTilePos(position), tile);
    }
};


#endif