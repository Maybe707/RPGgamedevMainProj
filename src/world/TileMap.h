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

    class TileMap
    {
    private:
        ChunkHashMap m_chunks;
        IntRect m_size;
    public:
        TileMap();
        
        void init();
        
        const IntRect& getSize() const;
        /**
         * <p>Возвращает ссылку на чанки в мире</p>
         * 
         * @return const ChunkVector&
        */
        const ChunkHashMap& getChunks() const;
        /**
         * <p>Возвращает ссылку на чанк по его позиции</p>
         * 
         * @param chunkPos Позиция чанка в мире
         * @return const ChunkVector&
        */
        const Chunk& getChunk(glm::ivec2 chunkPos) const;
        /**
         * <p>Возвращает id тайла по позиции в мире</p>
         * 
         * @param tilePos Позиция тайла в мире
         * @return const ChunkVector&
        */
        u8 getTile(glm::ivec2 tilePos) const;
        /**
         * <p>Рисуте мир</p>
         * 
         * @param batch Пакетный рендер
        */
        void draw(SpriteBatch& batch);
    };

} // namespace world


#endif