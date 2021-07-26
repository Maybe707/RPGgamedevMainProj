#include "World.h"
#include "../utils/Coordinate.h"

namespace map
{
    World::World() : m_chunks(25), m_size(5) { }

    void World::init()
    {
        for (size_t y = 0; y < m_size; y++)
        {
            for (size_t x = 0; x < m_size; x++)
            {
                // m_chunks[y * m_size + x] = Chunk({x, y});
                m_testChunks[glm::ivec2(x, y)] = Chunk({x, y});
                m_testChunks[glm::ivec2(-x, -y)] = Chunk({-x, -y});
            }
        }
    }

    const ChunkVector& World::getChunks() const
    {
        return m_chunks;
    }

    const Chunk& World::getChunk(glm::ivec2 chunkPos)
    {
        // return m_chunks.at(chunkPos.y * CHUNK_SIZE + chunkPos.x);
        return m_testChunks.at(chunkPos);
    }

    u8 World::getTile(glm::ivec2 tilePos)
    {
        auto chunkPos = toChunkPos(tilePos);
        // return m_chunks.at(chunkPos.y * 5 + chunkPos.x).getTile(toLocalTilePos(tilePos));
        return m_testChunks.at(chunkPos).getTile(toLocalTilePos(tilePos));
    }

    void World::draw(SpriteBatch& batch, Sprite& sprite)
    {
        for (auto& chunk : m_testChunks)
        {
            chunk.second.draw(batch, sprite);
        }
    }

} // namespace world
