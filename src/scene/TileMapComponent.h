#ifndef TILEMAPCOMPONENT_H
#define TILEMAPCOMPONENT_H

#include <unordered_map>
#include <glm/vec2.hpp>
#include "../utils/Types.h"
#include "../utils/Coordinate.h"
#include "../world/Chunk.h"

struct ChunkHash
{
    // http://www.beosil.com/download/CollisionDetectionHashing_VMV03.pdf
    std::size_t operator()(const glm::ivec2 position) const
    {
        return (position.x * 56554) ^ (position.y * 211287);
    }
};

using ChunkHashMap = std::unordered_map<glm::ivec2, map::Chunk, ChunkHash>;

struct TileMapComponent
{
    ChunkHashMap chunks;
    IntRect size;

    TileMapComponent(const IntRect& startSize) : size(startSize)
    {
        for (int x = size.getLeft(); x < size.getWidth(); x++)
        {
            for (int y = size.getBottom(); y < size.getHeight(); y++)
            {
                chunks[glm::ivec2(x, y)] = map::Chunk({x, y});
            }
        }
    }

    bool hasTile(const glm::ivec2& tilePosition) const
    {
        return chunks.at(utils::toLocalTilePos(tilePosition))
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