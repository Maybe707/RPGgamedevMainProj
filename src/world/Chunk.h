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
        
        const TileArray& getTiles() const;

        /**
         * <p>Возвращает позицию в мире</p>
         * 
         * @return const glm::ivec2&
        */
        const glm::ivec2& getPosition() const;

        /**
         * <p>Возвращает id тайла по позиции в чанке</p>
         * 
         * @param tilePos Позиция тайла в чанке
         * @return u8 id
        */
        u8 getTile(const glm::ivec2& tilePos) const;

        /**
         * <p>Возвращает id тайла по позиции в чанке</p>
         * 
         * @param tilePos Позиция тайла в чанке
         * @param tile устанавлеваемый тайл
        */
        void setTile(const glm::ivec2& tilePos, const Tile& tile);
        
        /**
         * <p>Рисуте чанк</p>
         * 
         * @param batch Пакетный рендер
        */
        void draw(SpriteBatch& batch);
    };
} // namespace world


#endif