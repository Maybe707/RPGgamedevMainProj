#include "World.h"
#include "../utils/Coordinate.h"

namespace map
{
    World::World() : m_size(5) { }

    void World::init()
    {
        for (int y = -3; y < 2; y++)
        {
            for (int x = -2; x < 3; x++)
            {
                m_chunks[glm::ivec2(x, y)] = Chunk({x, y});
            }
        }
    }

    int World::getSize() const
    {
        return m_size;
    }

    const ChunkHashMap& World::getChunks() const
    {
        return m_chunks;
    }

    const Chunk& World::getChunk(glm::ivec2 chunkPos) const
    {
        // return m_chunks.at(chunkPos.y * CHUNK_SIZE + chunkPos.x);
        return m_chunks.at(chunkPos);
    }

    u8 World::getTile(glm::ivec2 tilePos) const
    {
        auto chunkPos = toChunkPos(tilePos);
        // return m_chunks.at(chunkPos.y * 5 + chunkPos.x).getTile(toLocalTilePos(tilePos));
        return m_chunks.at(chunkPos).getTile(toLocalTilePos(tilePos));
    }

    void World::draw(SpriteBatch& batch)
    {
        for (auto& chunk : m_chunks)
        {
            chunk.second.draw(batch);
        }
    }

} // namespace world
