#include "Chunk.h"
#include "../utils/Coordinate.h"
#include <cstring>


Chunk::Chunk() : m_pos(0, 0), m_size(CHUNK_SIZE) { }

    // TODO: Отрефакторить конструтор. Сделать генерацию в отдельном объекте
Chunk::Chunk(const glm::ivec2& pos) : m_pos(pos), m_size(CHUNK_SIZE) 
{
    std::memset(m_tiles, 0, sizeof(u8) * CHUNK_VOLUME);
}

const TileArray& Chunk::getTiles() const
{
    return m_tiles;
}

bool Chunk::hasTile(const glm::ivec2 tilePos) const
{
    return &m_tiles[utils::toLocalTileIndex(tilePos)] != nullptr;
}

const glm::ivec2& Chunk::getPosition() const
{
    return m_pos;
}

u8 Chunk::getTile(const glm::ivec2& tilePos) const
{
    return m_tiles[utils::toLocalTileIndex(tilePos)];
}

void Chunk::setTile(const glm::ivec2& tilePos, const Tile& tile)
{
    m_tiles[utils::toLocalTileIndex(tilePos)] = tile.getId();
}

void Chunk::draw(SpriteBatch& batch)
{
    for (size_t y = 0; y < CHUNK_SIZE; y++)
    {
        for (size_t x = 0; x < CHUNK_SIZE; x++)
        {
            u8 tileId = m_tiles[y * CHUNK_SIZE + x];
            int realX = x + m_pos.x * CHUNK_SIZE;
            int realY = y + m_pos.y * CHUNK_SIZE;

            if (tileId == 0) continue;

            auto& spr = TilesData.at(tileId)->getSprite();
            spr.setPosition({realX * spr.getGlobalBounds().getWidth(), realY * spr.getGlobalBounds().getHeight()});
            batch.draw(spr);
        }
    }
}
