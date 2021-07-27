#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <unordered_map>
#include <glm/vec2.hpp>
#include "Tile.h"
#include "../graphics/SpriteBatch.h"
#include "../utils/WorldConst.h"
#include "../utils/Types.h"

namespace map
{
    using TileArray = std::array<u8, CHUNK_VOLUME>;

    class Chunk
    {
    private:
        TileArray m_tiles;
        glm::ivec2 m_pos;
        int m_size;
    public:
        Chunk();
        Chunk(const glm::ivec2& pos);
        ~Chunk() = default;

        const glm::ivec2& getPosition() const;
        u8 getTile(const glm::ivec2& tilePos) const;
        void setTile(const glm::ivec2& tilePos, const Tile& tile);
        
        // TODO: временное решение. Переделать под структуру Tile
        void draw(SpriteBatch& batch);
    };
} // namespace world


#endif