#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/vec2.hpp>
#include "Chunk.h"

namespace map
{
    using ChukVector = std::vector<Chunk>;

    class World
    {
    private:
        ChukVector m_chunks;
        int m_size;
    public:
        World();
        
        void init();
        void destroy();
        
        const ChukVector& getChunks() const;
        const Chunk& getChunk(glm::ivec2 chunkPos);
        u8 getTile(glm::ivec2 tilePos);

        // TODO: временное решение. Переделать под структуру Tile
        void draw(SpriteBatch& batch, Sprite& sprite);
    };

} // namespace world


#endif