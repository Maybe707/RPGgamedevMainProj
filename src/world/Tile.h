#ifndef TILE_H
#define TILE_H

#include <vector>
#include <memory>
#include "../graphics/Sprite.h"
#include "../utils/Types.h"

namespace map
{
    enum class TileType
    {
        EMPTY = 0,
        WALL,
        GROUND
    };

    // TODO: Заготовка для информации о тайле. 
    struct Tile
    {
        TileType m_type;
        Sprite& m_sprite;
        u8 m_id;
        bool m_collide;

        Tile(TileType type, Sprite& sprite, u8 id, bool collide) 
            : m_type(type),
            m_sprite(sprite),
            m_id(id),
            m_collide(collide) {};
        // может ли игрок столкнуться с тайлом
        inline bool isCollide() const { return m_collide; }
        inline Sprite& getSprite() const { return m_sprite; }
        inline TileType getType() const { return m_type; }
        inline u8 getId() const { return m_id; }
    };

    // TODO: временное решение в виде глобальной переменной. Определение в GameMain.cpp
    extern std::vector<std::unique_ptr<Tile>> TilesData;
} // namespace world

#endif
