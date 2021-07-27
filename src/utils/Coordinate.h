#ifndef COORDINATE_H
#define COORDINATE_H

#include <glm/vec2.hpp>
#include "WorldConst.h"

namespace map
{
    inline glm::ivec2 toChunkPos(const glm::ivec2& globalTilePos)
    {
        int x = globalTilePos.x;
        int y = globalTilePos.y;

        return 
        {
            x < 0 ? ((x - CHUNK_SIZE) / CHUNK_SIZE) : (x / CHUNK_SIZE),
            y < 0 ? ((y - CHUNK_SIZE) / CHUNK_SIZE) : (y / CHUNK_SIZE)
        };
    }

    inline glm::ivec2 toLocalTilePos(const glm::ivec2& globalTilePos)
    {
        int x = globalTilePos.x;
        int y = globalTilePos.y;

        return
        {
            ((CHUNK_SIZE + (x % CHUNK_SIZE)) % CHUNK_SIZE),
            ((CHUNK_SIZE + (y % CHUNK_SIZE)) % CHUNK_SIZE)
        };
    }

    inline glm::ivec2 toGlobalTilePos(const glm::ivec2& locallTilePos, const glm::ivec2& chunkPos)
    {
        return 
        {
            (locallTilePos.x + chunkPos.x * CHUNK_SIZE),
            (locallTilePos.y + chunkPos.y * CHUNK_SIZE),
        };
    }

    inline std::size_t toLocalTileIndex(const glm::ivec2& localTilePos)
    {
        return localTilePos.y * CHUNK_SIZE + localTilePos.x;
    }
} // namespace map

#endif