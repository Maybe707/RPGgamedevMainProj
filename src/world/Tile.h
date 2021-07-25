#ifndef TILE_H
#define TILE_H

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
    };   
} // namespace world




#endif