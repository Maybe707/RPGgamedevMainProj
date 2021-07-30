#include "TileMap.h"
#include "../utils/Coordinate.h"

namespace map
{
    TileMap::TileMap() : m_size({-2, -3, 3, 2}) { }

    void TileMap::init()
    {
        for (int y = -3; y < 2; y++)
        {
            for (int x = -2; x < 3; x++)
            {
                m_chunks[glm::ivec2(x, y)] = Chunk({x, y});
            }
        }
    }

    const IntRect& TileMap::getSize() const
    {
        return m_size;
    }

    const ChunkHashMap& TileMap::getChunks() const
    {
        return m_chunks;
    }

    const Chunk& TileMap::getChunk(glm::ivec2 chunkPos) const
    {
        // return m_chunks.at(chunkPos.y * CHUNK_SIZE + chunkPos.x);
        return m_chunks.at(chunkPos);
    }

    u8 TileMap::getTile(glm::ivec2 tilePos) const
    {
        auto chunkPos = toChunkPos(tilePos);
        // return m_chunks.at(chunkPos.y * 5 + chunkPos.x).getTile(toLocalTilePos(tilePos));
        return m_chunks.at(chunkPos).getTile(toLocalTilePos(tilePos));
    }

    void TileMap::draw(SpriteBatch& batch)
    {
        for (auto& chunk : m_chunks)
        {
            chunk.second.draw(batch);
        }
    }

} // namespace world
