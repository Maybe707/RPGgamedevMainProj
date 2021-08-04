#ifndef TILE_H
#define TILE_H

#include <vector>
#include <memory>
#include "../../client/graphics/Sprite.h"
#include "../../utils/Types.h"

class Tile
{
private:
    u8 m_id{0};
    FloatRect m_aabb{0, 0, 0, 0};
    IntRect m_texRect{0, 0, 0, 0};
    bool m_collide{0};
public:
    Tile() = default;
    Tile(u8 id, const FloatRect& aabb, const IntRect& texRect, bool collide) : 
        m_id(id),
        m_aabb(aabb),
        m_texRect(texRect),
        m_collide(collide) { }
    
    /**
     * <p>Возвращает id тайла</p>
     * 
     * @return id тайла
    */
    u8 getId() const { return m_id; }
    /**
     * <p>Возвращает размер и положение тайла</p>
     * 
     * @return размер и положение тайла
    */
    const IntRect& getRect() const { return m_texRect; }
};

#endif
