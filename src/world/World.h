#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <unordered_map>
#include <glm/vec2.hpp>
#include "Chunk.h"

// TODO: не знаю куда лучше положить
struct ChunkHash
{
    // http://www.beosil.com/download/CollisionDetectionHashing_VMV03.pdf
    std::size_t operator()(const glm::ivec2 position) const
    {
        return (position.x * 56554) ^ (position.y * 211287);
    }
};

namespace map
{
    using ChunkVector = std::vector<Chunk>;
    using ChunkHashMap = std::unordered_map<glm::ivec2, Chunk, ChunkHash>;

    class World
    {
    private:
        ChunkVector m_chunks;
        ChunkHashMap m_testChunks;
        int m_size;
    public:
        World();
        
        void init();
        
        int getSize() const;

        const ChunkVector& getChunks() const;
        const Chunk& getChunk(glm::ivec2 chunkPos) const;
        u8 getTile(glm::ivec2 tilePos) const;

        // TODO: временное решение. Переделать под структуру Tile
        void draw(SpriteBatch& batch);
    };

} // namespace world


#endif